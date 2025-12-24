/*
    Simple CANMessage usage example
  
    Prints two CAN messages on alternate timings to serial output,
    demonstrates two ways to use the basic functionality including updating the message data.

    The constructor uses template <i> to define the number of bytes the CAN message will hold
*/

#include <CANMessage.h>


// A 4 byte CAN frame, with CAN ID 0x0B4, to be sent every 500ms. 
CANMessage<4> CAN_0B4(0x0B4, 500);
// An 8 byte CAN frame, with CAN ID 0x0B8, to be sent every 1000ms. 
CANMessage<8> CAN_0B8(0x0B8, 1000);

void setup() {
    // start a serial port output for debugging
    // try changing the baud rate it this doesn't work properly!
    Serial.begin(9600);  
}

void loop() {


    if(CAN_0B4.shouldSend()){ // check if ready to send
        // put the some data into the message
        CAN_0B4.message[0] = 0;
        CAN_0B4.message[1] = 1;
        CAN_0B4.message[2] = 2;
        CAN_0B4.message[3] = 3;
        CAN_0B4.sendMessage(); // calling sendMessage() will send the message
    }

    if(CAN_0B8.shouldSend()){ // check if ready to send
        // put the some data into the message
        CAN_0B8.message[0] = 0;
        CAN_0B8.message[1] = 1;
        CAN_0B8.message[2] = 2;
        CAN_0B8.message[3] = 3;
        CAN_0B8.message[4] = 4;
        CAN_0B8.message[5] = 5;
        CAN_0B8.message[6] = 6;
        CAN_0B8.message[7] = 7;
        CAN_0B8.sendMessage(); // calling sendMessage() will send the message
    }



}