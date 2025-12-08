/******************************************************************************
// Define the CANMessageChecksumCalculator class
// Further checksum types and calculations can be defined by inheriting from the base CANMessageChecksumCalculator class
******************************************************************************/
#ifndef CAN_MESSAGE_CHECKSUM_CALCULATOR_HEADER_FILE
#define CAN_MESSAGE_CHECKSUM_CALCULATOR_HEADER_FILE

#include <Arduino.h>

class CANMessageChecksumCalculator{
    public:
        int checksumStartBit;
        uint8_t messageHolder[8];
        CANMessageChecksumCalculator(int bitPos = 0) {};
        virtual uint8_t * calculateChecksum(unsigned long ID, uint8_t *message, int messageLength);
};

class CANMessageChecksumCalculatorDefault : public CANMessageChecksumCalculator{
    public:
        CANMessageChecksumCalculatorDefault(int bitPos = 0) {
            checksumStartBit = bitPos;
            for(int i = 0; i < 8; i++){
                messageHolder[i] = 0;
            }
        };
        uint8_t * calculateChecksum(unsigned long ID, uint8_t *message, int messageLength);
};


class CANMessageChecksumCalculator8BitSumIncID : public CANMessageChecksumCalculator{
    public:
        CANMessageChecksumCalculator8BitSumIncID(int bitPos = 0) {
            checksumStartBit = bitPos;
            for(int i = 0; i < 8; i++){
                messageHolder[i] = 0;
            }
        };
        uint8_t * calculateChecksum(unsigned long ID, uint8_t *message, int messageLength);
};

class CANMessageChecksumCalculator8BitSumNoID : public CANMessageChecksumCalculator{
    public:
        CANMessageChecksumCalculator8BitSumNoID(int bitPos = 0) {
            checksumStartBit = bitPos;
            for(int i = 0; i < 8; i++){
                messageHolder[i] = 0;
            }
        };
        uint8_t * calculateChecksum(unsigned long ID, uint8_t *message, int messageLength);
};

class CANMessageChecksumCalculator4BitSumIncID : public CANMessageChecksumCalculator{
    public:
        CANMessageChecksumCalculator4BitSumIncID(int bitPos = 0) {
            checksumStartBit = bitPos;
            for(int i = 0; i < 8; i++){
                messageHolder[i] = 0;
            }
        };
        uint8_t * calculateChecksum(unsigned long ID, uint8_t *message, int messageLength);
};

class CANMessageChecksumCalculator4BitSumNoID : public CANMessageChecksumCalculator{
    public:
        CANMessageChecksumCalculator4BitSumNoID(int bitPos = 0) {
            checksumStartBit = bitPos;
            for(int i = 0; i < 8; i++){
                messageHolder[i] = 0;
            }
        };
        uint8_t * calculateChecksum(unsigned long ID, uint8_t *message, int messageLength);
};

class CANMessageChecksumCalculatorJ1939RuleC : public CANMessageChecksumCalculator{
    public:
        CANMessageChecksumCalculatorJ1939RuleC(int bitPos = 0) {
            checksumStartBit = bitPos;
            for(int i = 0; i < 8; i++){
                messageHolder[i] = 0;
            }
        };
        uint8_t * calculateChecksum(unsigned long ID, uint8_t *message, int messageLength);
};

class CANMessageChecksumCalculatorJ1939RuleD : public CANMessageChecksumCalculator{
    public:
        CANMessageChecksumCalculatorJ1939RuleD(int bitPos = 0) {
            checksumStartBit = bitPos;
            for(int i = 0; i < 8; i++){
                messageHolder[i] = 0;
            }
        };
        uint8_t * calculateChecksum(unsigned long ID, uint8_t *message, int messageLength);
};

class CANMessageChecksumCalculatorJ1939RuleE : public CANMessageChecksumCalculator{
    public:
        CANMessageChecksumCalculatorJ1939RuleE(int bitPos = 0) {
            checksumStartBit = bitPos;
            for(int i = 0; i < 8; i++){
                messageHolder[i] = 0;
            }
        };
        uint8_t * calculateChecksum(unsigned long ID, uint8_t *message, int messageLength);
};

#endif //CAN_MESSAGE_CHECKSUM_CALCULATOR_HEADER_FILE