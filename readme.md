CAN_Message_Arduino is a simple helper library to make sending CAN bus message easy.  
  
Instation:  
CANMessage<8> CAN_0B8(0x0B8, 1000);  
Specify the number of message bytes in the <template> for the constructor. Valid values are ints 0-8.  
First Argument is the CAN ID  
Second Argument is the sending interval in ms.  
  
Public Properties:  
CANID: the CAN ID  
messageLength: the length of the message, in bytes  
message: the message data, array of 8bit bytes  
sendingFrequency: the sending interval in ms  
lastSentTimestamp: the timestamp millis() when this message was last sent  
  
Public Methods:  
shouldSend(): compares the lastSentTimestamp to current millis(), returns true if greater than the sendingFrequency  
sendIfReady(): all in one method to send the message if ready sendingFrequency has elapsed since it was last sent.   Calling without arguments will log to serial port, or can accept an instance of mcp2515_can CAN interface to send on. Updates the lastSentTimestamp.  
sendMessage: sends the message, Calling without arguments will log to serial port, or can accept an instance of mcp2515_can CAN interface to send on. Updates the lastSentTimestamp.  
outputToSerial(int idFormat = HEX, int dataFormat = HEX): log the message to an open serial output. Formating of the ID and message data are customiseable. Calling this method does not update the lastSentTimestamp.  
updateTimestamp: updates the lastSentTimestamp to current value of millis().  


