#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // Defines the LCD
int trigPin = 10;                      // Ultrasonic sensor trigger pin
int echoPin = 9;                       // Ultrasonic sensor echo pin
int buzzerPin = 6;
// We're now defining our variables in the processing operation
int distance, previousDistance, state, previousState, count, countIn, countOut;
int minDistance = 100; // The minimum distance from the sensor at which it starts to count
int maxDistance = 150; // The maximum distance from the sensor at which it counts
long duration;         // The duration of the echo receiving time
void setup()
{
  // Initializes our components + the serial monitor
  lcd.begin(16, 2);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  // This stores the previous values for state and distance
  previousState = state;
  previousDistance = distance;

  /* This uses the ultrasonic sensor to detect the object's distance
  by the use of the constant speed of sound and duration for the trave;
  of the ultrasonic waves */
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.0343 / 2;

  // The main processing for computing the state of the object
  // The object has a state of 1 if and only if it's in the distance range and the distance is decreasing (Person coming in)
  // The object has a state of -1 if and only if it's in the distance range and the distance is increasing (Person going out)
  // The object has a state of 0 if it's outside the distance range or the speed is very low (to reduce noise effects on reads)
  if ((distance < previousDistance) & ((minDistance < distance) & (distance < maxDistance)))
  {
    state = 1;
  }
  if ((distance > previousDistance) & ((minDistance < distance) & (distance < maxDistance)))
  {
    state = -1;
  }
  if ((abs(distance - previousDistance) < 1.5) || (minDistance > distance) || (distance > maxDistance))
  {
    state = 0; // The (abs) condition is there to neglect noise that might change the state by accident
  }

  // When the state changes from 0 to 1 or -1 we add the state to the total count (1 if coming in, and -1 if going out)
  if ((previousState != state) & (minDistance < distance) & (distance < maxDistance))
  {
    count += state;
  }

  // Prints the count value onto the sensor
  lcd.clear();
  lcd.print("people inside: ");
  lcd.setCursor(0, 1);
  lcd.print(count);

  // Checks whether the buzzer must start to ring or not
  if (count >= 5)
  {
    tone(buzzerPin, 1000);
  }
  else
  {
    noTone(buzzerPin);
  }

  delay(10); // delay is for simulation only
}
