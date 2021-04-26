#include "mqttclient.h"
#include <malloc.h>

void callback(char*, uint8_t*, unsigned int);

WiFiClient _wifiClient;
PubSubClient _client(_wifiClient);

double lat, lon;
boolean cAvailable = false;

void MqttClient::setup_wifi(char *ssid, char *password) {
    // Connect to a wifi network
    WiFi.begin(ssid, password);
   // Wait until wifi is connected
    while(WiFi.status() != WL_CONNECTED) {
        delay(500);
    }

    _client.setServer(broker, 1883);
    _client.setCallback(callback);

    delay(100);
}

void callback(char* topic, uint8_t* payload, unsigned int length) {
    if((char)payload[0] == 'G') {
        String temp = "";
        for(unsigned int i = 1; i < length; i++) {
            if((char)payload[i] != ',') {
                temp += (char)payload[i];
            } else {
                lat = temp.toDouble();
                temp = "";
                temp += (char)payload[i];
            }
        }
        lon = temp.toDouble();
        cAvailable = true;
    }
}

void MqttClient::reconnect() {
   // Blocking call
    while(!_client.connected()) {
        // create a random clientID
        String prefix = "ESP8266Client-";
        prefix += String(random(0xffff), HEX);
        // If connected, subscribe to topics
        if(_client.connect(prefix.c_str())) {
            _client.publish(outTopic, "NodeMCU connected! Waiting for destination coordinates...");
            _client.subscribe(inTopic);
        }
        else
            delay(5000); // wait 5 seconds before retrying
    }
}

double* MqttClient::getDestinationCoordinates() {
    double *destn = (double*) malloc(2*sizeof(double));
    if(cAvailable) {
        destn[0] = lat;
        destn[1] = lon;
        return destn;
    }
    return NULL;
}

void MqttClient::locationAvailable() {
    return cAvailable;
}

void MqttClient::disconnect() {
    if(cAvailable)
        _client.publish(outTopic, "Destination received. Now disconnecting NodeMCU-12E...");
  
    _client.disconnect();
}

void MqttClient::loop() {
  if(!_client.connected())
        reconnect();

    _client.loop();
}