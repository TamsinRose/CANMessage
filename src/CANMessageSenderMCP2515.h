/******************************************************************************
// Define the CANMessageSender class
// This CANMessageSender wraps an interface provided by mcp2515_can.h
******************************************************************************/
#ifndef CAN_MESSAGE_SENDER_MCP2515_HEADER_FILE
#define CAN_MESSAGE_SENDER_MCP2515_HEADER_FILE

#include <Arduino.h>
#include "CANMessageSender.h"
#include "mcp2515_can.h" 

class CANMessageSenderMCP2515 : public CANMessageSender{
    public:
        mcp2515_can& interface;
        CANMessageSenderMCP2515(mcp2515_can& CANinterface):
        interface{CANinterface}{  
        };
        bool send(unsigned long ID, uint8_t *message, int messageLength){
            interface.sendMsgBuf(ID, 0, messageLength, message);
            return true;
        };
};

#endif //CAN_MESSAGE_SENDER_MCP2515_HEADER_FILE