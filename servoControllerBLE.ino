#include <Servo.h>
#include <ArduinoBLE.h>

//output EMG pin
int sensorValOne;
int sensorValTwo;
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
    while (!Serial);

  // initialize the BLE hardware
  BLE.begin();

  Serial.println("BLE Central -Dummy Int check");

  // start scanning for peripherals
  BLE.scanForUuid("19b10000-e8f2-537e-4f6c-d104768a1214");
  
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
  Serial.println(sensorValOne);
  Serial.print("EMG 2: ");
  Serial.println(sensorValTwo);
  // check if a peripheral has been discovered
  BLEDevice peripheral = BLE.available();

  if (peripheral) {
    // discovered a peripheral, print out address, local name, and advertised service
    Serial.print("Found ");
    Serial.print(peripheral.address());
    Serial.print(" '");
    Serial.print(peripheral.localName());
    Serial.print("' ");
    Serial.print(peripheral.advertisedServiceUuid());
    Serial.println();

    if (peripheral.localName() != "LED") {// checks for the local name of the device you want to connect to
      return;
    }

    // stop scanning
    BLE.stopScan();

    controlNum(peripheral);// function call to send dummy number 

    // peripheral disconnected, start scanning again
    BLE.scanForUuid("19b10000-e8f2-537e-4f6c-d104768a1214");
  }
}

void controlNum(BLEDevice peripheral) {
  // connect to the peripheral
  Serial.println("Connecting ...");

  if (peripheral.connect()) {
    Serial.println("Connected");
  } else {
    Serial.println("Failed to connect!");
    return;
  }

  // discover peripheral attributes
  Serial.println("Discovering attributes ...");
  if (peripheral.discoverAttributes()) {
    Serial.println("Attributes discovered");
  } else {
    Serial.println("Attribute discovery failed!");
    peripheral.disconnect();
    return;
  }

  // retrieve the LED characteristic on the other board LED is used here but it is the same as checking for a NUM characteristic, I butchered a code for you all
  BLECharacteristic ledCharacteristic = peripheral.characteristic("19b10001-e8f2-537e-4f6c-d104768a1214");

  if (!ledCharacteristic) {
    Serial.println("Peripheral does not have LED characteristic!");
    peripheral.disconnect();
    return;
  } else if (!ledCharacteristic.canWrite()) {
    Serial.println("Peripheral does not have a writable LED characteristic!");
    peripheral.disconnect();
    return;
  }

  while (peripheral.connected()) {
    // while the peripheral is connected
  
        Serial.println("Sending value");

        // button is pressed, write 0x80 to the peripheral to read on its serial monitor 
        ledCharacteristic.writeValue((byte)0x80);//sending 128 to the peripheral

        
     
    }

  Serial.println("Peripheral disconnected");
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
