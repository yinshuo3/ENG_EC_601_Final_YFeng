#define TRIGGER_PINL 9
#define ECHO_PINL 10

#define TRIGGER_PINM 6
#define ECHO_PINM 7

#define TRIGGER_PINR 2
#define ECHO_PINR 3
// defines variables
long durationL, durationM, durationR;
float distanceL, distanceM, distanceR;
void setup() {
  pinMode(TRIGGER_PINL, OUTPUT); // Sets the trigPin as an Output
  pinMode(ECHO_PINL, INPUT); // Sets the echoPin as an Input

  pinMode(TRIGGER_PINM, OUTPUT); // Sets the trigPin as an Output
  pinMode(ECHO_PINM, INPUT); // Sets the echoPin as an Input

  pinMode(TRIGGER_PINR, OUTPUT); // Sets the trigPin as an Output
  pinMode(ECHO_PINR, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600); // Starts the serial communication
}
void loop() {
  // Clears the trigPin Left
  digitalWrite(TRIGGER_PINL, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(TRIGGER_PINL, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PINL, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  durationL = pulseIn(ECHO_PINL, HIGH);
  // Calculating the distance
  distanceL = durationL * 0.34 / 2.0;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance Left: ");
  Serial.print(distanceL);
  Serial.println(" mm");

  //middle
  digitalWrite(TRIGGER_PINM, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(TRIGGER_PINM, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PINM, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  durationM = pulseIn(ECHO_PINM, HIGH);
  // Calculating the distance
  distanceM = durationM * 0.34 / 2.0;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance Middle: ");
  Serial.print(distanceM);
  Serial.println(" mm");

  //right
  digitalWrite(TRIGGER_PINR, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(TRIGGER_PINR, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PINR, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  durationR = pulseIn(ECHO_PINR, HIGH);
  // Calculating the distance
  distanceR = durationR * 0.34 / 2.0;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance Right: ");
  Serial.print(distanceR);
  Serial.println(" mm");

  delay(500);
}
