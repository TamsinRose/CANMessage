# CANMessage

Simple helper library to make sending, scheduling and checksum calculation of CAN bus messages in Arduino easy.  


---
## Usage:

### instantiation


**Basic**

Will default to Serial printing when sent. Useful for setup and debugging.

`CANMessage<messageLength> CAN_0B8(unsigned long id, int freq);`  

Specify the number of message bytes *messageLength* in the \<template> for the constructor. Valid values are ints 0-8.  

First parameter *id* is the CAN ID.  

Second parameter *freq* is the sending interval in ms. 


**Specifying a Sender interface**

Will be sent using the given CANMessageSender instance.

`CANMessage<messageLength> CAN_0B8(unsigned long id, int freq, CANMessageSender& senderService)`

Specify the number of message bytes *messageLength* in the \<template> for the constructor. Valid values are ints 0-8.  

First parameter *id* is the CAN ID.  

Second parameter *freq* is the sending interval in ms.

A **CANMessageSender** is a wrapper class for any CAN bus interface, must be instantiated before passing to constructor. Senders for the built-in Arduino_CAN and MCP2515 interfaces are included with lis library, see futher in readme for extending for your own CAN interface if different.


**Specifying a Checksum Calculator**

Message checksum will be calculated and insterted into the payload before being sent on the default (Serial) output.

`CANMessage<messageLength> CAN_0B8(unsigned long id, int freq, CANMessageChecksumCalculator& checksumCalculator)`  

Specify the number of message bytes *messageLength* in the \<template> for the constructor. Valid values are ints 0-8.  

First parameter *id* is the CAN ID.  

Second parameter *freq* is the sending interval in ms.

A **CANMessageChecksumCalculator** is an instance of a Checksum calculator class and some basic ones are included with this library, see further in readme for extending your own checksum calculators


**Specifying a Sender interface and Checksum Calculator**

Message checksum will be calculated and insterted into the payload before being sent on the default given CANMessageSender instance.

`CANMessage<messageLength> CAN_0B8(unsigned long id, int freq, CANMessageSender& senderService, CANMessageChecksumCalculator& checksumCalculator)`  

Specify the number of message bytes *messageLength* in the \<template> for the constructor. Valid values are ints 0-8.  

First parameter *id* is the CAN ID.  

Second parameter *freq* is the sending interval in ms.

A **CANMessageSender** is a wrapper class for any CAN bus interface, must be instantiated before passing to constructor. Senders for the built-in Arduino_CAN and MCP2515 interfaces are included with lis library, see futher in readme for extending for your own CAN interface if different.

A **CANMessageChecksumCalculator** is an instance of a Checksum calculator class and some basic ones are included with this library, see further in readme for extending your own checksum calculators


  
## Public Properties:  
**CANID:** the CAN ID  
**messageLength:** the length of the message, in bytes  
**message:** the message data, array of 8bit bytes  
**sendingFrequency:** the sending interval in ms  
**lastSentTimestamp:** the timestamp millis() when this message was last sent  
  
## Public Methods:  
**shouldSend():** compares the lastSentTimestamp to current millis(), returns true if greater than the sendingFrequency  
**sendIfReady():** all in one method to send the message if ready sendingFrequency has elapsed since it was last sent.   Calling without arguments will log to serial port, or can accept an instance of mcp2515_can CAN interface to send on. Updates the lastSentTimestamp.  
**sendMessage():** sends the message, Calling without arguments will log to serial port, or can accept an instance of mcp2515_can CAN interface to send on. Updates the lastSentTimestamp.  
**outputToSerial(int idFormat = HEX, int dataFormat = HEX):** log the message to an open serial output. Formating of the ID and message data are customiseable. Calling this method does not update the lastSentTimestamp.  
**updateTimestamp:** updates the lastSentTimestamp to current value of millis().  






