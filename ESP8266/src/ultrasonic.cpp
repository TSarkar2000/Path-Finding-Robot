#include "ultrasonic.h"

void Ultrasonic::init(int pins[], int nSensors) {
    this->pins = pins;
    this->nSensors = nSensors;
}

float Ultrasonic::calculateDistance(int echo, int trig) {
    // clear trigger pin
    digitalWrite(trig, LOW);
    delayMicroseconds(2);
    
    // set trigger pin high for 10uS
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);
    
    // Reads the echoPin, returns the sound wave travel time in microseconds
    long duration = pulseIn(echo, HIGH);

    return (float) duration * 0.034 / 2; // cm
}

float* Ultrasonic::getDistanceReadings() {
    float *dist = (float*) malloc(nSensors * 2 * sizeof(float));
    for (int i = 0; i < nSensors; i++)
        dist[i] = calculateDistance(pins[i], pins[i+1]);
    
    return dist;
}