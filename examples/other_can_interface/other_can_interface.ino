/*
    Simple CANMessage usage example
  
    This example shows how to access the CANMessage data structure and send with using another interface,
    MCP2515 is used in this example but others can be substituted.

    The constructor uses template <i> to define the number of bytes the CAN message will hold
*/

#include <SPI.h>
#include <mcp2515_can.h>
#include <CANMessage.h>

// An 8 byte CAN frame, with CAN ID 0x0B8, to be sent every 100ms. 
CANMessage<8> CAN_0B8(0x0B8, 100);

// Define the I/O pin used for C/S of the CAN bus shield
const int SPI_CS_PIN = 9;

// Establish a CAN bus interface, in this case using the mcp2515 library and CAN shield from Seed Studio
mcp2515_can CANinterface(SPI_CS_PIN);

int count = 0; // Set an int variable to store a counter that increments each time the message is sent

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
  
    // 0x0B5 frame - check if ready to send
    if(CAN_0B8.shouldSend()){
        // do some other logic here

        // put the counter variable into the first two bytes of the CAN message
        CAN_0B8.message[0] = lowByte(count);
        CAN_0B8.message[1] = highByte(count);

        // Send the message using the CANinterface
        CANinterface.sendMsgBuf(CAN_0B8.CANID, 0, CAN_0B8.messageLength, CAN_0B8.message);
        count++;
    }
  
}

