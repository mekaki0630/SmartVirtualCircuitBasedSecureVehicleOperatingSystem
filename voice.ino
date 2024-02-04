
/************************ Adafruit IO Configuration *******************************/

// visit io.adafruit.com if you need to create an account,
// or if you need your Adafruit IO key.
#define IO_USERNAME    "xxxxxxxxxxx"
#define IO_KEY         "xxxxxxxxxxx"

/******************************* WIFI Configuration **************************************/

#define WIFI_SSID       "xxxxxxxxxxx"
#define WIFI_PASS       "xxxxxxxxxxx"

#include "AdafruitIO_WiFi.h"
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);

/************************ Main Program Starts Here *******************************/
#include <ESP8266WiFi.h>
#include <AdafruitIO.h>
#include <Adafruit_MQTT.h>
#include <ArduinoHttpClient.h>

// These are used to set the direction of the bridge driver.
#define  n D3 //IN3
#define  m D4 //IN4
#define  l D1 //IN1
#define  o D2 //IN2

AdafruitIO_Feed *command = io.feed("voice1"); // Set up the 'command' feed

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

  // connect to io.adafruit.com
  Serial.print("Connecting to Adafruit IO");
  io.connect();

  // set up a message handler for the 'command' feed.
  // the handleMessage function (defined below)
  // will be called whenever a message is
  // received from adafruit io.
  command->onMessage(handleMessage);  

  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(50);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());
}

// MAIN CODE
void loop()
{
  io.run();
}

// this part of the code runs whenever there's a new message on Adafruit.io feed
void handleMessage(AdafruitIO_Data *data) {
  
  String commandStr = data->toString(); // store the incoming commands in a string
  
  // received message
  Serial.print("received <- ");
  Serial.println(commandStr);

  String cmd;
  int angle;

  // separate text and number ingredients
  for (int i = 0; i < commandStr.length(); i++) {
    if (commandStr.substring(i, i+1) == ":") {
      cmd = commandStr.substring(0, i);
      angle = commandStr.substring(i+1).toInt();
      break;
    }
  }

  // print command
  Serial.println(cmd);
  Serial.println(angle);
  
  // perform movements
  // LEFT
  if (cmd.equalsIgnoreCase("left")){    
    Serial.println("Turning left");
    digitalWrite(l, HIGH);
    digitalWrite (m, HIGH);
    digitalWrite(n,LOW);
    digitalWrite(o,LOW);
    delay(angle*15);
    Serial.println("Stop");
    digitalWrite(l,LOW);
    digitalWrite(m,LOW);
    digitalWrite(n,LOW);
    digitalWrite(o,LOW);
  }
  // RIGHT
  if (cmd.equalsIgnoreCase("right")){    
    Serial.println("Turning right");
    digitalWrite(l, LOW);
    digitalWrite(m, LOW);
    digitalWrite(n, HIGH);
    digitalWrite(o,HIGH);
    delay(angle*15);
    Serial.println("Stop");
    digitalWrite(l,LOW);
    digitalWrite(m,LOW);
    digitalWrite(n,LOW);
    digitalWrite(o,LOW);
  }
  // FORWARD
  if (cmd.equalsIgnoreCase("forward")){    
    Serial.println("Moving forward");
    digitalWrite (l,LOW);
    digitalWrite (m,HIGH);
    digitalWrite (n,LOW);
    digitalWrite (o,HIGH);
    delay(angle*15);
    Serial.println("Stop");

    digitalWrite(l,LOW);
    digitalWrite(m,LOW);
    digitalWrite(n,LOW);
    digitalWrite(o,LOW);
  }
  // BACK
  if (cmd.equalsIgnoreCase("back")){    
    Serial.println("Moving back");
   digitalWrite (l, HIGH);
   digitalWrite (m, LOW);
   digitalWrite (n, HIGH);
   digitalWrite (o, LOW);
    delay(angle*15);
    Serial.println("Stop");

    digitalWrite(l,LOW);
    digitalWrite(m,LOW);
    digitalWrite(n,LOW);
    digitalWrite(o,LOW);
  }  
} 
