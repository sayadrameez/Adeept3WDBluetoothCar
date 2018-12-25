#include <Servo.h>
Servo ultrasonicServo;            // define servo to control turning of ultrasonic sensor
int ultrasonicPin = 2;            // define pin for signal line of the last servo
float ultrasonicServoOffset = 0;  // define a variable for deviation(degree) of the servo. The value is limited to(-20~20).

const int redPin = A0;
const int greenPin = A1;
const int bluePin = A2;

const int red2Pin = A3;
const int green2Pin = A4;
const int blue2Pin = A5;
bool clock =true;

const int trigPin = 10;                  // define Trig pin for ultrasonic ranging module
const int echoPin = 11;                  // define Echo pin for ultrasonic ranging module

float maxDistance = 200;           // define the range(cm) for ultrasonic ranging module, Maximum sensor distance is rated at 400-500cm.
float soundVelocity = 340;         // Sound velocity = 340 m/s
float rangingTimeOut = 2 * maxDistance / 100 / soundVelocity * 1000000; // define the timeout(ms) for ultrasonic ranging module

const int buzzerPin = 3;  // define pin for buzzer

void setup() {
  Serial.begin(9600); // initialize serial port
  // put your setup code here, to run once:
  // put your setup code here, to run once:
  ultrasonicServo.attach(ultrasonicPin);//attachs the servo on pin 9 to servo object
  ultrasonicServo.write(90);//back to 0 degrees 
  pinMode(buzzerPin, OUTPUT); // set buzzerPin to output mode
   pinMode(trigPin, OUTPUT); // set trigPin to output mode
  pinMode(echoPin, INPUT);  // set echoPin to input mode
  setColourRgb(0,0,0);
  setColourRgb2(0,0,0);
}

void loop() {
  // put your main code here, to run repeatedly:
  int ultrasonicServoDegree;
    unsigned int rgbColour[3];
    rgbColour[0]=1;
    rgbColour[1]=0;
    rgbColour[2]=0;
int decColour = 0;
  // put your main code here, to run repeatedly:
  if(clock){
    for(int i=60; i<120; i++){
                           
                          ultrasonicServoDegree = i+ultrasonicServoOffset;
                          ultrasonicServo.write(ultrasonicServoDegree);            
                          digittalLED(rgbColour[0],rgbColour[1],rgbColour[2]);  
                          rgbColour[0] = rgbColour[0] == 0 ? 1: 0;
                          rgbColour[1] = rgbColour[1] == 0 ? 1: 0;
                          rgbColour[2] = rgbColour[2] == 0 ? 1: 0;

                          
                                            
                          delay(1000);

                         float dist = getDistance();
                       if(dist<20){ 
                              tone(buzzerPin, 50); 
                             }else
                             {
                              noTone(buzzerPin);
                             }

                              Serial.println(dist);
                              delay(50);
                          
            }
            clock =false;
  }else{
            for(int i=120; i>60; i--){
                          ultrasonicServoDegree = i+ultrasonicServoOffset;
                          ultrasonicServo.write(ultrasonicServoDegree); 
                          digittalLED(rgbColour[0],rgbColour[1],rgbColour[2]);     
                          rgbColour[0] = (rgbColour[0] == 0 ? 1: 0);
                          rgbColour[1] = (rgbColour[1] == 0 ? 1: 0);
                          rgbColour[2] = (rgbColour[2] == 0 ? 1: 0); 
                         delay(1000);

                          float dist = getDistance();
                       if(dist<20){ 
                              tone(buzzerPin, 2000); 
                             }else
                             {
                              noTone(buzzerPin);
                             }

                              Serial.println(dist);
                              delay(50);
            }
            clock =true;
  }
                     
}

void digittalLED(unsigned int red, unsigned int green, unsigned int blue){
       digitalWrite(redPin,red == 0 ? LOW : HIGH);
       digitalWrite(greenPin, green == 0 ? LOW : HIGH);
       digitalWrite(bluePin, blue == 0 ? LOW : HIGH);//red led
       digitalWrite(red2Pin, red == 0 ? HIGH : LOW);
       digitalWrite(green2Pin, green == 0 ? HIGH : LOW);
       digitalWrite(blue2Pin, blue == 0 ? HIGH : LOW);//red led
}
void setColourRgb(unsigned int red, unsigned int green, unsigned int blue) {
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
 }

 void setColourRgb2(unsigned int red, unsigned int green, unsigned int blue) {
  analogWrite(red2Pin, red);
  analogWrite(green2Pin, green);
  analogWrite(blue2Pin, blue);
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
