const int rightLinefinderPin=13;//Set the digital 13 to the right Line Finder Moudle     
const int leftLinefinderPin=12; //Set the digital 12 to the left Line Finder Moudle

const int dirAPin = 7;    // define pin used to control rotational direction of motor A
const int pwmAPin = 6;    // define pin for PWM used to control rotational speed of motor A
const int dirBPin = 4;    // define pin used to control rotational direction of motor B
const int pwmBPin = 5;    // define pin for PWM used to control rotational speed of motor B

void setup() {

  Serial.begin(9600); // initialize serial port
  pinMode(dirAPin, OUTPUT);   // set dirAPin to output mode
  pinMode(pwmAPin, OUTPUT);   // set pwmAPin to output mode
  pinMode(dirBPin, OUTPUT);   // set dirBPin to output mode
  pinMode(pwmBPin, OUTPUT);   // set pwmBPin to output mode
  // put your setup code here, to run once:
    pinMode(rightLinefinderPin,INPUT_PULLUP); //initialize the line finder S pin as input
  pinMode(leftLinefinderPin,INPUT_PULLUP); //initialize the line finder S pin as input
  ctrlCar(0, 0, 0);
}

void loop() {
  // put your main code here, to run repeatedly:
   //Serial.println(analogRead(rightLinefinderPin) + "RIGHT");   
    //Serial.println(analogRead(leftLinefinderPin)+ "LEFT");
    if(digitalRead(rightLinefinderPin) == HIGH)
      Serial.println("HIGH RIGHT");
    else
      Serial.println("LOW RIGHT");
    if(digitalRead(leftLinefinderPin) == HIGH)
      Serial.println("HIGH LEFT");
    else
      Serial.println("LOW LEFT");

   delay(3000);
   
//  if((digitalRead(rightLinefinderPin) == HIGH) && (digitalRead(leftLinefinderPin)==LOW)){
//          ctrlCar(3, 150, 150);//backwards
//          delay(10);
//          ctrlCar(0, 255, 255);//turn right
//          delay(10);     
//          Serial.println(" Backwards Right");
//        }
//        else if((digitalRead(leftLinefinderPin)==HIGH) && (digitalRead(rightLinefinderPin)==LOW)){
//          ctrlCar(3, 150, 150);//backwards
//          delay(10);
//          ctrlCar(1, 255, 255);//turn left
//          delay(10);
//          Serial.println(" Backwards Left");
//        } 
//        else if((digitalRead(leftLinefinderPin)==HIGH) && (digitalRead(rightLinefinderPin)==HIGH))
//        {
//          ctrlCar(2, 120, 120);
//          Serial.println(" Ahead");
//          delay(10);
//        }//go ahead
//         else {
//             ctrlCar(3, 0, 0);
//             Serial.println(" Stop");
//             delay(10);
//         }
        
}

void ctrlCar(int motorDir,byte LeftotorSpd, byte rightMotorSpd) {
  if(motorDir==0){
    digitalWrite(dirAPin, LOW);
    digitalWrite(dirBPin, HIGH);
    Serial.println("Turn Right");
    }//turn right
  if(motorDir==1){
    digitalWrite(dirAPin, HIGH);
    digitalWrite(dirBPin, LOW);
    Serial.println("Turn Left");
    }  //turn left
  if(motorDir==2){
    digitalWrite(dirAPin, LOW);
    digitalWrite(dirBPin, LOW);
    Serial.println("Go Ahead");
    } //go ahead
  if(motorDir==3){
    digitalWrite(dirAPin, HIGH);
    digitalWrite(dirBPin, HIGH);
    Serial.println("Go Back");
    } //backwards
            
  analogWrite(pwmAPin, LeftotorSpd);
  analogWrite(pwmBPin, rightMotorSpd);
}
