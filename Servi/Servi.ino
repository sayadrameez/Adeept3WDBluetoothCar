#include <Servo.h>
Servo ultrasonicServo;            // define servo to control turning of ultrasonic sensor
int ultrasonicPin = 2;            // define pin for signal line of the last servo
float ultrasonicServoOffset = 0;  // define a variable for deviation(degree) of the servo. The value is limited to(-20~20).

void setup() {
  // put your setup code here, to run once:
  ultrasonicServo.attach(ultrasonicPin);//attachs the servo on pin 9 to servo object
  ultrasonicServo.write(90);//back to 0 degrees 
}
bool clock =true;
void loop() {
   int ultrasonicServoDegree;
  // put your main code here, to run repeatedly:
  if(clock){
    for(int i=0; i<180; i++){
              
                          ultrasonicServoDegree = i+ultrasonicServoOffset;
                          ultrasonicServo.write(ultrasonicServoDegree);                         
                          delay(10);
            }
            clock =false;
  }else{
            for(int i=180; i>0; i--){
                          ultrasonicServoDegree = i+ultrasonicServoOffset;
                          ultrasonicServo.write(ultrasonicServoDegree);                         
                          delay(10);
            }
            clock =true;
  }
}
