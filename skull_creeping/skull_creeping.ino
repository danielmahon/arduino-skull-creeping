#include <Servo.h>
// author: Daniel Mahon Oct 2014 //
// original author: jim demello feb 2014 //
boolean pirStatus;
Servo servo1;
int servangle = 0; // servo angle variable
int pirNo[] = {3,4,5};          // pir pin numbers
int pirPrevLow[] = {1,1,1};     // previously low flag set to true
int pirPrevUsed[]  = {0,0,0};     // has pir been on used before going low
int pirCount = 3;
int maxRange = 140;
int pirPos[] = {10,maxRange/2,maxRange}; // positions for servo (0-180)
int curPosPir = 0;
int pirPin = 3;  
int ledPin = 13;


void setup(){
  Serial.begin(9600);
  servo1.attach(9);
  for(int i=0;i<pirCount;i++){
  pinMode(pirNo[i], INPUT);
   }
  pinMode(ledPin, OUTPUT);
  servo1.write(maxRange/2); // put servo at center to begin
  delay(10000); // calibrate for about 10 seconds
  
  // pulse eyes to show ready
  digitalWrite(ledPin, HIGH);
  delay(250);
  digitalWrite(ledPin, LOW);
  delay(250);
  digitalWrite(ledPin, HIGH);
  delay(250);
  digitalWrite(ledPin, LOW);
  }
////////////////////////////
//Main LOOP
//////////////////
void loop(){
  
//  servo1.write(70);
//  return;
  
  //test positions
 /*
  servo1.write(10);
  delay(2000);
  servo1.write(70);
  delay(2000);
  servo1.write(140);
  delay(2000);
  servo1.write(70);
  delay(2000);
  return;
  */
  
  for(int j=0;j<pirCount;j++){ // for each PIR
     pirPin=pirNo[j];
     pirStatus = digitalRead(pirPin);
     if (pirStatus == HIGH) {
          digitalWrite(ledPin, HIGH);   //the led visualizes the sensors output pin state
          if(pirPrevLow[j])    { 
                if (curPosPir != pirPin && pirPrevUsed[j] == 0) { // if high PIR is different than current position PIR then move to new position
                   servo1.write(pirPos[j]);
                   Serial.println(j);
                   delay(50);
                   curPosPir = pirPin; // keep current PIR
                   pirPrevUsed[j] = 1;
                }
          pirPrevLow[j] = 0; // pir is now not low
          }
      }
      else {
              digitalWrite(ledPin, LOW);  //the led visualizes the sensors output pin state
              pirPrevLow[j] = 1;   // pir is now low
              pirPrevUsed[j] = 0;
      }
    } // end j number of pirs loop
  }// end infinite loop
