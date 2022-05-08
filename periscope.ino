int ldrPin = A1;
int ledPins[] = {1, 3, 5};
int intensity;
const MIN_INTENSITY = 100;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  int arrLen = sizeof ledPins / sizeof ledPins[0];
  for (int i = 0; i < arrLen; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
}

//Method used to turn on/off all leds
void setLeds(int value) {
  int arrLen = sizeof ledPins / sizeof ledPins[0];
  for (int i = 0; i < arrLen; i++) {
    digitalWrite(ledPins[i], value);
  }
}


void loop() {
  // put your main code here, to run repeatedly:
  intensity = analogRead(ldrPin);
  Serial.println(intensityura);
  delay(300);
  if (intensity < MIN_INTENSITY) {
    setLeds(HIGH);
  } else {
    setLeds(LOW);
  }
}
