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
const int buttons[count] = {2,3,4,5}; // buttons 2-5 
const  int toneFrequencies[count] = {262, 330, 392, 523}; // vals are hz for buzzer 
const int maxSequenceLength = 8; 
const int buzzerPin = 6;
const int responseMS = 160;
const int playbackMS = 500;
const int playbackGapMS = 250;
int sequenceArr[maxSequenceLength] = {};
int answerPosition = 0; // position in the sequence that the players next button press must match
int currentLen = 0;
const int waitingState = 0;
const int playbackState = 1;
const int playerInputState = 2;
int gameState = waitingState;
const int debounceMS = 25; // waits until the button reading stops changing for 25 ms before accepting input
int lastButtonReadings[count] = {HIGH, HIGH, HIGH, HIGH};

// millis() timestamps need unsigned long; Uno's int only reaches 32767
// Keeping the full unsigned timestamp also allows subtraction across rollover
unsigned long lastButtonChange = 0;

int readyForPress = 0; // 1 allows a new press; 0 requires all buttons to be released first
const int answerTimeoutMS = 5000; // max allowed time for each next answer
unsigned long answerWaitStarted = 0; // unsigned long matches the type returned by millis()

// Play one colors LED and matching tone for durationMS milliseconds
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

// Require a fresh release after playback or feedback
// A button held through either display cannot become an answer afterward
void requireButtonRelease() {
  readyForPress = 0;
  for (int i = 0; i < count; i++) {
    lastButtonReadings[i] = digitalRead(buttons[i]);
  }
  lastButtonChange = millis();
}

// Return one new color choice (0-3), or -1 if no press is ready
// Mechanical contacts can flicker briefly, the stability check filters this bounce
int readNewButtonPress() {
  const unsigned long now = millis();
  int pressedCount = 0;
  int choice = -1;

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

  // Reject multiple buttons until every button has been released
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
  readyForPress = 0; // Holding this button cannot produce another event
  return choice;
}

void setAllLeds(int state) {
  for (int i = 0; i < count; i++) {
    digitalWrite(ledPins[i], state);
  }
}

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
  flashFeedback(784, 120); // first val is tone freq, second is light / sound duration in ms
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
    pinMode(buttons[i], INPUT_PULLUP);
  }
  pinMode(buzzerPin, OUTPUT);
  noTone(buzzerPin);

  // Seed randomness once here using an unconnected A0 reading;
  // that does not guarantee a different sequence after every reset
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

  // Playback blocks answer checking; held buttons must be released afterward
  if (gameState == playbackState) {
    playSequence();
    answerPosition = 0;
    requireButtonRelease();
    answerWaitStarted = millis();
    gameState = playerInputState;
    return;
  }

  // Only answer input has a time limit; playback and feedback do not
  // Unsigned subtraction handles rollover of the millis() counter
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

  // A wrong answer ends the game instantly
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

  // Check for final victory before appending to the array
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
