/******************************************************************************
// Define the CANMessage class
******************************************************************************/
#ifndef CAN_MESSAGE_HEADER_FILE
#define CAN_MESSAGE_HEADER_FILE
#include "Arduino.h"
#include "mcp2515_can.h"

template <int MESSAGE_ARRAY_LEN>
class CANMessage{
    public:
        int CANID;                                      // The CAN ID of the message
        int messageLength;                              // The length (number of bytes) of the CAN message
        unsigned char message[MESSAGE_ARRAY_LEN];       // the array which will hold the CAN message, length determined at construct
        int sendingFrequency;                           // Sending frequency in millisenconds - how often the frame should be sent
        int lastSentTimestamp;                          // Variable to store the timestamp when the CAN message was last sent

        CANMessage(int id, int freq);                   // Constructor, set the CAN ID and sending frequency. Message length determined from Template value MESSAGE_ARRAY_LEN

        bool updateTimestamp();                         // Method to manually update the lastSentTimeStamp - useful for debugging if we don't actually want to send the message each time

        bool shouldSend();                               // Method to determine if the message is ready to be sent based on the sending frequency & lastSentTimestamp

        bool sendMessage(mcp2515_can CANInterface);     // Method to send the message and update the lastSentTimestamp, must include an mcp2525_can interface object to send the message 

        bool sendIfReady(mcp2515_can CANInterface);     // Integrated method to check the timestamp, send if ready, update the timestamp

};

#endif //CAN_MESSAGE_HEADER_FILE