/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************
  This example runs directly on ESP8266 chip.

  Note: This requires ESP8266 support package:
    https://github.com/esp8266/Arduino

  Please be sure to select the right ESP8266 module
  in the Tools -> Board menu!

  Change WiFi ssid, pass, and Blynk auth token to run :)
  Feel free to apply it to any other example. It's simple!
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "XXXXX";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "YYYYY";
char pass[] = "ZZZZZ";

// These are used to set the direction of the bridge driver.
#define ENB D3      //ENB
#define MOTORB_1 D4 //IN3
#define MOTORB_2 D5 //IN4
#define MOTORA_1 D7 //IN1
#define MOTORA_2 D6 //IN2
#define ENA D8      //ENA

#define  n D3 //IN3
#define  m D4 //IN4
#define  l D1 //IN1
#define  o D2 //IN2

int motor_right_speed = 0;
int motor_left_speed = 0;

// SETUP
void setup()
{
  // Configure pins
  pinMode(ENA, OUTPUT);
  pinMode(MOTORA_1, OUTPUT);
  pinMode(MOTORA_2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(MOTORB_1, OUTPUT);
  pinMode(MOTORB_2, OUTPUT);

  digitalWrite(ENA,LOW);
  digitalWrite(ENB,LOW);
  
  // Start serial communication
  Serial.begin(9600);

  // Connect Blynk
  Blynk.begin(auth, ssid, pass);
}

// JOYSTICK
BLYNK_WRITE(V0) {
  int nJoyX = param[0].asInt(); // read x-joystick
  int nJoyY = param[1].asInt(); // read y-joystick

  // Print x and y values
  Serial.print("X = ");
  Serial.print(nJoyX);
  Serial.print("; Y = ");
  Serial.println(nJoyY);

  // OUTPUTS
  int nMotMixL; // Motor (left) mixed output
  int nMotMixR; // Motor (right) mixed output

  // CONFIG
  // - fPivYLimt  : The threshold at which the pivot action starts
  //                This threshold is measured in units on the Y-axis
  //                away from the X-axis (Y=0). A greater value will assign
  //                more of the joystick's range to pivot actions.
  //                Allowable range: (0..+127)
  float fPivYLimit = 1023.0;
      
  // TEMP VARIABLES
  float   nMotPremixL;    // Motor (left) premixed output
  float   nMotPremixR;    // Motor (right) premixed output
  int     nPivSpeed;      // Pivot Speed
  float   fPivScale;      // Balance scale between drive and pivot

  // Calculate Drive Turn output due to Joystick X input
  if (nJoyY >= 0) {
    // Forward
    nMotPremixL = (nJoyX>=0)? 1023.0 : (1023.0 + nJoyX);
    nMotPremixR = (nJoyX>=0)? (1023.0 - nJoyX) : 1023.0;
  } else {
    // Reverse
    nMotPremixL = (nJoyX>=0)? (1023.0 - nJoyX) : 1023.0;
    nMotPremixR = (nJoyX>=0)? 1023.0 : (1023.0 + nJoyX);
  }

  // Scale Drive output due to Joystick Y input (throttle)
  nMotPremixL = nMotPremixL * nJoyY/1023.0;
  nMotPremixR = nMotPremixR * nJoyY/1023.0;

  // Now calculate pivot amount
  // - Strength of pivot (nPivSpeed) based on Joystick X input
  // - Blending of pivot vs drive (fPivScale) based on Joystick Y input
  nPivSpeed = nJoyX;
  fPivScale = (abs(nJoyY)>fPivYLimit)? 0.0 : (1.0 - abs(nJoyY)/fPivYLimit);

  // Calculate final mix of Drive and Pivot
  nMotMixL = (1.0-fPivScale)*nMotPremixL + fPivScale*( nPivSpeed);
  nMotMixR = (1.0-fPivScale)*nMotPremixR + fPivScale*(-nPivSpeed);
  
  motor_left_speed = nMotMixL;
  motor_right_speed = nMotMixR;
  Serial.print("M1 = ");
  Serial.print(motor_right_speed);
  Serial.print("M2 = ");
  Serial.println(motor_left_speed);
 
  if (motor_right_speed > 600) {
    digitalWrite(l,HIGH);
    digitalWrite(o,LOW);
  }
  else if (motor_right_speed < -600) {
    digitalWrite(l,LOW);
    digitalWrite(o, HIGH);
    
  }
  else {
    digitalWrite(l, LOW);
    digitalWrite(o, LOW);
  }

  if (motor_left_speed > 600) {
    digitalWrite(n, LOW);
    digitalWrite(m, HIGH);
  }
  else if (motor_left_speed < -600) {
    digitalWrite(n,HIGH);
    digitalWrite(m,LOW);
  }
  else {
    digitalWrite(n, LOW);
    digitalWrite(m, LOW);
  }
 
}

// MAIN CODE
void loop()
{
  Blynk.run();
}
