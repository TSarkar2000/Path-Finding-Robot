#ifndef MQTTCLIENT_H_INCLUDED
#define MQTTCLIENT_H_INCLUDED

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

class MqttClient {

    private:
        char *ssid, *password, *broker, *subscription;
        
        // connect to a wifi network with given ssid, password
        void setup_wifi();

        // reconnecting logic when connection to server is lost
        void reconnect();


    public:
        /*
            ssid: name of the wifi network to connect to
            password: <for above ssid>
            broker-url: eg, "broker.mqtt-dashboard.com", "iot.eclipse.org", etc
        */
        MqttClient(char* ssid, char* password, char* broker);
        
        // topics to subscribe to (incoming)
        void subscribe(char *topics);

        /*
            topic: name of the topic to publish to
            payload: message to be published
            length: message length
        */
        void callback(char *topic, byte *payLoad, unsigned int length);

};

#endif