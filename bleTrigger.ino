/*
  iPhone, Arduino Shutter Trigger sketch for Shutter Trigger Ble iOS app.
 
 created on May 2015 by GkN
 Check http://gokhan.in/blog/ble-shutter-trigger-for-iphone-and-arduino/ for schematics and fritzing designs.
 
 Sound trigger mode;
 Laser trigger mode;
 Press to shot;
 Self timer;
 Bulb mode;
 
 iOS app tested with HM-10 Bluetooth Low Energy Module

 */

#include <SoftwareSerial.h>

#define FLASH_PIN 4 // flash pin
#define SHUTTER_PIN 2 // shutter pin

#define SOUND_TRIGGER_ANALOG_PIN A0 // Analog pin for sound input
#define LIGHT_TRIGGER_ANALOG_PIN A1 // Analog pin for light input

SoftwareSerial mySerial(7, 8); // RX, TX

String readString;
String serialCommand;
String funcData;

int soundVal;
int lightVal;

int sec1;
int sec2;
int sensitivity;
int shutterDelay = 0;
int bulbMode;
int started;
int bulbtimer = 0;
int shutterMode = 1;
unsigned long firstShutter = 0;

 
void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  
  pinMode(SHUTTER_PIN, OUTPUT); 
  digitalWrite(SHUTTER_PIN, LOW); 
  pinMode(FLASH_PIN, OUTPUT); 
  digitalWrite(FLASH_PIN, LOW); 
  pinMode(13, OUTPUT); 
  digitalWrite(13, LOW); 
  
  soundVal = analogRead(SOUND_TRIGGER_ANALOG_PIN);
  Serial.println(soundVal);
  lightVal = analogRead(LIGHT_TRIGGER_ANALOG_PIN);
  
  blinkLED(4);
}

void loop() {
  
  // Start listening Software serial for commands
  if (mySerial.available())  {
    char c = mySerial.read();
    if (c == '&') {
      
      sec1 = readString.indexOf(','); 
      serialCommand = readString.substring(0, sec1);
      sec2 = readString.indexOf(',', sec1+1 ); 
      funcData = readString.substring(sec1+1); 
      
      if (serialCommand == "a") {
       started = (funcData.toInt());
       Serial.print(started);
      Serial.println(serialCommand);
     }
      
     else if (serialCommand == "m") {
       shutterMode = (funcData.toInt());
       Serial.print(shutterMode);
      Serial.println(serialCommand);
     }
     
     else if (serialCommand == "s") {
       sensitivity = (funcData.toInt());
       Serial.print(sensitivity);
      Serial.println(serialCommand);
     }
     
     else if (serialCommand == "d") {
       shutterDelay = (funcData.toInt());
       Serial.print(shutterDelay);
      Serial.println(serialCommand);
     }
     
     else if (serialCommand == "f") {
       bulbMode = (funcData.toInt());
       Serial.print(bulbMode);
      Serial.println(serialCommand);
     }
     
     else if (serialCommand == "p") { // Press to shot mode
       digitalWrite(SHUTTER_PIN, HIGH);
       delay(200);
       digitalWrite(SHUTTER_PIN, LOW); 
       blinkLED(2);
     }
     
     else if (serialCommand == "t") { // self timer mode
       int delayedshot = shutterDelay * 1000;
       delay(delayedshot);
       digitalWrite(SHUTTER_PIN, HIGH);
       delay(200);
       digitalWrite(SHUTTER_PIN, LOW); 
       blinkLED(2);
     }
     
     else if (serialCommand == "c") { // bulb mode
       bulbtimer = (funcData.toInt());
       if (bulbtimer == 1) {
         digitalWrite(SHUTTER_PIN, HIGH);
         digitalWrite(13, HIGH);
       }
       else if (bulbtimer == 0) {
         digitalWrite(SHUTTER_PIN, LOW);
         digitalWrite(13, LOW);
       }
       Serial.print(bulbtimer);
      Serial.println(serialCommand);
     }
  
      
      readString=""; //clears variable for new input
      funcData="";
     
    }  
    else {     
      readString += c; //makes the string readString
    }
  }
  
  // call functions high speed trigger modes
  if (started == 1 && shutterMode == 1) {
       soundTrigger(sensitivity,shutterDelay,bulbMode);
     }
     
   else if (started == 1 && shutterMode == 2) {
       laserTrigger(sensitivity,shutterDelay,bulbMode);
     }
     
}

void soundTrigger(int sens, int delayed, int bulb) {
  
  // print to serial port for debug
  // you can delete all hardware serial prints
  Serial.println("sound trigger");
  Serial.println(sens);
  Serial.println(delayed);
  
  int newsoundVal = analogRead(SOUND_TRIGGER_ANALOG_PIN);
  Serial.println(newsoundVal);
  if (bulbMode == 0) {
  digitalWrite(SHUTTER_PIN, HIGH);
  digitalWrite(13, HIGH);
  }
  if (abs(newsoundVal - soundVal) > sens)
  {
      delay(delayed);
      // check the preferred fire option. Camera or Flash
      if (bulb == 0) {
      digitalWrite(FLASH_PIN, HIGH);
      delay(200);
      digitalWrite(SHUTTER_PIN, LOW);
      digitalWrite(FLASH_PIN, LOW);
      digitalWrite(13, LOW);
      blinkLED(2);
      started = 0;
      }
      else if (bulb == 1) {
        digitalWrite(SHUTTER_PIN, HIGH);
        delay(200);
        digitalWrite(SHUTTER_PIN, LOW);
        blinkLED(2);
        started = 0;
      }
  }
  soundVal = analogRead(SOUND_TRIGGER_ANALOG_PIN);
  
}

void laserTrigger(int sens, int delayed, int bulb) {
  
  Serial.println("laser tetik");
  Serial.println(sens);
  Serial.println(delayed);

  int newlightVal = analogRead(LIGHT_TRIGGER_ANALOG_PIN);
  digitalWrite(SHUTTER_PIN, HIGH);
  digitalWrite(13, HIGH);
  if (abs(newlightVal - lightVal > sens))
  {
      if (bulb == 0) {
      digitalWrite(FLASH_PIN, HIGH);
      delay(200);
      digitalWrite(SHUTTER_PIN, LOW);
      digitalWrite(FLASH_PIN, LOW);
      digitalWrite(13, LOW);
      blinkLED(2);
      started = 0;
      }
      else if (bulb == 1) {
        digitalWrite(SHUTTER_PIN, HIGH);
        delay(200);
        digitalWrite(SHUTTER_PIN, LOW);
        blinkLED(2);
        started = 0;
      }
  }
  lightVal = analogRead(LIGHT_TRIGGER_ANALOG_PIN);
  
}

void blinkLED(int numBlinks) {
  for (int i=0; i < numBlinks; i++) {
    delay(50);
    digitalWrite(13, HIGH);
    delay(50);                     
    digitalWrite(13, LOW);   
  }
}
