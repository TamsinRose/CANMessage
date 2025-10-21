/*
    Simple CANMessage usage example
  
    Prints two CAN messages on alternate timings to serial output,
    demonstrates two ways to use the basic functionality including updating the message data.

    The constructor uses template <i> to define the number of bytes the CAN message will hold
*/

#include <CANMessage.h>

// An 8 byte CAN frame, with CAN ID 0x0B8, to be sent every 1000ms. 
CANMessage<8> CAN_0B8(0x0B8, 1000);
// An 4 byte CAN frame, with CAN ID 0x0B8, to be sent every 500ms. 
CANMessage<4> CAN_0B4(0x0B4, 500);



//define an empty int variable to store the value of a count that increments each time 0x0B8 is sent
int counter = 0;

// Establish a CAN bus interface, in this case using the mcp2515 library and CAN shield from Seed Studio

void setup() {
    Serial.begin(9600);  // start a serial port output for debugging

}

void loop() {


    if(CAN_0B4.shouldSend()){ // check if ready to send
        // put the counter variable into the first two bytes of the CAN message
        CAN_0B4.message[0] = lowByte(counter);
        CAN_0B4.message[1] = highByte(counter);
        
        CAN_0B4.sendMessage(); // calling sendMessage() without arguments will default to serial output, in HEX format, and update timestamp
    }

    // Advanced usage of serial output
    if(CAN_0B8.shouldSend()){ // check if ready to send 

        // put the counter variable into the first two bytes of the CAN message
        CAN_0B8.message[0] = lowByte(counter);
        CAN_0B8.message[1] = highByte(counter);

        CAN_0B8.outputToSerial(HEX,BIN); // outputToSerial can take any valid arduino Serial.print() format specifiers. arg1 specifies format for the CAN ID, arg2 for the data.
        // CAN_timestamp.outputToSerial(DEC, HEX);
        // CAN_timestamp.outputToSerial(); // default format arguments are HEX, HEX.

        CAN_0B8.updateTimestamp(); // Need to call the updateTimestamp function separately as outputToSerial() does not update this directly, meaning the message would be sent every loop iteration if not called.
        counter++;
    }

}