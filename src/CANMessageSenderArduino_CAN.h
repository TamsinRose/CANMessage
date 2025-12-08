/******************************************************************************
// Define the CANMessageSender class
// This CANMessageSender wraps an interface provided by Aurduino_CAN.h
******************************************************************************/
#ifndef CAN_MESSAGE_SENDER_ARDUINO_CAN_HEADER_FILE
#define CAN_MESSAGE_SENDER_ARDUINO_CAN_HEADER_FILE

#include <Arduino.h>
#include "CANMessageSender.h"
#include <Arduino_CAN.h>

class CANMessageSenderArduino_CAN : public CANMessageSender{
    public:
        CANMessageSenderArduino_CAN()
        {};
        bool send(unsigned long ID, uint8_t *message, int messageLength){
            CanMsg const msg(CanStandardId(ID), sizeof(message), message);
            
            if (int const rc = CAN.write(msg); rc < 0){
                Serial.print  ("CAN.write(...) failed with error code ");
                Serial.println(rc);
            }
            return true;
        };
};

#endif //CAN_MESSAGE_SENDER_ARDUINO_CAN_HEADER_FILE