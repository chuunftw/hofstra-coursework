#include <Arduino.h>

const int CHOICE_COUNT = 4;
const int MAX_SEQUENCE_LENGTH = 8;
const int LED_PINS[CHOICE_COUNT] = {8, 9, 10, 11};
const int BUTTON_PINS[CHOICE_COUNT] = {2, 3, 4, 5};
const int TONE_FREQUENCIES[CHOICE_COUNT] = {262, 330, 392, 523};
const int BUZZER_PIN = 6;
const int DEBOUNCE_MS = 25;
const int PLAYBACK_MS = 500;
const int PLAYBACK_GAP_MS = 250;
const int RESPONSE_MS = 160;
// Time allowed for each next answer, excluding playback and answer feedback.
const int ANSWER_TIMEOUT_MS = 5000;

// Delays are used only while displaying lights/sounds. Input is polled between
// displays. The answer timer is checked while waiting for player input.
// Named integer values describe what the game is currently doing.
const int WAITING = 0;
const int PLAYBACK = 1;
const int PLAYER_INPUT = 2;
int gameState = WAITING;
int correctSequence[MAX_SEQUENCE_LENGTH] = {};
int sequenceLength = 0;
int answerPosition = 0;
// millis() returns an unsigned long. On Uno, int only reaches 32767, so it
// cannot hold running timestamps. Unsigned subtraction also handles rollover.
unsigned long answerWaitStarted = 0;

// Remember each button's previous reading using an ordinary integer array.
int lastButtonReadings[CHOICE_COUNT] = {HIGH, HIGH, HIGH, HIGH};
// This is also a millis() timestamp, so it needs unsigned long.
unsigned long lastButtonChange = 0;
// readyForPress: 1 allows a new press; 0 requires all buttons to be released first.
int readyForPress = 0;

// Force a stable release before input can count again. This prevents a press
// held through start, playback, or feedback from becoming an answer/restart.
void requireButtonRelease() {
  readyForPress = 0;
  for (int i = 0; i < CHOICE_COUNT; i++) {
    lastButtonReadings[i] = digitalRead(BUTTON_PINS[i]);
  }
  lastButtonChange = millis();
}

// Return exactly one new choice (0..3), or -1 when no press is ready.
// Both release and press must stay stable for 25 ms to reject contact bounce.
int readNewButtonPress() {
  // Keep the full millis() timestamp; an int would overflow too soon on Uno.
  const unsigned long now = millis();

  int pressedCount = 0;
  int choice = -1;
  for (int i = 0; i < CHOICE_COUNT; i++) {
    int reading = digitalRead(BUTTON_PINS[i]);
    // Any change restarts the time needed for the buttons to become stable.
    if (reading != lastButtonReadings[i]) {
      lastButtonReadings[i] = reading;
      lastButtonChange = now;
    }
    // INPUT_PULLUP makes a pressed button read LOW.
    if (reading == LOW) {
      pressedCount++;
      choice = i;
    }
  }

  // Reject simultaneous presses immediately, even if one is released first.
  // All buttons must be released before another single press is accepted.
  if (pressedCount > 1) {
    readyForPress = 0;
    return -1;
  }

  // Unsigned subtraction also works when the millis() counter wraps around.
  if (now - lastButtonChange < DEBOUNCE_MS) {
    return -1;
  }
  if (pressedCount == 0) {
    readyForPress = 1;
    return -1;
  }
  if (readyForPress == 0) {
    return -1;
  }

  readyForPress = 0; // A held button produces only one event.
  return choice;
}

// Pass HIGH to turn all LEDs on, or LOW to turn them off.
void setAllLeds(int state) {
  for (int i = 0; i < CHOICE_COUNT; i++) {
    if (state == HIGH) {
      digitalWrite(LED_PINS[i], HIGH);
    } else {
      digitalWrite(LED_PINS[i], LOW);
    }
  }
}

// One game item is one LED plus its matching tone, shown together.
void playChoice(int choice, int durationMs) {
  digitalWrite(LED_PINS[choice], HIGH);
  tone(BUZZER_PIN, TONE_FREQUENCIES[choice]);
  delay(durationMs);
  noTone(BUZZER_PIN);
  digitalWrite(LED_PINS[choice], LOW);
}

void playSequence() {
  Serial.print("Round length: ");
  Serial.println(sequenceLength);
  for (int i = 0; i < sequenceLength; i++) {
    playChoice(correctSequence[i], PLAYBACK_MS);
    // This dark, silent gap makes repeated colors distinguishable.
    delay(PLAYBACK_GAP_MS);
  }
  Serial.println("Your turn.");
}

// Reuse the four game LEDs as status LEDs; no extra LEDs are required.
void flashFeedback(int frequency, int durationMs) {
  setAllLeds(HIGH);
  tone(BUZZER_PIN, frequency);
  delay(durationMs);
  noTone(BUZZER_PIN);
  setAllLeds(LOW);
  delay(120);
}

void roundSuccessFeedback() {
  Serial.println("Correct round!");
  flashFeedback(659, 120);
  flashFeedback(784, 120);
}

void failureFeedback() {
  Serial.println("Game over.");
  flashFeedback(196, 300);
  flashFeedback(131, 400);
}

void victoryFeedback() {
  Serial.println("You completed all eight rounds!");
  // Three rising notes and a longer finish distinguish victory from a round.
  flashFeedback(523, 180);
  flashFeedback(659, 180);
  flashFeedback(784, 500);
}

void waitForNewGame() {
  setAllLeds(LOW);
  noTone(BUZZER_PIN);
  sequenceLength = 0;
  answerPosition = 0;
  gameState = WAITING;
  requireButtonRelease();
  Serial.println("Release buttons, then press any one to start.");
}

void startGame() {
  // Only the first sequence entry is needed initially. Later rounds append
  // one new entry; stale entries from an earlier game are never read.
  sequenceLength = 1;
  answerPosition = 0;
  correctSequence[0] = random(CHOICE_COUNT); // Upper bound excluded: 0..3.
  requireButtonRelease();
  Serial.println("Watch and listen...");
  delay(500); // Give the player time to release the start button.
  gameState = PLAYBACK;
}

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < CHOICE_COUNT; i++) {
    pinMode(LED_PINS[i], OUTPUT);
    digitalWrite(LED_PINS[i], LOW);
    // Each button connects its input pin to GND when pressed.
    pinMode(BUTTON_PINS[i], INPUT_PULLUP);
  }
  pinMode(BUZZER_PIN, OUTPUT);
  // Leave A0 unconnected. Its reading varies, but does not guarantee a unique
  // sequence at every reset; this is adequate for a simple classroom game.
  randomSeed(analogRead(A0));
  waitForNewGame();
}

void loop() {
  if (gameState == WAITING) {
    if (readNewButtonPress() != -1) {
      startGame();
    }
    return; // The start press is never compared with the sequence.
  }

  if (gameState == PLAYBACK) {
    playSequence();
    answerPosition = 0;
    requireButtonRelease();
    // Begin the five-second thinking period only after playback finishes.
    answerWaitStarted = millis();
    gameState = PLAYER_INPUT;
    return;
  }

  // Unsigned subtraction keeps this check valid across millis() rollover.
  if (millis() - answerWaitStarted >= ANSWER_TIMEOUT_MS) {
    Serial.println("Time limit exceeded.");
    failureFeedback();
    waitForNewGame();
    return;
  }

  const int choice = readNewButtonPress();
  if (choice == -1) {
    return;
  }
  playChoice(choice, RESPONSE_MS);

  // Check each accepted press immediately, rather than storing a second array.
  if (choice != correctSequence[answerPosition]) {
    Serial.println("Wrong choice.");
    failureFeedback();
    waitForNewGame();
    return;
  }

  answerPosition++;
  // A correct answer gives the player a fresh five seconds for the next one.
  answerWaitStarted = millis();
  if (answerPosition < sequenceLength) {
    return; // More answers are still needed for this round.
  }

  if (sequenceLength == MAX_SEQUENCE_LENGTH) {
    victoryFeedback();
    waitForNewGame();
    return; // Never append a ninth item to the eight-element array.
  }

  roundSuccessFeedback();
  correctSequence[sequenceLength] = random(CHOICE_COUNT);
  sequenceLength++;
  answerPosition = 0;
  requireButtonRelease();
  delay(500);
  gameState = PLAYBACK;
}
