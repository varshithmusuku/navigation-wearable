/*
  =====================================================================
  Offline Navigation Wearable for the Visually Impaired
  ---------------------------------------------------------------------
  Platform   : ESP32 (Dev Module)
  Sensors    : 3x HC-SR04 Ultrasonic Sensors (Front, Left, Right)
  Actuators  : 3x Coin Vibration Motors (via NPN transistor drivers)
  Extras     : 1x Tactile Push Button (sensitivity / mode toggle)
             : 1x Piezo Buzzer (optional audible alert for close range)

  Concept    : User-First Feedback Loop (UFFL)
  ---------------------------------------------------------------------
  Instead of a fixed alert threshold, the device continuously adapts
  its vibration intensity and alert distance based on:
    1. Real-time obstacle distance (closer = stronger/faster pulses)
    2. The user's own walking cadence (estimated from how often they
       trigger "close" events) so the feedback doesn't overwhelm a
       slow-moving user or under-alert a fast-moving one
    3. A manual sensitivity dial (button press cycles through 3 modes:
       Indoor / Outdoor / Crowded) so the user stays in control of
       the assistive behavior rather than the device dictating it

  This sketch is fully offline: no WiFi/BLE dependency required for
  core obstacle-avoidance functionality, matching the "low-cost,
  offline" design goal.

  v1.1 changes vs original_tested.ino (everything else is unchanged):
    1. Mode button: one mode change per press (was: repeated while held)
    2. UFFL: a "close event" is counted once when an obstacle ENTERS the
       danger zone (was: counted on every loop iteration, per sensor,
       which pinned adaptiveGain at 0.75 while any obstacle stayed close)
    3. Optional CSV logging (LOG_CSV) for scripts/plot_uffl.py
  In the Wokwi simulation the three LEDs stand in for the vibration motors.
  =====================================================================
*/

// Set to 1 to print CSV (ms,mode,front,left,right,close_event,gain) instead of text.
#define LOG_CSV 0

// ---------------------- Pin Configuration ---------------------------
const int TRIG_FRONT = 5,  ECHO_FRONT = 18;
const int TRIG_LEFT  = 19, ECHO_LEFT  = 21;
const int TRIG_RIGHT = 22, ECHO_RIGHT = 23;

const int MOTOR_FRONT = 25;
const int MOTOR_LEFT  = 26;
const int MOTOR_RIGHT = 27;

const int BUZZER_PIN  = 32;
const int MODE_BUTTON = 33;

// ---------------------- UFFL Tunable State ---------------------------
enum FeedbackMode { INDOOR, OUTDOOR, CROWDED };
FeedbackMode currentMode = INDOOR;

// Distance thresholds (cm) per mode -- tighter indoors, wider outdoors
struct ModeProfile {
  int cautionCm;   // start gentle pulsing
  int dangerCm;    // strong continuous vibration + buzzer
};
ModeProfile profiles[3] = {
  {80, 30},   // INDOOR   - tighter spaces, shorter warning distance
  {150, 60},  // OUTDOOR  - open spaces, earlier warning
  {60, 25}    // CROWDED  - dense obstacles, avoid alert fatigue
};

// Adaptive cadence tracking for the "user-first" part of UFFL
unsigned long lastCloseEventTime = 0;
unsigned long closeEventIntervals[5] = {0};
int intervalIndex = 0;
float adaptiveGain = 1.0; // scales vibration intensity based on user pace

// Debounce state for mode button
int lastButtonState = HIGH;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;
int stableButtonState = HIGH;

// Close-event edge detection for UFFL
bool wasClose = false;

void setup() {
  Serial.begin(115200);

  pinMode(TRIG_FRONT, OUTPUT); pinMode(ECHO_FRONT, INPUT);
  pinMode(TRIG_LEFT,  OUTPUT); pinMode(ECHO_LEFT,  INPUT);
  pinMode(TRIG_RIGHT, OUTPUT); pinMode(ECHO_RIGHT, INPUT);

  pinMode(MOTOR_FRONT, OUTPUT);
  pinMode(MOTOR_LEFT,  OUTPUT);
  pinMode(MOTOR_RIGHT, OUTPUT);

  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(MODE_BUTTON, INPUT_PULLUP);

#if LOG_CSV
  Serial.println("ms,mode,front,left,right,close_event,gain");
#else
  Serial.println("Navigation Wearable Initialized - Mode: INDOOR");
#endif
}

// ---------------------- Sensor Helpers ---------------------------
long readDistanceCm(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000); // 30ms timeout ~5m range
  if (duration == 0) return -1; // no echo / out of range
  return duration * 0.0343 / 2; // convert to cm
}

// ---------------------- UFFL Core Logic ---------------------------
void updateAdaptiveGain() {
  // Average recent time-between-close-events; faster events -> user
  // moving briskly through obstacles -> slightly reduce gain so
  // feedback doesn't feel spammy. Slower events -> boost gain so
  // a cautious/slow user still gets a clear, confident signal.
  unsigned long sum = 0;
  int count = 0;
  for (int i = 0; i < 5; i++) {
    if (closeEventIntervals[i] > 0) { sum += closeEventIntervals[i]; count++; }
  }
  if (count == 0) { adaptiveGain = 1.0; return; }

  float avgInterval = (float)sum / count;
  if (avgInterval < 800)      adaptiveGain = 0.75; // rapid events
  else if (avgInterval > 3000) adaptiveGain = 1.25; // sparse events
  else                          adaptiveGain = 1.0;
}

void recordCloseEvent() {
  unsigned long now = millis();
  if (lastCloseEventTime > 0) {
    closeEventIntervals[intervalIndex] = now - lastCloseEventTime;
    intervalIndex = (intervalIndex + 1) % 5;
  }
  lastCloseEventTime = now;
  updateAdaptiveGain();
}

// Drives a motor with PWM strength; strength scaled by adaptiveGain
void driveFeedback(int motorPin, long distance, ModeProfile profile) {
  if (distance < 0 || distance > profile.cautionCm) {
    analogWrite(motorPin, 0);
    return;
  }

  if (distance <= profile.dangerCm) {
    analogWrite(motorPin, constrain((int)(255 * adaptiveGain), 0, 255));
  } else {
    // Linear ramp between caution and danger distance
    float ratio = 1.0 - ((float)(distance - profile.dangerCm) /
                          (profile.cautionCm - profile.dangerCm));
    int strength = constrain((int)(180 * ratio * adaptiveGain), 40, 255);
    analogWrite(motorPin, strength);
  }
}

const char* modeName() {
  return currentMode == INDOOR ? "INDOOR" : currentMode == OUTDOOR ? "OUTDOOR" : "CROWDED";
}

void handleModeButton() {
  int reading = digitalRead(MODE_BUTTON);
  if (reading != lastButtonState) lastDebounceTime = millis();

  // Act only when the debounced state CHANGES to pressed -> one switch per press
  if ((millis() - lastDebounceTime) > debounceDelay && reading != stableButtonState) {
    stableButtonState = reading;
    if (stableButtonState == LOW) {
      currentMode = (FeedbackMode)((currentMode + 1) % 3);
      Serial.print("Mode switched to: ");
      Serial.println(modeName());
    }
  }
  lastButtonState = reading;
}

void loop() {
  handleModeButton();
  ModeProfile profile = profiles[currentMode];

  long dFront = readDistanceCm(TRIG_FRONT, ECHO_FRONT);
  long dLeft  = readDistanceCm(TRIG_LEFT,  ECHO_LEFT);
  long dRight = readDistanceCm(TRIG_RIGHT, ECHO_RIGHT);

  // UFFL: one close event each time any sensor enters the danger zone
  bool closeNow = (dFront >= 0 && dFront <= profile.dangerCm) ||
                  (dLeft  >= 0 && dLeft  <= profile.dangerCm) ||
                  (dRight >= 0 && dRight <= profile.dangerCm);
  if (closeNow && !wasClose) recordCloseEvent();
  wasClose = closeNow;

  driveFeedback(MOTOR_FRONT, dFront, profile);
  driveFeedback(MOTOR_LEFT,  dLeft,  profile);
  driveFeedback(MOTOR_RIGHT, dRight, profile);

  // Audible alert only for true "danger" front obstacles, to avoid
  // over-relying on sound (many visually impaired users depend on
  // ambient audio cues for navigation, so this stays minimal).
  if (dFront > 0 && dFront <= profile.dangerCm) {
    tone(BUZZER_PIN, 2000, 100);
  }

#if LOG_CSV
  Serial.print(millis());  Serial.print(",");
  Serial.print(modeName()); Serial.print(",");
  Serial.print(dFront);    Serial.print(",");
  Serial.print(dLeft);     Serial.print(",");
  Serial.print(dRight);    Serial.print(",");
  Serial.print(closeNow ? 1 : 0); Serial.print(",");
  Serial.println(adaptiveGain);
#endif

  delay(60); // ~16Hz sensing loop, quick enough for walking pace
}
