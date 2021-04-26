// Handles all wire commands (sending / receiving data to / from Arduino)

#ifndef UNO_H_INCLUDED
#define UNO_H_INCLUDED

#include <Arduino.h>
#include <Wire.h>

#define MOVE_FORWARD 1
#define MOVE_BACKWARD 2
#define TURN_LEFT 3
#define TURN_RIGHT 4
#define HALT 5

class Uno {

    public:

        void init();
        
        //  For common commands, e.g, move forward, left, right, etc..
        void sendToArduino(int command);

        /*
            For mqtt based commands
                payload: input data array in bytes
                length: data length
        */
        void sendToArduino(byte *payload, unsigned int length);
};

#endif