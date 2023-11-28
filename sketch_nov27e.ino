//scanner mode, move left, does work, need more polish
#define TRIGGER_PINL 9
#define ECHO_PINL 10

#define TRIGGER_PINM 6
#define ECHO_PINM 7

#define TRIGGER_PINR 2
#define ECHO_PINR 3
// defines variables
// 1st: Scanner Move left / right across the crack, then left -> middle -> right has detection spike for move left, move right opposite.
// implement move left first. 
long durationL, durationM, durationR;
float distanceL, distanceM, distanceR;

//try measure 3 times
//no, maybe 5 times as focus mode
int count_measures = 0;

//distance can't > 50cm
int max_distance = 400;

//difference to be considered as crack
// 5.0 is too small to tolerate sensor errors, try 10mm
float crack_difference = 10.0;

//too close, move further
int min_distance = 50;

//status code, 0 for nothing, 1 for L, 2 for M, 3 for R
int status_code = 0;
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

//do a time measurement for the average length of 3 measures
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
    
    //for move left, L -> M -> R
    //first check L
    if (status_code == 0) {
      float averageMR = (distanceM + distanceR) / 2.0;

      if (distanceL > averageMR + crack_difference) {
        count_measures += 1;
      } else {
        count_measures = 0;
      }

      if (count_measures > 4) {
        status_code = 1;
        count_measures = 0;
      }
    }

    //second check M
    if (status_code == 1) {
      float averageLR = (distanceL + distanceR) / 2.0;

      if (distanceM > averageLR + crack_difference) {
        count_measures += 1;
      } else {
        count_measures = 0;
      }

      if (count_measures > 4) {
        status_code = 2;
        count_measures = 0;
      }
    }
    
    //third check R
    if (status_code == 2) {
      float averageLM = (distanceL + distanceM) / 2.0;

      if (distanceR > averageLM + crack_difference) {
        count_measures += 1;
      } else {
        count_measures = 0;
      }

      if (count_measures > 4) {
        status_code = 3;
        count_measures = 0;
      }
    }

    //find crack
    //the measurement is NOT accurate enough. Use focus mode instead
    if (status_code == 3) {
      
      Serial.println("crack detected!");
      //Serial.print("Depth is: ");
      //Serial.print(average_depth_width);
      //Serial.println(" mm");
    
      count_measures = 0;
      status_code = 0;
    }

  }

  
  //try no delay, because move is fast
  //delay(10);
}