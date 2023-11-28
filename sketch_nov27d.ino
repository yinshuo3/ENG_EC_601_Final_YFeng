#define TRIGGER_PINL 9
#define ECHO_PINL 10

#define TRIGGER_PINM 6
#define ECHO_PINM 7

#define TRIGGER_PINR 2
#define ECHO_PINR 3
// defines variables
// 2nd: Depth Mode, L and R for wall, M for crack, crack depth = M - average(L + R)
// do 5 measures, 0.1s each. 
long durationL, durationM, durationR;
float distanceL, distanceM, distanceR;
int count_measures = 0;

//distance can't > 40cm
int max_distance = 400;

//too close, move further
int min_distance = 50;

//another five measures
float average_depth_width = 0.0;

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
  /*Serial.print("Distance Left: ");
  Serial.print(distanceL);
  Serial.println(" mm");*/

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
  /*Serial.print("Distance Middle: ");
  Serial.print(distanceM);
  Serial.println(" mm");*/

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
  /*Serial.print("Distance Right: ");
  Serial.print(distanceR);
  Serial.println(" mm");*/

  //5mm for crack, 10mm/1cm for serious crack. 
  //skip unreasonable data
  if (distanceL < max_distance && distanceM < max_distance && distanceR < max_distance && distanceL > min_distance && distanceM > min_distance && distanceR > min_distance) {
    // what if L or R run into obstacles?
    float averageLR = (distanceL + distanceR) / 2.0;

    if (distanceM > averageLR + 5.0) {
      count_measures += 1;
    } else {
      count_measures = 0;
    }

    if (distanceM > averageLR + 5.0 && count_measures > 4) {
      average_depth_width += (distanceM - averageLR);
    } else {
      average_depth_width = 0.0;
      //count_measures = 0;
     }

    if (distanceM > averageLR + 5.0 && count_measures > 9) {
      average_depth_width = average_depth_width / 5.0;
      Serial.println("crack detected!");
      Serial.print("Depth is: ");
      Serial.print(average_depth_width);
      Serial.println(" mm");
    
      count_measures = 0;
      average_depth_width = 0.0;
    }

  }

  
  //delay 0.1s
  delay(10);
}