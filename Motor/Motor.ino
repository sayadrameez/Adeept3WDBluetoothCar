int motorRun = 0;//0:Stop;  1:Go ahead;  2;Backwards;  3:Turn left;  4:Turn right;
//'leftMotorSpeed' & 'rightMotorSpeed' Adjust the rotation speed of the left and right motor
int leftMotorSpeed = 0; 
int rightMotorSpeed = 0;

const int dirAPin = 7;    // define pin used to control rotational direction of motor A
const int pwmAPin = 6;    // define pin for PWM used to control rotational speed of motor A
const int dirBPin = 4;    // define pin used to control rotational direction of motor B
const int pwmBPin = 5;    // define pin for PWM used to control rotational speed of motor B
const int snsAPin = 0;    // define pin for detecting current of motor A
const int snsBPin = 1;    // define pin for detecting current of motor B


int bufferSettings=1;            //Let the car smooth back

void setup() {
  // put your setup code here, to run once:
  pinMode(dirAPin, OUTPUT);   // set dirAPin to output mode
  pinMode(pwmAPin, OUTPUT);   // set pwmAPin to output mode
  pinMode(dirBPin, OUTPUT);   // set dirBPin to output mode
  pinMode(pwmBPin, OUTPUT);   // set pwmBPin to output mode
}

void loop() {
    delay(1000);
    digitalWrite(dirBPin, HIGH);
     analogWrite(pwmBPin, 255);
     digitalWrite(dirAPin, HIGH);
     analogWrite(pwmAPin, 255);
     delay(1000);
     analogWrite(pwmBPin, 0);
     analogWrite(pwmAPin, 0);
     delay(10000);
     digitalWrite(dirBPin, LOW);
     analogWrite(pwmBPin, 255);
      digitalWrite(dirAPin, LOW);
     analogWrite(pwmAPin, 255);
     delay(1000);
     analogWrite(pwmBPin, 0);
     analogWrite(pwmAPin, 0);
     delay(10000);
    //ctrlCar(3, 150+leftMotorSpeed, 150+rightMotorSpeed);
//delay(3000);
//ctrlCar(0, 0, 0);
//
//delay(3000);
// ctrlCar(1, 150+leftMotorSpeed, 150+rightMotorSpeed);
//delay(3000);
//ctrlCar(0, 0, 0);
//
//delay(3000);
// ctrlCar(2, 150+leftMotorSpeed, 150+rightMotorSpeed);
//delay(3000);
//ctrlCar(0, 0, 0);
//
// delay(3000);
// ctrlCar(3, 150+leftMotorSpeed, 150+rightMotorSpeed);
//delay(3000);
//ctrlCar(0, 0, 0);
}

// send motor current to serial port  
//  float iMotorA = analogRead(snsAPin) * 5.0 / 1024 / 30 / 0.05;
//  float iMotorB = analogRead(snsBPin) * 5.0 / 1024 / 30 / 0.05;

//  Serial.print("iMotorA: ");
//  Serial.print(iMotorA);
//  Serial.print(" A ,iMotorB: ");
//  Serial.print(iMotorB);
//  Serial.println(" A");

void ctrlCar(int motorDir,byte LeftotorSpd, byte rightMotorSpd) {
  if(motorDir==0){
    digitalWrite(dirAPin, LOW);
    digitalWrite(dirBPin, HIGH);
    }//turn right
  if(motorDir==1){
    digitalWrite(dirAPin, HIGH);
    digitalWrite(dirBPin, LOW);
    }  //turn left
  if(motorDir==2){
    digitalWrite(dirAPin, LOW);
    digitalWrite(dirBPin, LOW);
    } //go ahead
  if(motorDir==3){
    digitalWrite(dirAPin, HIGH);
    digitalWrite(dirBPin, HIGH);
    } //backwards
            
  analogWrite(pwmAPin, LeftotorSpd);
  analogWrite(pwmBPin, rightMotorSpd);
}
