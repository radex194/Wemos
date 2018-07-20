#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
ESP8266WebServer server(80);

//----------------------------------------------------------------
//-- Basic Otto´s setup
//-- You can add functions, gestures or sounds in loop
//-- https://github.com/OttoDIY
//-- CC BY SA (http://ottodiy.com)
//-----------------------------------------------------------------
#include <Servo.h>
#include <Oscillator.h>
#include <US.h>
#include <Otto.h>
Otto Otto;  //This is Otto!
//---------------------------------------------------------
//-- First step: Make sure the pins for servos are in the right position
/*
         ---------------
        |     O   O     |
        |---------------|
  YR D6==> |               | <== YL D5
         ---------------
            ||     ||
  RR D8==>   -----   ------  <== RL D7
         |-----   ------|
*/
#define PIN_YL D5 //servo[2]
#define PIN_YR D6 //servo[3]
#define PIN_RL D7 //servo[4]
#define PIN_RR D8 //servo[5]
#define USTrigger D2 //Trigger on D2
#define USEcho D3 //Echo on Trigger D3

/*MOVEMENTS LIST**************
   dir=1---> FORWARD/LEFT
   dir=-1---> BACKWARD/RIGHT
   T : amount of movement. HIGHER VALUE SLOWER MOVEMENT usually 1000 (from 600 to 1400)
   h: height of mov. around 20
     jump(steps=1, int T = 2000);
     walk(steps, T, dir);
     turn(steps, T, dir);
     bend (steps, T, dir); //usually steps =1, T=2000
     shakeLeg (steps, T, dir);
     updown(steps, T, HEIGHT);
     swing(steps, T, HEIGHT);
     tiptoeSwing(steps, T, HEIGHT);
     jitter(steps, T, HEIGHT); (small T)
     ascendingTurn(steps, T, HEIGHT);
     moonwalker(steps, T, HEIGHT,dir);
     crusaito(steps, T, HEIGHT,dir);
     flapping(steps, T, HEIGHT,dir);
*/

bool obstacleDetected = false;
int distance = 0;

void handleFWD() {
  Serial.println("FWD");
  String message;
  message += "{ \"success\": ";
  message += "1 }";
  server.send(200, "text/plain", message );
  Otto.walk(2, 1000, 1); //2 steps FORWARD
  Otto.home();
}
void handleBACK() {
  Serial.println("BACK");
  String message;
  message += "{ \"success\": ";
  message += "1 }";
  server.send(200, "text/plain", message );
  Otto.walk(2, 1000, -1);
  Otto.home();
}
void handleRIGHT() {
  Serial.println("RIGHT");
  String message;
  message += "{ \"success\": ";
  message += "1 }";
  server.send(200, "text/plain", message );
  Otto.turn(2, 1000, 1);
  Otto.home();
}
void handleLEFT() {
  Serial.println("LEFT");
  String message;
  message += "{ \"success\": ";
  message += "1 }";
  server.send(200, "text/plain", message );
  Otto.turn(2, 1000, -1);
  Otto.home();
}
void handleMOON() {
  Serial.println("Ooowwwww");
  String message;
  message += "{ \"success\": ";
  message += "1 }";
  server.send(200, "text/plain", message );
  Otto.moonwalker(3, 1000, 25, 1);
  Otto.home();
}
void handleFLAP() {
  Serial.println("Flap");
  String message;
  message += "{ \"success\": ";
  message += "1 }";
  server.send(200, "text/plain", message );
  Otto.flapping(3, 1000, 25, 1);
  Otto.home();
}

void handleHOME() {
  Serial.println("Home");
  String message;
  message += "{ \"success\": ";
  message += "1 }";
  server.send(200, "text/plain", message );
  Otto.home();

}
void handleUPDOWN() {
  Serial.println("UpDown");
  String message;
  message += "{ \"success\": ";
  message += "1 }";
  server.send(200, "text/plain", message );
  Otto.updown(1, 2000, 22);
  Otto.home();
}
void handleBEND() {
  Serial.println("Bend");
  String message;
  message += "{ \"success\": ";
  message += "1 }";
  server.send(200, "text/plain", message );
  Otto.bend (1, 2000, 1);
  Otto.home();
}

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println("Starting: Please connect to DIYODE-AP")

  WiFi.mode(WIFI_AP);
  WiFi.softAP("DIYODE-AP", "1234");
  server.begin(); // Start the HTTP Server
  Serial.print("Please connect to http://192.168.4.1/");

  server.on("/fwd", handleFWD);
  server.on("/back", handleBACK);
  server.on("/right", handleRIGHT);
  server.on("/left", handleLEFT);
  server.on("/moon", handleMOON);
  server.on("/flap", handleFLAP);
  server.on("/home", handleHOME);
  server.on("/updown", handleUPDOWN);
  server.on("/bend", handleBEND);
  server.begin(); //Start the server

  //Set the servo pins
  Otto.init(PIN_YL, PIN_YR, PIN_RL, PIN_RR, true);
  //Otto.sing(S_connection); //Otto wake up!
  Otto.home();
  delay(50);
}
void loop() {

  server.handleClient();
  delay(100);

}

