#include <Arduino.h>
/*
Color:       Red    Blue   White   Yellow
  LED pin:     D8     D9     D10     D11
  Button pin:  D2     D3     D4      D5
  Tone (Hz):   262    330    392     523
  Passive buzzer: D6 to positive
*/
const int count = 4; 
const int ledPins[count] = {8,9,10,11}; // red, blue, white, yellow
const int buttons[count] = {2,3,4,5}; // same color order as ledPins
const  int toneFrequencies[count] = {262, 330, 392, 523}; // matching tone frequencies in Hz 
const int maxSequenceLength = 8; 
const int buzzerPin = 6;
const int responseMS = 160; // light and tone duration for an accepted answer, in ms
const int playbackMS = 500; // light and tone duration for each sequence item, in ms
const int playbackGapMS = 250; // dark, silent pause between sequence items, in ms
// Stores color indices 0-3; only the first currentLen entries are used
int sequenceArr[maxSequenceLength] = {};
int answerPosition = 0; // position in the sequence that the player's next button press must match
int currentLen = 0; // number of sequence items the player must repeat this round
const int waitingState = 0;
const int playbackState = 1;
const int playerInputState = 2;
int gameState = waitingState;
const int debounceMS = 25; // prevents contact bounce, no extra presses 
int lastButtonReadings[count] = {HIGH, HIGH, HIGH, HIGH};

// unsigned long matches millis() and holds clock values too large for an Uno int
unsigned long lastButtonChange = 0;

int readyForPress = 0; // 1 allows a new press; 0 waits for all buttons to be released for 25 ms
const int answerTimeoutMS = 5000; // time allowed for each next answer, in ms
unsigned long answerWaitStarted = 0; // unsigned long matches the type returned by millis()

// choice is a color index (0-3); play its LED and matching tone for durationMS milliseconds
void playChoice(int choice, int durationMS) {
  digitalWrite(ledPins[choice], HIGH);
  tone(buzzerPin, toneFrequencies[choice]);
  delay(durationMS);
  noTone(buzzerPin);
  digitalWrite(ledPins[choice], LOW);
}

// Leave a dark silent gap between items so repeated colors are distinguishable
void playSequence() {
  Serial.print("Round length: ");
  Serial.println(currentLen);
  for (int i = 0; i < currentLen; i++) {
    // i is the sequence position; sequenceArr[i] is the color to display
    playChoice(sequenceArr[i], playbackMS);
    delay(playbackGapMS);
  }
  Serial.println("Your turn");
}

// Require all buttons to be released for 25 ms before accepting another press
// This prevents a button held during playback or feedback from counting afterward
void requireButtonRelease() {
  readyForPress = 0;
  for (int i = 0; i < count; i++) {
    lastButtonReadings[i] = digitalRead(buttons[i]);
  }
  lastButtonChange = millis(); //returns ms have passed since start
}

// Return the color index (red,blue,white,yellow) for one new press, or -1 when no press is accepted
// Ignore brief changes in the button readings caused by mechanical contact bounce
int readNewButtonPress() {
  // declares variables to check buttons
  const unsigned long now = millis(); // saves current time for timeout failure 
  int pressedCount = 0;
  int choice = -1;
  // loop reads all four buttons 
  for (int i = 0; i < count; i++) {
    int reading = digitalRead(buttons[i]);
    if (reading != lastButtonReadings[i]) {
      lastButtonReadings[i] = reading;
      lastButtonChange = now;
    }
    if (reading == LOW) {
      pressedCount++;
      choice = i;
    }
  }
  // If multiple buttons are down together, ignore them until all are released
  if (pressedCount > 1) {
    readyForPress = 0;
    return -1;
  }
  if (now - lastButtonChange < debounceMS) {
    return -1; // The readings have not been stable long enough
  }
  if (pressedCount == 0) {
    readyForPress = 1;
    return -1;
  }
  if (readyForPress == 0) {
    return -1;
  }
  readyForPress = 0; // this button must be released before another press can count
  return choice;
}

// state is HIGH to turn all LEDs on, or LOW to turn them off
void setAllLeds(int state) {
  for (int i = 0; i < count; i++) {
    digitalWrite(ledPins[i], state);
  }
}

// frequency is in Hz; durationMS is how long all LEDs and the tone stay on
// Each flash ends with a 120 ms dark, silent pause
void flashFeedback(int frequency, int durationMS) {
  setAllLeds(HIGH);
  tone(buzzerPin, frequency);
  delay(durationMS);
  noTone(buzzerPin);
  setAllLeds(LOW);
  delay(120);
}

void roundSuccessFeedback() {
  Serial.println("Correct round!");
  flashFeedback(659, 120);
  flashFeedback(784, 120);
}

void failureFeedback() {
  Serial.println("Game over :(");
  flashFeedback(196, 300);
  flashFeedback(131, 400);
}

void victoryFeedback() {
  Serial.println("You completed all eight rounds!");
  flashFeedback(523, 180);
  flashFeedback(659, 180);
  flashFeedback(784, 500);
}

// Reset the round progress and require a fresh press after all buttons release
void waitForNewGame() {
  setAllLeds(LOW);
  noTone(buzzerPin);
  currentLen = 0;
  answerPosition = 0;
  gameState = waitingState;
  requireButtonRelease();
  Serial.println("Press any button to start");
}

// Start a new game with one random sequence item
void startGame() {
  currentLen = 1;
  answerPosition = 0;
  // random(count) gives a color index from 0 through 3; colors can repeat
  sequenceArr[0] = random(count);
  requireButtonRelease();
  Serial.println("Listening");
  delay(500);
  gameState = playbackState;
}

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < count; i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW); 
    // Released reads HIGH; pressing the button connects this input to GND (LOW)
    pinMode(buttons[i], INPUT_PULLUP);
  }
  pinMode(buzzerPin, OUTPUT);
  noTone(buzzerPin);

  // Leave A0 unconnected and use its reading to seed the random number generator
  // This does not guarantee a different sequence after every reset
  randomSeed(analogRead(A0));
  waitForNewGame();
}

void loop() {
  if (gameState == waitingState) {
    if (readNewButtonPress() != -1) {
      startGame();
    }
    return; // The start press is not an answer
  }

  // Finish showing the sequence before checking answers, then require button release
  if (gameState == playbackState) {
    playSequence();
    answerPosition = 0;
    requireButtonRelease();
    answerWaitStarted = millis();
    gameState = playerInputState;
    return;
  }

  // Only answer input has a time limit; playback and feedback do not
  // Unsigned subtraction still works when the millis() clock wraps back to zero
  if (millis() - answerWaitStarted >= answerTimeoutMS) {
    Serial.println("Time limit exceeded");
    failureFeedback();
    waitForNewGame();
    return;
  }

  int choice = readNewButtonPress();
  if (choice == -1) {
    return;
  }
  playChoice(choice, responseMS);
  requireButtonRelease();

  // A wrong answer ends the current game
  if (choice != sequenceArr[answerPosition]) {
    Serial.println("Wrong choice");
    failureFeedback();
    waitForNewGame();
    return;
  }

  answerPosition++;
  answerWaitStarted = millis(); // Each correct answer starts a fresh five seconds
  if (answerPosition < currentLen) {
    return; // More answers are needed to complete this round
  }

  // Win at eight items before trying to add another item to the array
  if (currentLen == maxSequenceLength) {
    victoryFeedback();
    waitForNewGame();
    return; // Never write a ninth item into the eight-element array
  }
  roundSuccessFeedback();
  // Keep the earlier items and append one new choice for the next round
  sequenceArr[currentLen] = random(count);
  currentLen++;
  answerPosition = 0;
  requireButtonRelease();
  delay(500);
  gameState = playbackState;
}
