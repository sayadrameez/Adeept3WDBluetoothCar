/***********************************************************
File name:  Adeept3WDBluetoothCar.ino
Description:  
Three working modes after the car is power on: 
Mode No.1: Remote control via Bluetooth
You can control the car to go forward and backward and turn left and right by commands via Bluetooth. At the same time, you can switch between the modes and control the buzzer to beep.
Mode No.2: Obstacle avoidance by ultrasonic
Under this mode, the car can detect and bypass the obstacles in front automatically. 
Mode No.3: Line following 
Under this mode, on a white surface with routes of 3cm-width black lines, the car can go along the black lines. 
Website: www.adeept.com
E-mail: support@adeept.com
Author: Tom
Date: 2017/08/19 
***********************************************************/

#include <Servo.h>

//mode = 0:Bluetooth remote control mode
//mode = 1:Ultrasonic barrier mode
//mode = 2:Tracking mode
int mode = 0;

int motorRun = 0;//0:Stop;  1:Go ahead;  2;Backwards;  3:Turn left;  4:Turn right;
//'leftMotorSpeed' & 'rightMotorSpeed' Adjust the rotation speed of the left and right motor
int leftMotorSpeed = 0; 
int rightMotorSpeed = 0;

int bufferSettings=1;            //Let the car smooth back

Servo ultrasonicServo;            // define servo to control turning of ultrasonic sensor
int ultrasonicPin = 2;            // define pin for signal line of the last servo
float ultrasonicServoOffset = 0;  // define a variable for deviation(degree) of the servo. The value is limited to(-20~20).

int trigPin = 10;                  // define Trig pin for ultrasonic ranging module
int echoPin = 11;                  // define Echo pin for ultrasonic ranging module
float maxDistance = 200;           // define the range(cm) for ultrasonic ranging module, Maximum sensor distance is rated at 400-500cm.
float soundVelocity = 340;         // Sound velocity = 340 m/s
float rangingTimeOut = 2 * maxDistance / 100 / soundVelocity * 1000000; // define the timeout(ms) for ultrasonic ranging module

const int rightLinefinderPin=13;//Set the digital 13 to the right Line Finder Moudle     
const int leftLinefinderPin=12; //Set the digital 12 to the left Line Finder Moudle
const int dirAPin = 7;    // define pin used to control rotational direction of motor A
const int pwmAPin = 6;    // define pin for PWM used to control rotational speed of motor A
const int dirBPin = 4;    // define pin used to control rotational direction of motor B
const int pwmBPin = 5;    // define pin for PWM used to control rotational speed of motor B
const int snsAPin = 0;    // define pin for detecting current of motor A
const int snsBPin = 1;    // define pin for detecting current of motor B
const int buzzerPin = 3;  // define pin for buzzer
const int R1Pin = A0;     // define R pin for RGB LED module 1 
const int G1Pin = A1;     // define G pin for RGB LED module 1
const int B1Pin = A2;     // define B pin for RGB LED module 1
const int R2Pin = A3;     // define R pin for RGB LED module 2
const int G2Pin = A4;     // define G pin for RGB LED module 2
const int B2Pin = A5;     // define B pin for RGB LED module 2

int right = 0;
int left = 0;

void setup() {
  ultrasonicServo.attach(ultrasonicPin);//attachs the servo on pin 9 to servo object
  ultrasonicServo.write(90);//back to 0 degrees 
  Serial.begin(9600); // initialize serial port
  pinMode(dirAPin, OUTPUT);   // set dirAPin to output mode
  pinMode(pwmAPin, OUTPUT);   // set pwmAPin to output mode
  pinMode(dirBPin, OUTPUT);   // set dirBPin to output mode
  pinMode(pwmBPin, OUTPUT);   // set pwmBPin to output mode
  pinMode(buzzerPin, OUTPUT); // set buzzerPin to output mode
  pinMode(R1Pin, OUTPUT);   // set R1Pin to output mode
  pinMode(G1Pin, OUTPUT);   // set G1Pin to output mode
  pinMode(B1Pin, OUTPUT);   // set B1Pin to output mode
  pinMode(R2Pin, OUTPUT);   // set R2Pin to output mode
  pinMode(G2Pin, OUTPUT);   // set G2Pin to output mode
  pinMode(B2Pin, OUTPUT);   // set B2Pin to output mode

  pinMode(trigPin, OUTPUT); // set trigPin to output mode
  pinMode(echoPin, INPUT);  // set echoPin to input mode

  pinMode( rightLinefinderPin,INPUT_PULLUP); //initialize the line finder S pin as input
  pinMode( leftLinefinderPin,INPUT_PULLUP); //initialize the line finder S pin as input
}

void loop()
{     
  
      byte barDistance = maxDistance; // save the minimum measured distance from obstacles
      byte barDegree;                 // save the minimum measured angel from obstacles
      byte distance;                  // save the current the measured distance from obstacles
      int ultrasonicServoDegree;
      int obstacle=0;
      char receiveVal;                  // Defined receive data

       if(Serial.available() > 0)       //Receive serial data
       {        
           receiveVal = Serial.read();  //Save the serial data received 
           switch(receiveVal){
           case 'a': motorRun = 3;break;//go ahead
           case 'b': motorRun = 1;break;//turn right
           case 'c': motorRun = 2;break;//turn left
           case 'd': motorRun = 4;break;//backwards
           case 'e': mode = 0; motorRun = 0;break;
           case 'f': mode = 1; break;
           case 'g': mode = 2; break;
           case 'h':  ctrlCar(0, 0, 0);   // stop car
                     tone(buzzerPin, 2000); 
                     delay(100); 
                     noTone(buzzerPin); break;
           }

      }
      //Bluetooth remote control mode
      if(mode==0){
        digitalWrite(R1Pin, LOW);digitalWrite(G1Pin, HIGH);digitalWrite(B1Pin, HIGH);//red led
        digitalWrite(R2Pin, LOW);digitalWrite(G2Pin, HIGH);digitalWrite(B2Pin, HIGH);//red led
        switch(motorRun){
        case 0: ctrlCar(0, 0, 0);   // control steering and reversing smart car
                bufferSettings = 1;
                break;
        case 1: ctrlCar(0, 150+leftMotorSpeed, 150+rightMotorSpeed);   // control smart car turn right
                bufferSettings = 1;
                break;
        case 2: ctrlCar(1, 150+leftMotorSpeed, 150+rightMotorSpeed);   // control smart car turn left
                bufferSettings = 1;
                break;
        case 3: ctrlCar(2, 150+leftMotorSpeed, 150+rightMotorSpeed);   // control smart car go ahead
                bufferSettings = 1;
                break;
        case 4: if(bufferSettings == 1){
                  bufferSettings = 0;
                  for(int i=40;i<150+leftMotorSpeed;i++){
                    ctrlCar(3, i, i);   // control smart car backwards
                    delay(5); 
                  }
                }else{
                ctrlCar(3, 150+leftMotorSpeed, 150+rightMotorSpeed);   // control smart car backwards
                }
                break;
        default:break;
        }
      }

      
      //Ultrasonic barrier mode
      if(mode==1){
        digitalWrite(R1Pin, HIGH);digitalWrite(G1Pin, LOW);digitalWrite(B1Pin, HIGH);//green led
        digitalWrite(R2Pin, HIGH);digitalWrite(G2Pin, LOW);digitalWrite(B2Pin, HIGH);//green led
            for(int i=60; i<120; i++){
                          ultrasonicServoDegree = i+ultrasonicServoOffset;
                          ultrasonicServo.write(ultrasonicServoDegree);
                          if(getDistance()<20){ 
                            delay(1);
                           if(getDistance()<20){
                            ctrlCar(0, 0, 0);
                            obstacle=1;
                            }
                          }
                          delay(1);
            }
             for(int i=120; i>60; i--){
                          ultrasonicServoDegree = i+ultrasonicServoOffset;
                          ultrasonicServo.write(ultrasonicServoDegree);
                          if(getDistance()<20){ 
                            delay(1);
                           if(getDistance()<20){
                            ctrlCar(0, 0, 0);
                            obstacle=1;
                            }
                          }
                           delay(1);
            }
          if(obstacle==1){
                 
                          for(int i=90; i<160; i++){
                          ultrasonicServoDegree = i+ultrasonicServoOffset;
                          ultrasonicServo.write(ultrasonicServoDegree);//
                          distance = getDistance(); // detect the current distance from obstacle with angle of pan tilt stable
                          if (distance < barDistance) { // if the current measured distance is smaller than the previous one, save the data of current measured distance
                            barDegree = ultrasonicServoDegree;       // save the measured angle
                            barDistance = distance;     // save the measured distance
                          }
                          delay(1);
                        }
                        for(int i=160; i>20; i--){
                          ultrasonicServoDegree = i+ultrasonicServoOffset;
                          ultrasonicServo.write(ultrasonicServoDegree);//
                          distance = getDistance();            // detect the current distance from obstacle with angle of pan tilt stable
                          if (distance < barDistance) {        // if the current measured distance is smaller than the previous one, save the data of current measured distance
                            barDegree = ultrasonicServoDegree; // save the measured angle
                            barDistance = distance;            // save the measured distance
                          }
                        }
                        for(int i=20; i<90; i++){
                          ultrasonicServoDegree = i+ultrasonicServoOffset;
                          ultrasonicServo.write(ultrasonicServoDegree);//
                          distance = getDistance(); // detect the current distance from obstacle with angle of pan tilt stable
                          if (distance < barDistance) { // if the current measured distance is smaller than the previous one, save the data of current measured distance
                            barDegree = ultrasonicServoDegree;       // save the measured angle
                            barDistance = distance;     // save the measured distance
                          }
                          delay(1);
                        }
                        delay(1);
            }
      // According to the result of scanning control action of intelligent vehicles
      if (barDistance < 20) {     // if the obstacle distance is too close, reverse the travelling direction
        if (barDegree < 90)       // choose to reverse direction according to the angle with obstacle
        {
         ctrlCar(3, 150, 150);//backwards
         delay(random(500, 1000));
         ctrlCar(0, 150, 150);//turn right
         delay(random(50, 375));
        }
        else
        {
          ctrlCar(3, 150, 150);//backwards
          delay(random(500, 1000));
          ctrlCar(1, 150, 150);//turn left
          delay(random(50, 375));        
        }
      }else{
          ctrlCar(2, 150, 150);//go ahead
        }
      }
     
     //Tracking mode
     if(mode==2){
      digitalWrite(R1Pin, HIGH);digitalWrite(G1Pin, HIGH);digitalWrite(B1Pin, LOW);//blue led
      digitalWrite(R2Pin, HIGH);digitalWrite(G2Pin, HIGH);digitalWrite(B2Pin, LOW);//blue led
        if((digitalRead(rightLinefinderPin)==HIGH) && (digitalRead(leftLinefinderPin)==LOW)){
          ctrlCar(3, 150, 150);//backwards
          delay(10);
          ctrlCar(0, 255, 255);//turn right
          delay(10);     
        }
        else if((digitalRead(leftLinefinderPin)==HIGH) && (digitalRead(rightLinefinderPin)==LOW)){
          ctrlCar(3, 150, 150);//backwards
          delay(10);
          ctrlCar(1, 255, 255);//turn left
          delay(10);
        } else
        {ctrlCar(2, 120, 120);}//go ahead
      }
// send motor current to serial port  
//  float iMotorA = analogRead(snsAPin) * 5.0 / 1024 / 30 / 0.05;
//  float iMotorB = analogRead(snsBPin) * 5.0 / 1024 / 30 / 0.05;

//  Serial.print("iMotorA: ");
//  Serial.print(iMotorA);
//  Serial.print(" A ,iMotorB: ");
//  Serial.print(iMotorB);
//  Serial.println(" A");
}
void ctrlCar(int motorDir,byte LeftotorSpd, byte rightMotorSpd) {
  if(motorDir==0){digitalWrite(dirAPin, LOW);digitalWrite(dirBPin, HIGH);}//turn right
  if(motorDir==1){digitalWrite(dirAPin, HIGH);digitalWrite(dirBPin, LOW);}  //turn left
  if(motorDir==2){digitalWrite(dirAPin, LOW);digitalWrite(dirBPin, LOW);} //go ahead
  if(motorDir==3){digitalWrite(dirAPin, HIGH);digitalWrite(dirBPin, HIGH);} //backwards
            
  analogWrite(pwmAPin, LeftotorSpd);
  analogWrite(pwmBPin, rightMotorSpd);
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
