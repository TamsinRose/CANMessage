/******************************************************************************
// Define the CANMessage class
******************************************************************************/
#ifndef CAN_MESSAGE_HEADER_FILE
#define CAN_MESSAGE_HEADER_FILE

#include <Arduino.h>
#include "CANMessageSender.h"
#include "CANMessageChecksumCalculator.h"
#include <SimpleCounter.h>



template <int MESSAGE_ARRAY_LEN>
class CANMessage{   
    private:
        bool hasSenderService;                          // Whether this CANMessage has a sender service or not
        bool hasChecksum;                               // Whether this CANMessage has a checksum feature or not
    public:
        unsigned long CANID;                            // The CAN ID of the message
        unsigned int messageLength;                     // The length (number of bytes) of the CAN message
        uint8_t message[MESSAGE_ARRAY_LEN];                // the array which will hold the CAN message, length determined at construct
        unsigned int sendingFrequency;                  // Sending frequency in millisenconds - how often the frame should be sent
        unsigned long lastSentTimestamp;                // Variable to store the timestamp when the CAN message was last sent
        SimpleCounter counter[2];                       // Two internal counters
        
        CANMessageSender& senderService;                // An instance of a sender service
        CANMessageChecksumCalculator& checksumService;  // An instance of a checksum calculating service    

        explicit CANMessage(unsigned long id, int freq, CANMessageSender& senderService, CANMessageChecksumCalculator& checksumCalculator);                   // Constructor, set the CAN ID and sending frequency. Message length determined from Template value MESSAGE_ARRAY_LEN

        explicit CANMessage(unsigned long id, int freq, CANMessageSender& senderService); 

        explicit CANMessage(unsigned long id, int freq, CANMessageChecksumCalculator& checksumCalculator);

        explicit CANMessage(unsigned long id, int freq); 

        bool updateTimestamp();                         // Method to manually update the lastSentTimeStamp - useful for debugging if we don't actually want to send the message each time

        bool updateCounters();                         // Method to manually increment the internal counter(s) - useful for debugging if we don't actually want to send the message each time
        
        bool shouldSend();                              // Method to determine if the message is ready to be sent based on the sending frequency & lastSentTimestamp

        bool sendMessage();                             // Method to (calulate checksum), send the message and update the lastSentTimestamp

        bool sendIfReady();                             // Integrated method to check the timestamp, then sendMessage() if ready to send
    
        bool outputToSerial(int idFormat = HEX, int dataFormat = HEX);        // Method to output to Serial

        bool setCounter(int counterId = 0, int startVal = 0, unsigned long maxVal = 14, int step = 1, int incAt = 1); // All in one method to setup an internal counter

        bool updateChecksum();                          // Method to calculate the checksum and insert into message
    };


#endif //CAN_MESSAGE_HEADER_FILE