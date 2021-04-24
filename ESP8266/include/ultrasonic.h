/*
 * This class handles all 5 ultrasonic sensors
*/

#ifndef ULTRASONIC_H_INCLUDED
#define ULTRASONIC_H_INCLUDED

#include <Arduino.h>
#include <malloc.h>

class Ultrasonic {
    
    private:
        int *pins;
        int nSensors;
        float calculateDistance(int echo, int trigger);
    
    public:
    /*
        Pins have to be in the following format:
            Sensor1: echo,trigger
            Sensor2: echo, trigger
             & so on..
        Thus array must be: echo1, trigger1, echo2, trigger2,.....
    */
        void init(int pins[], int nSensors);

    /*
        Get calculated distances for each sensor in the form of an array (all in cm)
            Output: distanceBySensor1, distanceBySensor2,.... 
    */
        float* getDistanceReadings();

};

#endif