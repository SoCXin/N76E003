#include "SimpleModbus.h"

#include "N76E003.h"
#include "Common.h"
#include "Delay.h"
#include "SFR_Macro.h"
#include "Function_define.h"

#define BUFFER_SIZE 32

UINT8 frame[BUFFER_SIZE];
UINT16 holdingRegsSize; // size of the register array 
UINT8 broadcastFlag;
UINT8 slaveID;
UINT8 function;
UINT16 errorCount;
UINT16 T1_5; // inter character time out
UINT16 T3_5; // frame delay

// function definitions
void exceptionResponse(UINT8 exception);
UINT16 calculateCRC(UINT8 bufferSize); 
void sendPacket(UINT8 bufferSize);

void modbus_configure(UINT32 baud, UINT8 _slaveID, UINT16 _holdingRegsSize, UINT8 _lowLatency) {
	set_ES;           //enable UART interrupt
  set_EA;           //enable global interrupt
	
	slaveID = _slaveID;
	InitialUART0_Timer1(baud);
	
  // Modbus states that a baud rate higher than 19200 must use a fixed 750 us 
  // for inter character time out and 1.75 ms for a frame delay.
  // For baud rates below 19200 the timeing is more critical and has to be calculated.
  // E.g. 9600 baud in a 10 bit packet is 960 characters per second
  // In milliseconds this will be 960characters per 1000ms. So for 1 character
  // 1000ms/960characters is 1.04167ms per character and finaly modbus states an
  // intercharacter must be 1.5T or 1.5 times longer than a normal character and thus
  // 1.5T = 1.04167ms * 1.5 = 1.5625ms. A frame delay is 3.5T.
  // Added experimental low latency delays. This makes the implementation
  // non-standard but practically it works with all major modbus master implementations.
  
  if (baud == 1000000 && _lowLatency)
  {
      T1_5 = 1; 
      T3_5 = 10;
  }
  else if (baud >= 115200 && _lowLatency){
      T1_5 = 75; 
      T3_5 = 175; 
  }
  else if (baud > 19200)
  {
    T1_5 = 750; 
    T3_5 = 1750;
  }
  else 
  {
    T1_5 = 15000000/baud; // 1T * 1.5 = T1.5
    T3_5 = 35000000/baud; // 1T * 3.5 = T3.5
  }	
	
	holdingRegsSize = _holdingRegsSize;
  errorCount = 0; // initialize errorCount
}

UINT16 modbus_poll(UINT16 *holdingRegs) {
  UINT8 buffer = 0;
  UINT8 overflow = 0;
	UINT8 id;
	UINT16 crc;
  UINT16 startingAddress; 
  UINT16 no_of_registers; 
  UINT16 maxData;
  UINT8 index;
  UINT8 address;
  UINT16 crc16;		
	UINT8 noOfBytes;
	UINT8 responseFrameSize;	
	UINT16 temp;	
  UINT16 regStatus;
	
	while (RI) {
		if (overflow) {
			Receive_Data_From_UART0();
		}
		else {
			if (buffer == BUFFER_SIZE) {
				overflow = 1;
			}
			frame[buffer] = Receive_Data_From_UART0();
//			Send_Data_To_UART0(frame[buffer]); /* For debug */
			buffer++;
		}
		Timer3_Delay10us(T1_5/10);
	}
//	Send_Data_To_UART0(0x65); /* For debug */
  // If an overflow occurred increment the errorCount
  // variable and return to the main sketch without 
  // responding to the request i.e. force a timeout
  if (overflow)
//		Send_Data_To_UART0(0x65); /* For debug */
    return errorCount++;
	// The minimum request packet is 8 bytes for function 3 & 16	
	if (buffer > 6) {
//		Send_Data_To_UART0(0x65); /* For debug */
		id = frame[0];
		broadcastFlag = 0;
		
    if (id == 0)
      broadcastFlag = 1;
		if (id == slaveID || broadcastFlag) {
//			Send_Data_To_UART0(0x65); /* For debug */
			crc = ((frame[buffer - 2] << 8) | frame[buffer - 1]); // combine the crc Low & High bytes
			if (calculateCRC(buffer - 2) == crc) {
				function = frame[1];
        startingAddress = ((frame[2] << 8) | frame[3]); // combine the starting address bytes
        no_of_registers = ((frame[4] << 8) | frame[5]); // combine the number of register bytes  
        maxData = startingAddress + no_of_registers;
				
				// broadcasting is not supported for function 3 
				if (!broadcastFlag && (function == 3)) {
//					Send_Data_To_UART0(frame[buffer]); /* For debug */
					if (startingAddress < holdingRegsSize) { // check exception 2 ILLEGAL DATA ADDRESS
						if (maxData <= holdingRegsSize) {
              noOfBytes = no_of_registers * 2;
              responseFrameSize = 5 + noOfBytes; // ID, function, noOfBytes, (dataLo + dataHi) * number of registers, crcLo, crcHi
              frame[0] = slaveID;
              frame[1] = function;
              frame[2] = noOfBytes;
              address = 3; // PDU starts at the 4th byte
							
              for (index = startingAddress; index < maxData; index++) {
                temp = holdingRegs[index];
                frame[address] = temp >> 8; // split the register into 2 bytes
                address++;
                frame[address] = temp & 0xFF;
                address++;
              } 
							
              crc16 = calculateCRC(responseFrameSize - 2);
              frame[responseFrameSize - 2] = crc16 >> 8; // split crc into 2 bytes
              frame[responseFrameSize - 1] = crc16 & 0xFF;
//              frame[responseFrameSize - 2] = calculateCRC(responseFrameSize - 2) >> 8; // split crc into 2 bytes
//              frame[responseFrameSize - 1] = calculateCRC(responseFrameSize - 2) & 0xFF;							
              sendPacket(responseFrameSize);
						}
						else 
							exceptionResponse(3); // exception 3 ILLEGAL DATA VALUE
					}
					else 
						exceptionResponse(2); // exception 2 ILLEGAL DATA ADDRESS
				}
				else if (function == 6) {
					if (startingAddress < holdingRegsSize) { // check exception 2 ILLEGAL DATA ADDRESS
						startingAddress = ((frame[2] << 8) | frame[3]);
						regStatus = ((frame[4] << 8) | frame[5]);
						responseFrameSize = 8;
						
            crc16 = calculateCRC(responseFrameSize - 2);
            frame[responseFrameSize - 2] = crc16 >> 8; // split crc into 2 bytes
            frame[responseFrameSize - 1] = crc16 & 0xFF;
//            frame[responseFrameSize - 2] = calculateCRC(responseFrameSize - 2) >> 8; // split crc into 2 bytes
//            frame[responseFrameSize - 1] = calculateCRC(responseFrameSize - 2) & 0xFF;						
            sendPacket(responseFrameSize);						
					}
					else 
						exceptionResponse(2); // exception 2 ILLEGAL DATA ADDRESS
				}
				else if (function == 16) {
          // check if the recieved number of bytes matches the calculated bytes minus the request bytes
          // id + function + (2 * address bytes) + (2 * no of register bytes) + byte count + (2 * CRC bytes) = 9 bytes
          if (frame[6] == (buffer - 9)) {
						 if (startingAddress < holdingRegsSize) { // check exception 2 ILLEGAL DATA ADDRESS
							  if (maxData <= holdingRegsSize) { // check exception 3 ILLEGAL DATA VALUE
									address = 7; // start at the 8th byte in the frame
									for (index = startingAddress; index < maxData; index++) {
										holdingRegs[index] = ((frame[address] << 8) | frame[address + 1]);
										address += 2;
									} 					
									
									// only the first 6 bytes are used for CRC calculation
									crc16 = calculateCRC(6); 
									frame[6] = crc16 >> 8; // split crc into 2 bytes
									frame[7] = crc16 & 0xFF;
//									frame[6] = calculateCRC(6) >> 8; // split crc into 2 bytes
//									frame[7] = calculateCRC(6) & 0xFF;
									
									// a function 16 response is an echo of the first 6 bytes from the request + 2 crc bytes
									if (!broadcastFlag) // don't respond if it's a broadcast message
										sendPacket(8); 
								}
								else 
									exceptionResponse(3); // exception 3 ILLEGAL DATA VALUE
						 }
						 else 
							 exceptionResponse(2); // exception 2 ILLEGAL DATA ADDRESS
					}				
					else 
						errorCount++; // corrupted packet
				}
				else 
					exceptionResponse(1); // exception 1 ILLEGAL FUNCTION
			}
			else // checksum failed
				errorCount++; 
		}
	}
	else if (buffer > 0 && buffer < 8) {
//		Send_Data_To_UART0(0x65); /* For debug */
		errorCount++;
	}
		 
	 return errorCount;
}

void exceptionResponse(UINT8 exception) {
	UINT16 crc16;
  errorCount++; // each call to exceptionResponse() will increment the errorCount
  if (!broadcastFlag) // don't respond if its a broadcast message
  {
    frame[0] = slaveID;
    frame[1] = (function | 0x80); // set the MSB bit high, informs the master of an exception
    frame[2] = exception;
    crc16 = calculateCRC(3); // ID, function + 0x80, exception code == 3 bytes
    frame[3] = crc16 >> 8;
    frame[4] = crc16 & 0xFF;
//    frame[3] = calculateCRC(3) >> 8;
//    frame[4] = calculateCRC(3) & 0xFF;
    sendPacket(5); // exception response is always 5 bytes ID, function + 0x80, exception code, 2 bytes crc
  }
}

UINT16 calculateCRC(UINT8 bufferSize) {
  UINT16 temp, temp2, flag;
	UINT8 i, j;
  temp = 0xFFFF;
  for (i = 0; i < bufferSize; i++)
  {
    temp = temp ^ frame[i];
    for (j = 1; j <= 8; j++)
    {
      flag = temp & 0x0001;
      temp >>= 1;
      if (flag)
        temp ^= 0xA001;
    }
  }
  // Reverse byte order. 
  temp2 = temp >> 8;
  temp = (temp << 8) | temp2;
  temp &= 0xFFFF;
  return temp; // the returned value is already swopped - crcLo byte is first & crcHi byte is last
}

void sendPacket(UINT8 bufferSize) {   
	UINT8 i;
  for (i = 0; i < bufferSize; i++)
    Send_Data_To_UART0(frame[i]);
    
  // allow a frame delay to indicate end of transmission
	Timer3_Delay10us(T3_5/10);
  
}