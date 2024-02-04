#define BLYNK_PRINT Serial
#include <Servo.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SPI.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "xxxxxxxxxxx";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "xxxxxxxxxxx";
char pass[] = "xxxxxxxxxxx";

// These are used to set the direction of the bridge driver.

#define  n D3 //IN3
#define  m D4 //IN4
#define  l D1 //IN1
#define  o D2 //IN2


Servo servo;  
Servo servo1;


// SETUP
void setup()
{
  // Configure pins

  pinMode(m, OUTPUT);
  pinMode(l, OUTPUT);
  pinMode(n, OUTPUT);
  pinMode(o, OUTPUT);

  
  // Start serial communication
  Serial.begin(9600);

  // Connect Blynk
  Blynk.begin(auth, ssid, pass);
  servo.attach(14);
  servo1.attach(12);
}


// FORWARD
BLYNK_WRITE(V0) {
  int button = param.asInt(); // read button
  if (button == 1) {
    Serial.println("Moving forward");
    digitalWrite (l,HIGH);
    digitalWrite (m,LOW);
    digitalWrite (n,LOW);
    digitalWrite (o,LOW);
    
  }
  else {
    Serial.println("Stop");
   
    digitalWrite(l,LOW);
    digitalWrite(m,LOW);
    digitalWrite(n,LOW);
    digitalWrite(o,LOW);
  }
}

// RIGHT
BLYNK_WRITE(V1) {
  int button = param.asInt(); // read button
  if (button == 1) {
    Serial.println("Turning right");
    digitalWrite(l, LOW);
    digitalWrite(m, LOW);
    digitalWrite(n, HIGH);
    digitalWrite(o,LOW);
  
  }
  else {
    Serial.println("Stop");
    
    digitalWrite(l,LOW);
    digitalWrite(m,LOW);
    digitalWrite(n,LOW);
    digitalWrite(o,LOW);
  }
}

// LEFT
BLYNK_WRITE(V2) {
  int button = param.asInt(); // read button
  if (button == 1) {
    Serial.println("Turning left");
    digitalWrite(l, LOW);
    digitalWrite (m, HIGH);
    digitalWrite(n,LOW);
    digitalWrite(o,LOW);
    
  }
  else {
    Serial.println("Stop");
    
    digitalWrite(l,LOW);
    digitalWrite(m,LOW);
    digitalWrite(n,LOW);
    digitalWrite(o,LOW);
  }
}

// BACKWARD
BLYNK_WRITE(V3) {
  int button = param.asInt(); // read button
  if (button == 1) {
    Serial.println("Moving backward");
     digitalWrite (l, LOW);
   digitalWrite (m, LOW);
   digitalWrite (n, LOW);
   digitalWrite (o, HIGH);
    
   
  }
  else {
    Serial.println("Stop");
  
    digitalWrite(l,LOW);
    digitalWrite(m,LOW);
    digitalWrite(n,LOW);
    digitalWrite(o,LOW);
  }
}
//stop
BLYNK_WRITE(V4) {
  int button = param.asInt(); // read button
  if (button == 1) {
    Serial.println("stop");
     digitalWrite (l, LOW);
   digitalWrite (m, LOW);
   digitalWrite (n, LOW);
   digitalWrite (o, LOW);
  }
  }

//Voice Commands  
BLYNK_WRITE(V7) {
  int button = param.asInt(); // read button
  if (button == 1) {
    Serial.println("Turning left");
    digitalWrite(l, HIGH);
    digitalWrite (m, HIGH);
    digitalWrite(n,LOW);
    digitalWrite(o,LOW);
    delay (800);
      digitalWrite(l, LOW);
    digitalWrite (m, LOW);
    digitalWrite(n,LOW);
    digitalWrite(o,LOW);
    delay(100); 
  }
  else {
    Serial.println("Stop");
  
    digitalWrite(l,LOW);
    digitalWrite(m,LOW);
    digitalWrite(n,LOW);
    digitalWrite(o,LOW);
  }
}

BLYNK_WRITE(V8) {
  int button = param.asInt(); // read button
  if (button == 1) {
    Serial.println("Turning right");
    digitalWrite(l, HIGH);
    digitalWrite(m, LOW);
    digitalWrite(n, HIGH);
    digitalWrite(o,LOW);
    delay (800);
    digitalWrite(l, LOW);
    digitalWrite (m, LOW);
    digitalWrite(n,LOW);
    digitalWrite(o,LOW);
    delay(100);
  }
  else {
    Serial.println("Stop");
  
    digitalWrite(l,LOW);
    digitalWrite(m,LOW);
    digitalWrite(n,LOW);
    digitalWrite(o,LOW);
  }
}

// ACCELEROMETER
BLYNK_WRITE(V4) {
  float y = param[1].asFloat(); // read y-axis acceleration
  float z = param[2].asFloat(); // read z-axis acceleration
  if (y > 0.5) {
    Serial.println("Turning left");
    digitalWrite(l,HIGH);
    digitalWrite(o,LOW);
    digitalWrite(m,HIGH);
    digitalWrite(n,LOW);
   
  }
  if (y < -0.5) { 
    Serial.println("Turning right");

     digitalWrite(l,HIGH);
    digitalWrite(o,LOW);
    digitalWrite(m,LOW);
    digitalWrite(n,HIGH);
    
  } 
 if (z < -0.9) {
    Serial.println("Moving forward");

    digitalWrite(l,HIGH);
    digitalWrite(o,LOW);
    digitalWrite(m,LOW);
    digitalWrite(n,LOW);
  }
  if (z > 0) { 
    Serial.println("Moving backward");

    digitalWrite(l,LOW);
    digitalWrite(o,HIGH);
    digitalWrite(m,LOW);
    digitalWrite(n,LOW);
  }
  if ((y < 0.5) and (y > -0.5) and (z > -0.9) and (z < 0)) {
    Serial.println("Stop");

    digitalWrite(l,LOW);
    digitalWrite(o,LOW);
    digitalWrite(n,LOW);
    digitalWrite(m,LOW);
  }    
}
BLYNK_WRITE(V10)  
{
  servo.write(param.asInt());  
}
BLYNK_WRITE(V11)  
{ 
  servo1.write(param.asInt());
}  
 
// MAIN CODE
void loop()
{
  Blynk.run();
}
