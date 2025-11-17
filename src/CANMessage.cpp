/******************************************************************************
// Define the CANMessage class methods
******************************************************************************/

#include "CANMessage.h"

// Constructor, set the CAN ID and sending frequency. Message length determined from Template value MESSAGE_ARRAY_LEN
// Including an instance of checksum calulating service
template <int MESSAGE_ARRAY_LEN>
CANMessage<MESSAGE_ARRAY_LEN>::CANMessage(unsigned long id, int freq, CANMessageChecksumCalculator& checksumCalculator):
checksumService{checksumCalculator}{                   
    counter[0] = SimpleCounter();
    counter[1] = SimpleCounter();
    CANID = id;
    sendingFrequency = freq;
    messageLength = MESSAGE_ARRAY_LEN;
    for(int i = 0; i < messageLength; i++){
        message[i] = 0;
    }
    lastSentTimestamp = 0;
    hasChecksum = true;
}

// Constructor, set the CAN ID and sending frequency. Message length determined from Template value MESSAGE_ARRAY_LEN
template <int MESSAGE_ARRAY_LEN>
CANMessage<MESSAGE_ARRAY_LEN>::CANMessage(unsigned long id, int freq)
{                   
    checksumService = CANMessageChecksumCalculatorDefault();
    counter[0] = SimpleCounter();
    counter[1] = SimpleCounter();
    CANID = id;
    sendingFrequency = freq;
    messageLength = MESSAGE_ARRAY_LEN;
    for(int i = 0; i < messageLength; i++){
        message[i] = 0;
    }
    lastSentTimestamp = 0;
    hasChecksum = false;
}

// Method to manually update the lastSentTimeStamp - useful for debugging if we don't actually want to send the message each time
template <int MESSAGE_ARRAY_LEN>
bool CANMessage<MESSAGE_ARRAY_LEN>::updateTimestamp(){                         
    lastSentTimestamp = millis();
    return true;
}

// Method to manually update the internal counter(s) - useful for debugging if we don't actually want to send the message each time
template <int MESSAGE_ARRAY_LEN>
bool CANMessage<MESSAGE_ARRAY_LEN>::updateCounters(){                         
    counter[0].increment();
    counter[1].increment();
    return true;
}

// Method to determine if the message is ready to be sent based on the sending frequency & lastSentTimestamp
template <int MESSAGE_ARRAY_LEN>
bool CANMessage<MESSAGE_ARRAY_LEN>::shouldSend(){                              
    if(millis() - lastSentTimestamp >= sendingFrequency){
        return true;
    }
    else{
        return false;
    }
}

// Method to send the message and update the lastSentTimestamp, must include an mcp2525_can interface object to send the message 
template <int MESSAGE_ARRAY_LEN>
bool CANMessage<MESSAGE_ARRAY_LEN>::sendMessage(mcp2515_can CANInterface){     
    updateChecksum();
    CANInterface.sendMsgBuf(CANID, 0, messageLength, message);
    updateTimestamp();
    updateCounters();
    return true;
}

// Integrated method to check the timestamp, send if ready, update the timestamp
template <int MESSAGE_ARRAY_LEN>
bool CANMessage<MESSAGE_ARRAY_LEN>::sendIfReady(mcp2515_can CANInterface){     
    if(shouldSend()){
        sendMessage(CANInterface);
        updateCounters();
        return true;
    }
    else{
        return false;
    }
}

// Method to send the message and update the lastSentTimestamp. Calling without arguments will output to Serial. template <int MESSAGE_ARRAY_LEN>
template <int MESSAGE_ARRAY_LEN>
bool CANMessage<MESSAGE_ARRAY_LEN>::sendMessage(){    
    updateChecksum();
    outputToSerial();
    updateTimestamp();
    updateCounters();
    return true;
}

// Integrated method to check the timestamp, send if ready, update the timestamp. Calling without arguments will output to Serial.
template <int MESSAGE_ARRAY_LEN>
bool CANMessage<MESSAGE_ARRAY_LEN>::sendIfReady(){     
    if(shouldSend()){
        sendMessage();
        return true;
    }
    else{
        return false;
    }
}

// Method output to Serial, takes arguments for displayed format of id and data
template <int MESSAGE_ARRAY_LEN>
bool CANMessage<MESSAGE_ARRAY_LEN>::outputToSerial(int idFormat, int dataFormat){     
    if(idFormat != BIN && idFormat != OCT && idFormat != DEC && idFormat != HEX){
        idFormat = HEX;
    }
    if(dataFormat != BIN && dataFormat != OCT && dataFormat != DEC && dataFormat != HEX){
        dataFormat = HEX;
    }
    Serial.print(CANID, idFormat);
    for(int i = 0; i < messageLength; i++){
        Serial.print(" ");
        Serial.print(message[i], dataFormat);
    }
    Serial.println();
    return true;
}

// Method to setup the internal counters
template <int MESSAGE_ARRAY_LEN>
bool CANMessage<MESSAGE_ARRAY_LEN>::setCounter(int counterId = 0, int startVal = 0, unsigned long maxVal = 14, int step = 1,int incAt = 1){   
    if(counterId > (sizeof(counter) / sizeof(counter[0]))-1 || counterId < 0){
        return false;
    }
    counter[counterId] = SimpleCounter(startVal, maxVal, step, incAt);
    return true;
}

// Method to setup the internal checksum calculator
template <int MESSAGE_ARRAY_LEN>
bool CANMessage<MESSAGE_ARRAY_LEN>::updateChecksum(){   
    if(hasChecksum){
        byte * checksumAdjustedMessage = checksumService.calculateChecksum(CANID, message, messageLength);;
        for(int i = 0; i < messageLength; i++){
            message[i] = checksumAdjustedMessage[i];
        }
    }
    return true;
}


template class CANMessage<1>;
template class CANMessage<2>;
template class CANMessage<3>;
template class CANMessage<4>;
template class CANMessage<5>;
template class CANMessage<6>;
template class CANMessage<7>;
template class CANMessage<8>;

