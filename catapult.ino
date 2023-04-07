///////////////
// Libraries //
///////////////
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <ESP32Servo.h>

#define BLYNK_TEMPLATE_ID "TMPL6bZXYfk74"
#define BLYNK_TEMPLATE_NAME "Esp"

///////////////////////////
// Enter your Auth token //
///////////////////////////
char auth[] = "41gMx1No0PYBn4grwGcueua8fjTHPjyN";



///////////////////////////////////////
// Enter your WIFI SSID and password //z
//       Use Router/hotspot          //
///////////////////////////////////////
char ssid[] = "HelloWorld";
char pass[] = "123456789";



/////////////////////////////////
// Define your pin assignments //
/////////////////////////////////
const int SERVOCATAPULTARM_PIN = 16;
const int SERVO_PIN = 2;
const int SERVODIRECTION_PIN = 17;
const int relay1 = 32;
const int relay2 = 5;
const int rightLED = 25;
const int leftLED = 26;
const int SERVOFIRE_PIN = 8;
const int alarmLED = 18;
const int alarmBuzzerPin = 19;

//////////////////
// servo Loader //
//////////////////
Servo servo;

///////////////
// servo Arm //
///////////////
Servo servoArm;

/////////////////////
// servo Direction //
///////////////
Servo servoDirection;

////////////////
// servo Fire //
////////////////
Servo servoFire;




//////////////////////////
// dc motor init values //
//////////////////////////
//int motorSpeed = 0;
//int motorDirection = 0;



void setup(){
  Serial.begin(9600);// initialize serial monitor with 9600 baud

  //////////
  // Auth //
  //////////
  Blynk.begin(auth, ssid, pass);

  ////////////////////////////
  // servo loader pin setup //
  ////////////////////////////
  servo.attach(SERVO_PIN);
  servoArm.attach(SERVOCATAPULTARM_PIN);
  servoDirection.attach(SERVODIRECTION_PIN);
  servoFire.attach(SERVOFIRE_PIN);

  ////////////////////////
  // Relay Setup for DC //
  ////////////////////////
  pinMode(relay1, OUTPUT);// set pin as output for relay 1
  pinMode(relay2, OUTPUT);// set pin as output for relay 2
  // keep the motor off by keeping both HIGH
  digitalWrite(relay1, HIGH); 
  digitalWrite(relay2, HIGH); 



  //////////////
  // pinModes //
  //////////////

  // keep the motor off by keeping both HIGH
  //digitalWrite(relayPin1, HIGH); 
 // digitalWrite(relayPin2, HIGH); 

  
}

void loop()
{
  Blynk.run();

}



void alarmFor3Sec() 
{
  for (int i = 0; i < 3; i++) 
  {
    // Activate the alarm and LED by setting their pins to HIGH
    digitalWrite(alarmBuzzerPin, HIGH);
    delay(500);
    // Deactivate the alarm and LED by setting their pins to LOW
    digitalWrite(alarmBuzzerPin, LOW);
    delay(500);
  }
}


////////////////////
// Servo Reloader //
////////////////////
BLYNK_WRITE(V0)
{
  // Set servo position based on joystick Y value
  int angle = map(param.asInt(), 0, 255, 0, 90);
  servo.write(angle);
}
////////////////////////
// Servo Catapult Arm //
////////////////////////
BLYNK_WRITE(V1)
{
    // Set servo position based on joystick Y value
  int angle = map(param.asInt(), 0, 200, 0, 90);
  servoArm.write(angle);
}

/////////////////////
// Direction Servo //
/////////////////////
BLYNK_WRITE(V2)
{
  // Set servo position based on joystick Y value
  int angle = map(param.asInt(), 0, 255, 30, 150);
  servoDirection.write(angle);
  if (angle < 100)
  {
    digitalWrite(leftLED, HIGH);
    digitalWrite(rightLED, LOW);
  }
  else if (angle > 100)
  {
    digitalWrite(leftLED, LOW);
    digitalWrite(rightLED, HIGH);
  }
  else
  {
    digitalWrite(leftLED, LOW);
    digitalWrite(rightLED, LOW);
  }
}

//////////////////////
// Forward Movement //
//////////////////////

BLYNK_WRITE(V3) 
  {
    digitalWrite(relay1, LOW);// turn relay 1 ON
    digitalWrite(relay2, HIGH);// turn relay 2 OFF
  }

///////////////////////
// Backward Movement //
///////////////////////
BLYNK_WRITE(V4) 
{
  digitalWrite(relay1, HIGH);// turn relay 1 OFF
  digitalWrite(relay2, LOW);// turn relay 2 ON 
}

///////////////////////
// Battle Mode //
///////////////////////
BLYNK_WRITE(V5) 
{
  digitalWrite(alarmLED, LOW);

  ///////////////
  // the purge //
  ///////////////
  // Play a tone for 100 milliseconds
  tone(alarmBuzzerPin, 1000, 100);
  delay(100);
  
  // Play a tone for 300 milliseconds
  tone(alarmBuzzerPin, 2000, 300);
  delay(300);
  
  // Play a tone for 500 milliseconds
  tone(alarmBuzzerPin, 3000, 500);
  delay(500);
  
  // Play a tone for 700 milliseconds
  tone(alarmBuzzerPin, 4000, 700);
  delay(700);
}

/////////////////
// Fire Button //
/////////////////
BLYNK_WRITE(V6)
{
  // Set servo position based on joystick Y value
  int angle = map(param.asInt(), 0, 200, 0, 90);
  servoFire.write(angle);
}


//////////
// STOP //
//////////
BLYNK_WRITE(V7) 
{
  digitalWrite(relay1, LOW);// turn relay 1 OFF
  digitalWrite(relay2, LOW);// turn relay 2 ON 
}