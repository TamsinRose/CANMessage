#include "CANMessageChecksumCalculator.h"


byte * CANMessageChecksumCalculatorDefault:: calculateChecksum(unsigned long ID, byte *message, int messageLength){
    for(int i = 0; i < 8 ; i ++){
        messageHolder[i] = message[i];
    }
    return messageHolder;
}

byte * CANMessageChecksumCalculator8BitSumIncID:: calculateChecksum(unsigned long ID, byte *message, int messageLength){
    int checksumBits = 8;
    int checksum = 0;
    for(int i = 0; i < 8 ; i ++){
        messageHolder[i] = message[i];
    }
    int byteContainingChecksum = checksumStartBit / 8;
    // for(int i = (checksumStartBit % 8); i < checksumBits; i++){
    //     bitWrite(messageHolder[byteContainingChecksum], 8-i, 0);
    // }
    messageHolder[byteContainingChecksum] = 0x00;
    for(int i = 0; i < messageLength; i++){
        checksum = checksum + messageHolder[i];
    }
    checksum = checksum + ID;
    checksum = (highByte(checksum) + lowByte(checksum)) & 0xFF;
    messageHolder[byteContainingChecksum] = checksum;
    return messageHolder;
}

byte * CANMessageChecksumCalculator8BitSumNoID:: calculateChecksum(unsigned long ID, byte *message, int messageLength){
    int checksumBits = 8;
    int checksum = 0;
    for(int i = 0; i < 8 ; i ++){
        messageHolder[i] = message[i];
    }
    int byteContainingChecksum = checksumStartBit / 8;
    // for(int i = (checksumStartBit % 8); i < checksumBits; i++){
    //     bitWrite(messageHolder[byteContainingChecksum], 8-i, 0);
    // }
    messageHolder[byteContainingChecksum] = 0x00;
    for(int i = 0; i < messageLength; i++){
        checksum = checksum + messageHolder[i];
    }
    //checksum = checksum + ID;
    checksum = (highByte(checksum) + lowByte(checksum)) & 0xFF;
    messageHolder[byteContainingChecksum] = checksum;
    return messageHolder;
}

byte * CANMessageChecksumCalculator4BitSumIncID:: calculateChecksum(unsigned long ID, byte *message, int messageLength){
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

byte * CANMessageChecksumCalculator4BitSumNoID:: calculateChecksum(unsigned long ID, byte *message, int messageLength){
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

