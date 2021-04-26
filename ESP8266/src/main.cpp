/* 
  **************************************************************
  Main controlling code for NodeMCU-12E
  
  @author Tanmoy Sarkar
  @date 26/04/2021 14:01
  **************************************************************


  This code is the only interface between the user and the robot through NodeMCU-12E (ESP8266) wi-fi module.
  
  It performs the following tasks (serially ordered):
    1) Connects to a wifi network (internet required) to be able to accept commands from smartphone users
    
    2) Accesses the internet to connect to a MQTT broker and subscribes to incoming topics
    
    3) Receives commands:
        If in MANUAL MODE: Receives direction commands from user (needs access to internet for the WHOLE session)
        If in AUTO mode (default): Receives destination location from user (internet required UNTIL co-ordinates are received)
    
    4) Calibrates the compass (done automatically)

    5) Activates the GPS module and gets the current location

    6) Calculates heading direction (by periodically retrieving location from GPS module) and moves alongside continuosly evaluating 
       obstacle distances from ultrasonic sensors.

    7) Sends movement command to Arduino Uno (which is in charge of motor drivers).
*/

#include "mqttclient.h"

boolean _isAutoMode = true;

double *destn = NULL;

void setup() {
  
  if(_isAutoMode) {
    MqttClient _mqttClient;
  // Connect to WiFi network and MQTT server
  _mqttClient.setup_wifi("ssid", "password");

  // Loop until destination is available
  while(!_mqttClient.locationAvailable()) {
      _mqttClient.loop();
       delay(100);
  }

  // Get destination from user
  destn = _mqttClient.getDestinationCoordinates();
  // Disconnect
  _mqttClient.disconnect();
  }
}

void loop() {

}