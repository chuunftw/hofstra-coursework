#include <Arduino.h>

// Completed study reference. Write your own version in the parent src/main.cpp.
// Each array uses the same order: red, blue, green, yellow.
const int CHOICE_COUNT = 4;
const int MAX_SEQUENCE_LENGTH = 4;
const int LED_PINS[CHOICE_COUNT] = {8, 9, 10, 11};
const int BUTTON_PINS[CHOICE_COUNT] = {2, 3, 4, 5};
const unsigned int TONE_FREQUENCIES[CHOICE_COUNT] = {262, 330, 392, 523};
const int BUZZER_PIN = 6;
const unsigned long DEBOUNCE_MS = 25;
const unsigned long PLAYBACK_MS = 500;
const unsigned long PLAYBACK_GAP_MS = 250;
const unsigned long RESPONSE_MS = 160;

// Delays are used only while displaying lights/sounds. Input is polled between
// displays; there is no timer limiting how long the player can think.
enum GameState { WAITING, PLAYBACK, PLAYER_INPUT };
GameState gameState = WAITING;
int correctSequence[MAX_SEQUENCE_LENGTH] = {};
int sequenceLength = 0;
int answerPosition = 0;

// Button debouncing remembers the whole set of pressed buttons. A mask uses
// one binary bit per button: 0001 = red, 0010 = blue, 0011 = both.
unsigned int lastButtonMask = 0;
unsigned long lastButtonChange = 0;
bool buttonsArmed = false;

// Return the currently pressed buttons. INPUT_PULLUP makes a press read LOW.
unsigned int readButtonMask() {
  unsigned int mask = 0;
  for (int i = 0; i < CHOICE_COUNT; i++) {
    if (digitalRead(BUTTON_PINS[i]) == LOW) {
      mask |= (1U << i);
    }
  }
  return mask;
}

// Force a stable release before input can count again. This prevents a press
// held through start, playback, or feedback from becoming an answer/restart.
void requireButtonRelease() {
  buttonsArmed = false;
  lastButtonMask = readButtonMask();
  lastButtonChange = millis();
}

// Return exactly one new choice (0..3), or -1 when no press is ready.
// Both release and press must stay stable for 25 ms to reject contact bounce.
int readNewButtonPress() {
  const unsigned int mask = readButtonMask();
  const unsigned long now = millis();

  if (mask != lastButtonMask) {
    lastButtonMask = mask;
    lastButtonChange = now;
  }

  int pressedCount = 0;
  int choice = -1;
  for (int i = 0; i < CHOICE_COUNT; i++) {
    if ((mask & (1U << i)) != 0) {
      pressedCount++;
      choice = i;
    }
  }

  // Reject simultaneous presses immediately, even if one is released first.
  // All buttons must be released before another single press is accepted.
  if (pressedCount > 1) {
    buttonsArmed = false;
    return -1;
  }

  // Unsigned subtraction also works when the millis() counter wraps around.
  if (now - lastButtonChange < DEBOUNCE_MS) {
    return -1;
  }
  if (pressedCount == 0) {
    buttonsArmed = true;
    return -1;
  }
  if (!buttonsArmed) {
    return -1;
  }

  buttonsArmed = false; // A held button produces only one event.
  return choice;
}

void setAllLeds(bool on) {
  for (int i = 0; i < CHOICE_COUNT; i++) {
    digitalWrite(LED_PINS[i], on ? HIGH : LOW);
  }
}

// One game item is one LED plus its matching tone, shown together.
void playChoice(int choice, unsigned long durationMs) {
  digitalWrite(LED_PINS[choice], HIGH);
  tone(BUZZER_PIN, TONE_FREQUENCIES[choice]);
  delay(durationMs);
  noTone(BUZZER_PIN);
  digitalWrite(LED_PINS[choice], LOW);
}

void playSequence() {
  Serial.print(F("Round length: "));
  Serial.println(sequenceLength);
  for (int i = 0; i < sequenceLength; i++) {
    playChoice(correctSequence[i], PLAYBACK_MS);
    // This dark, silent gap makes repeated colors distinguishable.
    delay(PLAYBACK_GAP_MS);
  }
  Serial.println(F("Your turn."));
}

// Reuse the four game LEDs as status LEDs; no extra LEDs are required.
void flashFeedback(unsigned int frequency, unsigned long durationMs) {
  setAllLeds(true);
  tone(BUZZER_PIN, frequency);
  delay(durationMs);
  noTone(BUZZER_PIN);
  setAllLeds(false);
  delay(120);
}

void roundSuccessFeedback() {
  Serial.println(F("Correct round!"));
  flashFeedback(659, 120);
  flashFeedback(784, 120);
}

void failureFeedback() {
  Serial.println(F("Wrong choice. Game over."));
  flashFeedback(196, 300);
  flashFeedback(131, 400);
}

void victoryFeedback() {
  Serial.println(F("You completed all four rounds!"));
  // Three rising notes and a longer finish distinguish victory from a round.
  flashFeedback(523, 180);
  flashFeedback(659, 180);
  flashFeedback(784, 500);
}

void waitForNewGame() {
  setAllLeds(false);
  noTone(BUZZER_PIN);
  sequenceLength = 0;
  answerPosition = 0;
  gameState = WAITING;
  requireButtonRelease();
  Serial.println(F("Release buttons, then press any one to start."));
}

void startGame() {
  // Only the first sequence entry is needed initially. Later rounds append
  // one new entry; stale entries from an earlier game are never read.
  sequenceLength = 1;
  answerPosition = 0;
  correctSequence[0] = random(CHOICE_COUNT); // Upper bound excluded: 0..3.
  requireButtonRelease();
  Serial.println(F("Watch and listen..."));
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
    gameState = PLAYER_INPUT;
    return;
  }

  const int choice = readNewButtonPress();
  if (choice == -1) {
    return;
  }
  playChoice(choice, RESPONSE_MS);

  // Check each accepted press immediately, rather than storing a second array.
  if (choice != correctSequence[answerPosition]) {
    failureFeedback();
    waitForNewGame();
    return;
  }

  answerPosition++;
  if (answerPosition < sequenceLength) {
    return; // More answers are still needed for this round.
  }

  if (sequenceLength == MAX_SEQUENCE_LENGTH) {
    victoryFeedback();
    waitForNewGame();
    return; // Never append a fifth item to the four-element array.
  }

  roundSuccessFeedback();
  correctSequence[sequenceLength] = random(CHOICE_COUNT);
  sequenceLength++;
  answerPosition = 0;
  requireButtonRelease();
  delay(500);
  gameState = PLAYBACK;
}
