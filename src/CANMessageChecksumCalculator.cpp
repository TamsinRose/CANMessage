#include "CANMessageChecksumCalculator.h"


uint8_t * CANMessageChecksumCalculatorDefault:: calculateChecksum(unsigned long ID, uint8_t *message, int messageLength){
    for(int i = 0; i < 8 ; i ++){
        messageHolder[i] = message[i];
    }
    return messageHolder;
}

uint8_t * CANMessageChecksumCalculator8BitSumIncID:: calculateChecksum(unsigned long ID, uint8_t *message, int messageLength){
    int checksumBits = 8;
    int checksum = 0;
    for(int i = 0; i < 8 ; i ++){
        messageHolder[i] = message[i];
    }
    int byteContainingChecksum = checksumStartBit / 8;
    messageHolder[byteContainingChecksum] = 0x00;
    for(int i = 0; i < messageLength; i++){
        checksum = checksum + messageHolder[i];
    }
    checksum = checksum + ID;
    checksum = (highByte(checksum) + lowByte(checksum)) & 0xFF;
    messageHolder[byteContainingChecksum] = checksum;
    return messageHolder;
}

uint8_t * CANMessageChecksumCalculator8BitSumNoID:: calculateChecksum(unsigned long ID, uint8_t *message, int messageLength){
    int checksumBits = 8;
    int checksum = 0;
    for(int i = 0; i < 8 ; i ++){
        messageHolder[i] = message[i];
    }
    int byteContainingChecksum = checksumStartBit / 8;
    messageHolder[byteContainingChecksum] = 0x00;
    for(int i = 0; i < messageLength; i++){
        checksum = checksum + messageHolder[i];
    }
    //checksum = checksum + ID;
    checksum = (highByte(checksum) + lowByte(checksum)) & 0xFF;
    messageHolder[byteContainingChecksum] = checksum;
    return messageHolder;
}

uint8_t * CANMessageChecksumCalculator4BitSumIncID:: calculateChecksum(unsigned long ID, uint8_t *message, int messageLength){
    int checksumBits = 4;
    int checksum = 0;
    for(int i = 0; i < 8 ; i ++){
        messageHolder[i] = message[i];
    }
    int byteContainingChecksum = checksumStartBit / 8;
    for(int i = (checksumStartBit % 8); i < checksumBits; i++){
        bitWrite(messageHolder[byteContainingChecksum], i, 0);
    }
    for(int i = 0; i < messageLength; i++){
        checksum = checksum + messageHolder[i];
    }
    checksum = checksum + ID;
    checksum = (highByte(checksum) + lowByte(checksum)) & 0xFF;
    checksum = ((checksum >> 4) + (checksum & 0x0F)) & 0x0F;
    if(checksumStartBit % 8 == 4){
        checksum = (checksum & 0x0F) << 4;
        messageHolder[byteContainingChecksum] = messageHolder[byteContainingChecksum] | checksum ;
    }
    else if(checksumStartBit % 8 == 0){
        messageHolder[byteContainingChecksum] = messageHolder[byteContainingChecksum] | checksum ;
    }
    return messageHolder;
}

uint8_t * CANMessageChecksumCalculator4BitSumNoID:: calculateChecksum(unsigned long ID, uint8_t *message, int messageLength){
    int checksumBits = 4;
    int checksum = 0;
    for(int i = 0; i < 8 ; i ++){
        messageHolder[i] = message[i];
    }
    int byteContainingChecksum = checksumStartBit / 8;
    for(int i = (checksumStartBit % 8); i < checksumBits; i++){
        bitWrite(messageHolder[byteContainingChecksum], i, 0);
    }
    for(int i = 0; i < messageLength; i++){
        checksum = checksum + messageHolder[i];
    }
    //checksum = checksum + ID;
    checksum = (highByte(checksum) + lowByte(checksum)) & 0xFF;
    checksum = ((checksum >> 4) + (checksum & 0x0F)) & 0x0F;
    if(checksumStartBit % 8 == 4){
        checksum = (checksum & 0x0F) << 4;
        messageHolder[byteContainingChecksum] = messageHolder[byteContainingChecksum] | checksum ;
    }
    else if(checksumStartBit % 8 == 0){
        messageHolder[byteContainingChecksum] = messageHolder[byteContainingChecksum] | checksum ;
    }
    return messageHolder;
}

uint8_t * CANMessageChecksumCalculatorJ1939RuleC:: calculateChecksum(unsigned long ID, uint8_t *message, int messageLength){
    int checksumBits = 4;
    int checksum = 0;
    for(int i = 0; i < 8 ; i ++){
        messageHolder[i] = message[i];
    }
    int byteContainingChecksum = checksumStartBit / 8;
    for(int i = (checksumStartBit % 8); i < checksumBits; i++){
        bitWrite(messageHolder[byteContainingChecksum], i, 0);
    }
    for(int i = 0; i < messageLength; i++){
        checksum = checksum + messageHolder[i];
    }
    checksum = checksum + ((ID) & 0xFF);
    checksum = checksum + (((ID) >> 8) & 0xFF);
    checksum = checksum + (((ID) >> 16) & 0xFF);
    checksum = checksum + (((ID) >> 24) & 0xFF);
    checksum = ((checksum >> 4) + checksum) & 0x0F;
    if(checksumStartBit % 8 == 4){
        checksum = (checksum & 0x0F) << 4;
        messageHolder[byteContainingChecksum] = messageHolder[byteContainingChecksum] | checksum ;
    }
    else if(checksumStartBit % 8 == 0){
        messageHolder[byteContainingChecksum] = messageHolder[byteContainingChecksum] | checksum ;
    }
    return messageHolder;
}

uint8_t * CANMessageChecksumCalculatorJ1939RuleD:: calculateChecksum(unsigned long ID, uint8_t *message, int messageLength){
    int checksumBits = 4;
    int checksum = 0;
    for(int i = 0; i < 8 ; i ++){
        messageHolder[i] = message[i];
    }
    int byteContainingChecksum = checksumStartBit / 8;
    messageHolder[byteContainingChecksum] = 0x00;
    for(int i = 0; i < messageLength; i++){
        checksum = checksum + messageHolder[i];
    }
    checksum = checksum + ((ID) & 0xFF);
    checksum = checksum + (((ID) >> 8) & 0xFF);
    checksum = checksum + (((ID) >> 16) & 0xFF);
    checksum = checksum + (((ID) >> 24) & 0xFF);
    checksum = checksum & 0xFF;
    messageHolder[byteContainingChecksum] = checksum;
    return messageHolder;
}

uint8_t * CANMessageChecksumCalculatorJ1939RuleE:: calculateChecksum(unsigned long ID, uint8_t *message, int messageLength){
    int checksumBits = 4;
    int checksum = 0;
    for(int i = 0; i < 8 ; i ++){
        messageHolder[i] = message[i];
    }
    int byteContainingChecksum = checksumStartBit / 8;
    for(int i = (checksumStartBit % 8); i < checksumBits; i++){
        bitWrite(messageHolder[byteContainingChecksum], i, 0);
    }
    for(int i = 0; i < messageLength; i++){
        checksum = checksum + messageHolder[i];
    }
    checksum = checksum + ((ID) & 0xFF);
    checksum = checksum + (((ID) >> 8) & 0xFF);
    checksum = checksum + (((ID) >> 16) & 0xFF);
    checksum = checksum + (((ID) >> 24) & 0xFF);
    checksum = (((checksum >> 6) & 0x03) + (checksum >> 3) + checksum) & 0x07;
    if(checksumStartBit % 8 == 4){
        checksum = (checksum & 0x0F) << 4;
        messageHolder[byteContainingChecksum] = messageHolder[byteContainingChecksum] | checksum ;
    }
    else if(checksumStartBit % 8 == 0){
        messageHolder[byteContainingChecksum] = messageHolder[byteContainingChecksum] | checksum ;
    }
    return messageHolder;
}



