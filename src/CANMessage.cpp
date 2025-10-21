#include "Arduino.h"
#include "CANMessage.h"
#include "mcp2515_can.h"

/******************************************************************************
// Define the CANMessage class
******************************************************************************/
template <int MESSAGE_ARRAY_LEN>
CANMessage<MESSAGE_ARRAY_LEN>::CANMessage(int id, int freq){                   // Constructor, set the CAN ID and sending frequency. Message length determined from Template value MESSAGE_ARRAY_LEN
    CANID = id;
    sendingFrequency = freq;
    messageLength = MESSAGE_ARRAY_LEN;
    for(int i = 0; i < messageLength; i++){
        message[i] = 0;
    }
    lastSentTimestamp = 0;
}

template <int MESSAGE_ARRAY_LEN>
bool CANMessage<MESSAGE_ARRAY_LEN>::updateTimestamp(){                         // Method to manually update the lastSentTimeStamp - useful for debugging if we don't actually want to send the message each time
    lastSentTimestamp = millis();
    return true;
}

template <int MESSAGE_ARRAY_LEN>
bool CANMessage<MESSAGE_ARRAY_LEN>::shouldSend(){                              // Method to determine if the message is ready to be sent based on the sending frequency & lastSentTimestamp
    if(millis() - lastSentTimestamp >= sendingFrequency){
        return true;
    }
    else{
        return false;
    }
}

template <int MESSAGE_ARRAY_LEN>
bool CANMessage<MESSAGE_ARRAY_LEN>::sendMessage(mcp2515_can CANInterface){     // Method to send the message and update the lastSentTimestamp, must include an mcp2525_can interface object to send the message 
    CANInterface.sendMsgBuf(CANID, 0, messageLength, message);
    updateTimestamp();
    return true;
}

template <int MESSAGE_ARRAY_LEN>
bool CANMessage<MESSAGE_ARRAY_LEN>::sendIfReady(mcp2515_can CANInterface){     // Integrated method to check the timestamp, send if ready, update the timestamp
    if(shouldSend()){
        sendMessage(CANInterface);
        return true;
    }
    else{
        return false;
    }
}

template <int MESSAGE_ARRAY_LEN>
bool CANMessage<MESSAGE_ARRAY_LEN>::sendMessage(){     // Method to send the message and update the lastSentTimestamp. Calling without arguments will output to Serial.
    outputToSerial();
    updateTimestamp();
    return true;
}

template <int MESSAGE_ARRAY_LEN>
bool CANMessage<MESSAGE_ARRAY_LEN>::sendIfReady(){     // Integrated method to check the timestamp, send if ready, update the timestamp. Calling without arguments will output to Serial.
    if(shouldSend()){
        sendMessage();
        return true;
    }
    else{
        return false;
    }
}

template <int MESSAGE_ARRAY_LEN>
bool CANMessage<MESSAGE_ARRAY_LEN>::outputToSerial(int idFormat, int dataFormat){     // Method output to Serial, takes arguments for displayed format of id and data
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



template class CANMessage<1>;
template class CANMessage<2>;
template class CANMessage<3>;
template class CANMessage<4>;
template class CANMessage<5>;
template class CANMessage<6>;
template class CANMessage<7>;
template class CANMessage<8>;

