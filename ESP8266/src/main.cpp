#include "mqttclient.h"
#include "ultrasonic.h"
#include "wired.h"

Ultrasonic sensors;

void setup() {
  int arr[] = {D0, D1, D2, D3, D4, D5, D6, D7, D8, D9 , D10};
  sensors.init(arr, 5);

  Serial.begin(9600);
}

void loop() {
  float* dist = sensors.getDistanceReadings();
  for (int i = 0; i < 5; i++)
  {
    Serial.println(dist[i]);
  }
  
  free(dist);
  delay(1000);
}