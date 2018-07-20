# Wemos

WIFI CONTROLLED ROBOT
ADDITIONAL PARTS REQUIRED:	JAYCAR	ALTRONICS	CORE ELECTRONICS
1 × Wemos D1 or Similar ESP8266-Based Board	XC3802	-	ADA2471
1 × Suitable Prototype Board	XC3850	-	-
1 x Ultrasonic Sensor	XC4442	Z6322	CE05112
1 × Solid Core Hookup Wire Pack	WH3025	-	PRT-08026
 fritzing
Note: Connections to WiFi Mini shown, use the breakout image references if using the breakout board.
 diagram schematic
This upgraded WiFi version is based on the ESP8266. These are commonly available as a Wemos D1, or WiFi Mini, or various other names, depending on where you purchase it from.

Ultimately at their core, they're all based around the same ESP8266, just be aware that they may not have precisely the same pinouts.

With the addition of WiFi, we can set it up as a wireless access point. Using your smartphone or tablet, you can then drive (that is, walk) your biped robot around!

One major difference with an ESP8266-based board is that they run on 3.3V. This isn't a major issue, but it can make wiring a little more complex. If we try and run the servo motors from 3.3V, they're not going to go too far at all.

However the Wemos board does include a voltage regulator to reduce our 6V from the battery pack, to the 3.3V it requires to run. This is handy, as you can connect everything to the 6V pack directly, while the Wemos will protect itself from the higher voltage.


 
PROTOTYPE BOARD BREAKOUT BOARD
ESP8266 chips themselves aren't always terribly friendly to use, but the awesome D1 / WiFi Mini packages make it easier, and often have an available prototyping shield we can use to build our project on. This gives us a solderable, hard-wearing platform to work with. Awesome!

First, you'll usually need to solder up the prototyping board. Install the header pins to connect on top of your D1 board. From there, we're going to use a similar approach to the Nano breakout board, which provides us with easy-to-use power + data pin headers.

Depending on where you purchased your prototype board, you may or may not have header strip included. If you don't, you may need additional header strip, which is not included in the parts list. If you already have your header strip, you're in luck!

 protoshield protoshield
We need to start by creating a breakout board. In this case, we are using the XC3850 prototype board from Jaycar Electronics. You'll find these breakout boards in various incarnations from a variety of retailers. Place the header pins onto the board (see image). We have borrowed some ideas from the Arduino servo breakout boards, and so have the ground, power and signal rails all in a row. In addition, we have lined up the power and ground for the ultrasonic sensor, and the power in for the battery. The Wemos D1 Mini has a built-in 3.3V regulator, so we can feed it 5V to 6V from the batteries without issue. The batteries also feed the servos directly.

With the headers in place, run a piece of solid wire across all the header pins from the battery header. Then from the other end connect to the 5V connector for the Wemos. Repeat for the ground.Starting from the top, solder and connect from D5 to D8.

Finally, we need to connect the ultrasonic trigger to D2 and the echo to D3, as well as power. The prototype shield does make life easier for distributing power, but it's not entirely essential.

Attach the servos as per the image, connecting the hips and ankles, and connect the battery. If you still have the auto-homing code loaded on your Wemos, you may see the servos reset their positioning when attaching power.

THE CODE / SETUP
Using the Wemos D1 Mini (or equivalent), we have set up the system to operate as a wireless access point (AP), with Arduino providing a web server interface also. By doing this, we can operate the robot anywhere, even without a WiFi network.

You'll need to locate the "wifi_ap.ino" in the digital resources, and compile it to your Wemos.

The code below has been truncated for clarity. Please see the full code in the provided files.

Our code starts out with the normal importing of the libraries into the system. We then move to our defined functions for making the robot do various functions. These are all called later from the main loop. Below is an example of the basic syntax used to make the robot move, dance or home itself. The only line here that interacts with the robot is the final line, which calls the otto object to home the servos.

The first line is a serial output to give us feedback that the command is working. The next four lines are all designed to tell the system that the command has been received and is being executed correctly.

void handleHOME() {
  Serial.println(“Home”);
  String message;
  message += “{ ”success”: “;
  message += “1 }”;
  server.send(200, “text/plain”, message );
  Otto.home();
}
From the declarations we move on to the setup function of the code. In this case, we need to setup and start the access point. In this instance, we have given it the name of DIYODE-AP and the password of “12341234”; of course, you can change this. We then start the server object. The final line outputs the default IP address to the serial monitor.

WiFi.mode(WIFI_AP);
WiFi.softAP(“DIYODE-AP”, “12341234”);
server.begin(); // Start the HTTP Server
Serial.print(“Please connect to http://192.168.4.1/“);
After this, we then attach our commands to our URLs. In this case whenever the AP receives the URL that is “/home” it will call the “handleHOME” function that we discussed earlier. This is repeated for the various commands we will be using.

server.on(“/home”, handleHOME);
For the final part of our setup, we start the Otto object and assign the pins used for the servos before homing them.

//Set the servo pins
Otto.init(PIN_YL, PIN_YR, PIN_RL, PIN_RR, true);
Otto.home();
delay(50);
This is one of the simplest main loops we have ever done; it simply waits for the server to see what command it has been sent. This executes because of the server.on functions that we wrote earlier. After a slight delay, the code will repeat, to listen again.

void loop() {
  server.handleClient();
  delay(100);
{
We have included a basic web app to use as the robot’s control. It is located in the web app directory. When you extract and open the file, you’ll see we have a basic move forward, back, left and right, as well as other fun functions.

With the code loaded and your smartphone at the ready, it's time to power everything up and drive (or is that walk?) our robot!

Note that you can use any WiFi capable device with a modern web browser. That includes smartphones, tablets, and laptops.

TESTING
With your device connected to your regular WiFi, use your favourite web browser to navigate to https://diyode.io/013html - this will load the web app into your browser. To make it easy to find later if required, save it to your home screen or bookmark bar.

You will have a prompt labelled SETUP, asking for an IP address. Don't do anything with that just yet. We need to connect to your robot's WiFi network first.

 web app
Go to your device's WiFi settings (that is the control device, not the robot) and locate DIYODE-AP, which should auto-discover, and click/tap connect. When prompted, enter the password we set "12341234". You can change this in your code to something more difficult, but in reality, we're not controlling spacecraft here.

Give everything a few seconds to settle down, and go back to your web browser. Click / tap "Continue". The IP address required should be the same as what we have defaulted here, unless you changed it in the code. This is one benefit of using the Wemos as the access point rather than going through your router - everything is a little more predictable.

THE REMOTE CONTROL
We have built a few "standard" functions such as moving forward or backward. We also have a few fun functions to make our robot do a few funny actions such as flap feet, or moon everyone.

The responsiveness of the remote control is rather good. This is one additional benefit of the access point method of connection. Using a standard WiFi router would simply increase latency, which would in turn reduce the response time of our robot.

It should be noted however that the remote control triggers specific routines (such as take steps forward, flap feet), and these routines must finish before a new routine can be started.

It is possible to change this behaviour, but it increases the complexity of the code significantly, and introduces new challenges with servo positioning also. Allowing routines to complete automatically resolves many of these issues.

 remote control
WHERE TO FROM HERE?
There is so much more than you can do with this framework. The very idea with the Otto framework is to modify, change, update and share. There any many different sensors and “things” that exist, and there many different variations of this project that could incorporate them all!

Touch sensors, buzzers and sound sensors are all supported right out of the box; even Bluetooth modules are supported with the standard build.

Perhaps you can scale-up the robot to be a personal companion, then train him to go and fetch a drink from the fridge with a preset routine? Then again - he would need some arms. We'll leave those considerations with you!
