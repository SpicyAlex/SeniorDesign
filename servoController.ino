#include <Servo.h>

//output EMG pin
int sensorValOne;
int sensorValTwo;
int outputValue = 0;  
int pos = 0;
const int threshold = 10; //input min val here

//servo motors
Servo servoOne; //pinky & ring
Servo servoTwo; //middle
Servo servoThree; //index
Servo servoFour; //thumb

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  servoOne.attach(10); //pinky & ring
  servoTwo.attach(9); //middle
  servoThree.attach(6); //index
  servoFour.attach(5); //thumb
}

void loop() {
  //put your main code here, to run repeatedly:
  //print EMG value
  sensorValOne = analogRead(A0);
  sensorValTwo = analogRead(A1);
  Serial.print("EMG 1: ");
  outputValue = map(sensorValOne, 0, 1023, 0, 255);
  Serial.println(sensorValOne);
  Serial.print("EMG 2: ");
  Serial.println(sensorValTwo);
  outputValue = map(sensorValTwo, 0, 1023, 0, 255);
  
  //open and close hand
  if(sensorValOne > threshold){
    openHand();
    delay(2000);
  }
  if(sensorValTwo > threshold){
    openHand();
    delay(2000);
  }
  else if(sensorValOne < threshold){
    closeHand();
    delay(2000);
  }
  else if(sensorValTwo < threshold){
    
  }



  
}
//end of void loop()
//hand insytructions
//base grip
void openHand(){
   servoOne.write(0); //pinky & ring
   servoTwo.write(0); //middle
   servoThree.write(0); //index
   servoFour.write(0); //thumb
  
}
void closeHand(){
   servoOne.write(180); //pinky & ring
   servoTwo.write(180); //middle
   servoThree.write(180); //index
   servoFour.write(180); //thumb
  
}
//1st grip
void peaceSign(){
   servoOne.write(180); //pinky & ring
   servoTwo.write(0); //middle
   servoThree.write(0); //index
   servoFour.write(180); //thumb
}
//2nd grip
void pointFinger(){
   servoOne.write(0); //pinky & ring
   servoTwo.write(0); //middle
   servoThree.write(1800); //index
   servoFour.write(0); //thumb
}
//3rd grip
void chuckGrip(){
   servoOne.write(0); //pinky & ring
   servoTwo.write(90); //middle
   servoThree.write(90); //index
   servoFour.write(90); //thumb
}
//4th grip
void pinchGrip(){
   servoOne.write(0); //pinky & ring
   servoTwo.write(0); //middle
   servoThree.write(0); //index
   servoFour.write(0); //thumb
}
