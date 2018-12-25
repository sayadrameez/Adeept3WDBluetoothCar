int trigPin = 10;                  // define Trig pin for ultrasonic ranging module
int echoPin = 11;                  // define Echo pin for ultrasonic ranging module
const int buzzerPin = 3;  // define pin for buzzer

float maxDistance = 200;           // define the range(cm) for ultrasonic ranging module, Maximum sensor distance is rated at 400-500cm.
float soundVelocity = 340;         // Sound velocity = 340 m/s
float rangingTimeOut = 2 * maxDistance / 100 / soundVelocity * 1000000; // define the timeout(ms) for ultrasonic ranging module

void setup() {
  // put your setup code here, to run once:
  pinMode(buzzerPin, OUTPUT); // set buzzerPin to output mode
  Serial.begin(9600); // initialize serial port
    pinMode(trigPin, OUTPUT); // set trigPin to output mode
  pinMode(echoPin, INPUT);  // set echoPin to input mode
}

void loop() {
 byte barDistance = maxDistance; // save the minimum measured distance from obstacles
      byte barDegree;                 // save the minimum measured angel from obstacles
      byte distance;                  // save the current the measured distance from obstacles
  
  // put your main code here, to run repeatedly:
  float dist = getDistance();
   if(dist<20){ 
      tone(buzzerPin, 2000); 
     }else
     {
      noTone(buzzerPin);
     }
     Serial.println(dist);
     delay(500);
 }
 


float getDistance() {
  unsigned long pingTime; // save the high level time returned by ultrasonic ranging module
  float distance;         // save the distance away from obstacle

  // set the trigPin output 10us high level to make the ultrasonic ranging module start to measure
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // get the high level time returned by ultrasonic ranging module
  pingTime = pulseIn(echoPin, HIGH, rangingTimeOut);

  if (pingTime != 0) {  // if the measure is not overtime
    distance = pingTime * soundVelocity / 2 / 10000;  // calculate the obstacle distance(cm) according to the time of high level returned
    return distance;    // return distance(cm)
  }
  else                  // if the measure is overtime
    return maxDistance; // returns the maximum distance(cm)
}
