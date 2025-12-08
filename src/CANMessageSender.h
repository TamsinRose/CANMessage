/******************************************************************************
// Define the CANMessageSender class
******************************************************************************/
#ifndef CAN_MESSAGE_SENDER_HEADER_FILE
#define CAN_MESSAGE_SENDER_HEADER_FILE

#include <Arduino.h>

class CANMessageSender{
    public:
        // int checksumStartBit;
        // byte messageHolder[8];
        CANMessageSender() {};
        virtual bool send(unsigned long ID, uint8_t *message, int messageLength);
};

class CANMessageSenderSerialPrint : public CANMessageSender{
    public:
        CANMessageSenderSerialPrint() {};
        bool send(unsigned long ID, uint8_t *message, int messageLength){
            Serial.print(ID, HEX);
            for(int i = 0; i < messageLength; i++){
                Serial.print(" ");
                if(message[i] == 0){
                    Serial.print("00");
                }
                else if(message[i] < 0x10){
                    Serial.print("0");
                    Serial.print(message[i], HEX);
                }
                else{
                    Serial.print(message[i], HEX);
                }
                
            }
            Serial.println();
        };
};



#endif //CAN_MESSAGE_SENDER_HEADER_FILE