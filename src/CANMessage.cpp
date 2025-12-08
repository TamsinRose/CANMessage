/******************************************************************************
// Define the CANMessage class methods
******************************************************************************/

#include "CANMessage.h"

CANMessageSenderSerialPrint CANPrintToSerialDefault;
CANMessageChecksumCalculatorDefault CANChecksumServiceDefault;

// Constructor, set the CAN ID and sending frequency. Message length determined from Template value MESSAGE_ARRAY_LEN
// Including an instance of sender service
// Including an instance of checksum calulating service
template <int MESSAGE_ARRAY_LEN>
CANMessage<MESSAGE_ARRAY_LEN>::CANMessage(unsigned long id, int freq, CANMessageSender& sender, CANMessageChecksumCalculator& checksumCalculator):
senderService{sender},
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
    hasSenderService = true;
    hasChecksum = true;
}



// Constructor, set the CAN ID and sending frequency. Message length determined from Template value MESSAGE_ARRAY_LEN
// Including an instance of sender service
template <int MESSAGE_ARRAY_LEN>
CANMessage<MESSAGE_ARRAY_LEN>::CANMessage(unsigned long id, int freq, CANMessageSender& sender):
senderService{sender},
checksumService{CANChecksumServiceDefault}{                   
    counter[0] = SimpleCounter();
    counter[1] = SimpleCounter();
    CANID = id;
    sendingFrequency = freq;
    messageLength = MESSAGE_ARRAY_LEN;
    for(int i = 0; i < messageLength; i++){
        message[i] = 0;
    }
    lastSentTimestamp = 0;
    hasSenderService = true;
    hasChecksum = false;
}

// Constructor, set the CAN ID and sending frequency. Message length determined from Template value MESSAGE_ARRAY_LEN
// Including an instance of checksum calulating service
template <int MESSAGE_ARRAY_LEN>
CANMessage<MESSAGE_ARRAY_LEN>::CANMessage(unsigned long id, int freq, CANMessageChecksumCalculator& checksumCalculator):
senderService{CANPrintToSerialDefault},
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
    hasSenderService = false;
    hasChecksum = true;
}

// Constructor, set the CAN ID and sending frequency. Message length determined from Template value MESSAGE_ARRAY_LEN
template <int MESSAGE_ARRAY_LEN>
CANMessage<MESSAGE_ARRAY_LEN>::CANMessage(unsigned long id, int freq):
senderService{CANPrintToSerialDefault},
checksumService{CANChecksumServiceDefault}
{                   
    //senderService = CANMessageSenderSerialPrint();
    //checksumService = CANMessageChecksumCalculatorDefault();
    counter[0] = SimpleCounter();
    counter[1] = SimpleCounter();
    CANID = id;
    sendingFrequency = freq;
    messageLength = MESSAGE_ARRAY_LEN;
    for(int i = 0; i < messageLength; i++){
        message[i] = 0;
    }
    lastSentTimestamp = 0;
    hasSenderService = false;
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

// Method to upadte checksum, send the message and update the lastSentTimestamp. 
template <int MESSAGE_ARRAY_LEN>
bool CANMessage<MESSAGE_ARRAY_LEN>::sendMessage(){    
    updateChecksum();
    if(hasSenderService){
        senderService.send(CANID, message, messageLength);
    }
    else{
        outputToSerial(HEX, HEX);
    }
    updateTimestamp();
    updateCounters();
    return true;
}

// Integrated method to check the timestamp, sendMessage() if ready.
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
    if(dataFormat == HEX){
        Serial.print(CANID, HEX);
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
    }
    else{
        Serial.print(CANID, idFormat);
    for(int i = 0; i < messageLength; i++){
        Serial.print(" ");
        Serial.print(message[i], dataFormat);
    }
    Serial.println();
    }
    return true;
}

// Method to setup the internal counters
template <int MESSAGE_ARRAY_LEN>
bool CANMessage<MESSAGE_ARRAY_LEN>::setCounter(int counterId, int startVal, unsigned long maxVal, int step,int incAt){   
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
        uint8_t * checksumAdjustedMessage = checksumService.calculateChecksum(CANID, message, messageLength);;
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

