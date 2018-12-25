             
const int R1Pin = A0;     // define R pin for RGB LED module 1 
const int G1Pin = A1;     // define G pin for RGB LED module 1
const int B1Pin = A2;     // define B pin for RGB LED module 1
const int R2Pin = A3;     // define R pin for RGB LED module 1 
const int G2Pin = A4;     // define G pin for RGB LED module 1
const int B2Pin = A5;     // define B pin for RGB LED module 1

void setup() {
  // put your setup code here, to run once:
  pinMode(R1Pin, OUTPUT);   // set R1Pin to output mode
  pinMode(G1Pin, OUTPUT);   // set G1Pin to output mode
  pinMode(B1Pin, OUTPUT);   // set B1Pin to output mode
  pinMode(R2Pin, OUTPUT);   // set R1Pin to output mode
  pinMode(G2Pin, OUTPUT);   // set G1Pin to output mode
  pinMode(B2Pin, OUTPUT);   // set B1Pin to output mode
}

void loop() {
  // put your main code here, to run repeatedly:
       digitalWrite(R1Pin, LOW);
       digitalWrite(G1Pin, HIGH);
       digitalWrite(B1Pin, HIGH);//red led
        digitalWrite(R2Pin, HIGH);
       digitalWrite(G2Pin, LOW);
       digitalWrite(B2Pin, HIGH);//red led
        delay(1000);
         digitalWrite(R1Pin, HIGH);
       digitalWrite(G1Pin, LOW);
       digitalWrite(B1Pin, HIGH);//red led
       digitalWrite(R2Pin, HIGH);
       digitalWrite(G2Pin, HIGH);
       digitalWrite(B2Pin, LOW);//red led
        delay(1000);
         digitalWrite(R1Pin, HIGH);
       digitalWrite(G1Pin, HIGH);
       digitalWrite(B1Pin, LOW);//red led
       digitalWrite(R2Pin, LOW);
       digitalWrite(G2Pin, HIGH);
       digitalWrite(B2Pin, HIGH);//red led
       delay(1000);
}
