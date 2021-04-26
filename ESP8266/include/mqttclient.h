#ifndef MQTTCLIENT_H_INCLUDED
#define MQTTCLIENT_H_INCLUDED

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

class MqttClient {

    private:

        // broker-url: eg, "broker.mqtt-dashboard.com", "iot.eclipse.org", etc
        const char *broker = "broker.mqtt-dashboard.com";
        const char *inTopic = "roboticMind/fromAndroid/";
        const char *outTopic = "roboticMind/fromESP8266/";
        
        // reconnecting logic when connection to server is lost
        void reconnect();


    public:
        
         /* connect to a wifi network with given ssid, password
            ssid: name of the wifi network to connect to
            password: <for above ssid>
        */
        void setup_wifi(char *ssid, char *password);

        // Get destn. lat & long. if available
        double *getDestinationCoordinates();

        boolean locationAvailable();

        void disconnect();

        void loop();
};

#endif