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

const int buzzerPin = 3;  // define pin for buzzer

void setup() {
  // put your setup code here, to run once:
  // put your setup code here, to run once:
  ultrasonicServo.attach(ultrasonicPin);//attachs the servo on pin 9 to servo object
  ultrasonicServo.write(90);//back to 0 degrees 
  pinMode(buzzerPin, OUTPUT); // set buzzerPin to output mode
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
    for(int i=0; i<180; i++){
                           
                          ultrasonicServoDegree = i+ultrasonicServoOffset;
                          ultrasonicServo.write(ultrasonicServoDegree);            
                          digittalLED(rgbColour[0],rgbColour[1],rgbColour[2]);  
                          rgbColour[0] = rgbColour[0] == 0 ? 1: 0;
                          rgbColour[1] = rgbColour[1] == 0 ? 1: 0;
                          rgbColour[2] = rgbColour[2] == 0 ? 1: 0;
                          if(i%60 == 0) tone(buzzerPin, 2000); 
                          else noTone(buzzerPin);                          
                          delay(100);
            }
            clock =false;
  }else{
            for(int i=180; i>0; i--){
                          ultrasonicServoDegree = i+ultrasonicServoOffset;
                          ultrasonicServo.write(ultrasonicServoDegree); 
                          digittalLED(rgbColour[0],rgbColour[1],rgbColour[2]);     
                          rgbColour[0] = (rgbColour[0] == 0 ? 1: 0);
                          rgbColour[1] = (rgbColour[1] == 0 ? 1: 0);
                          rgbColour[2] = (rgbColour[2] == 0 ? 1: 0); 
                          if(i%60 == 0) tone(buzzerPin, 2000); 
                          else noTone(buzzerPin);                 
                          delay(100);
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
