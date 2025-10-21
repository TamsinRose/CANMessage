/*
    Simple CANMessage usage example
  
    Sends two empty CAN messages on alternate timings,
    demonstrates two ways to use the basic sending functionality.

    First example uses the sendIfReady() method which checks the timing and sends only if the sending interval has elapsed.
    Second example breaks this into two sections so some conditional logic can execute if the sending interval has elapsed, 
    and then sends the message

    The constructor uses template <i> to define the number of bytes the CAN message will hold
*/

#include <SPI.h>
#include <mcp2515_can.h>
#include <CANMessage.h>

// An 8 byte CAN frame, with CAN ID 0x0B8, to be sent every 100ms. 
CANMessage<8> CAN_0B8(0x0B8, 100);
// A 5 byte CAN frame, with CAN ID 0x0B5, to be sent every 20ms
CANMessage<5> CAN_0B5(0x0B5, 20);

// Define the I/O pin used for C/S of the CAN bus shield
const int SPI_CS_PIN = 9;

// Establish a CAN bus interface, in this case using the mcp2515 library and CAN shield from Seed Studio
mcp2515_can CANinterface(SPI_CS_PIN);

void setup() {

    // start a serial port output for debugging
    Serial.begin(9600);

    // initialise the CAN bus interface, in this case 500kbps
    while (CAN_OK != CANinterface.begin(CAN_500KBPS)) {  // init can bus : baudrate = 500k
        Serial.println("CAN init fail, retry...");
        delay(100);
    }
    Serial.println("CAN init ok!");

}

void loop() {
  
    // 0x0B5 frame - Convenient all in one method to check the timing and send if the sending interval has elapsed
    CAN_0B5.sendIfReady(CANinterface);

    // 0x0B8 frame - does same as above but breaks it down to allow some conditional logic to excecute
    if(CAN_0B8.shouldSend()){
        // do some other logic here such as updating the message data
        CAN_0B8.outputToSerial(); // log to serial, for debugging 
        CAN_0B8.sendMessage(CANinterface);
    }

}