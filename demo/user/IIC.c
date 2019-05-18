
#include "N76E003.h"
#include "Common.h"
#include "Delay.h"
#include "SFR_Macro.h"
#include "Function_define.h"

#define  GETACK  1                      // get ack                        
#define  GETNAK  0                      // get nak   

#ifndef  HIGH
#define  HIGH          1
#endif
#ifndef  LOW
#define  LOW           0
#endif

#ifndef  OUTPUT
#define  OUTPUT          1
#endif
#ifndef  INPUT
#define  INPUT           0
#endif

#define SlaveADDR 0x08
#define SlaveWR  0
#define SlaveRD  1

#define SCLPin  P03
#define SDAPin  P04

unsigned char sda_in_out;
unsigned char recv_len;

void delay()
{
	int i;
	for(i=0;i<200;i++)
	{
		i++;
	}
}

//SCL½ÅÖÃ1/0
void setSCL(unsigned char ucDta)
{
  P03 = ucDta;//digitalWrite(SCLPin, ucDta);
}

//SDA½ÅÉèÎªÊä³öÄ£Ê½²¢ÖÃ1/0
void setSDA(unsigned char ucDta)
{
  if (sda_in_out != OUTPUT)
  {
    sda_in_out = OUTPUT;
    P04_PushPull_Mode;//pinMode(SDAPin, OUTPUT);
  }
  P04 = ucDta;//digitalWrite(SDAPin, ucDta);
}
//SDA½ÅÉèÎªÊäÈëÄ£Ê½
void setSDAInput()
{
	P04_Input_Mode;//pinMode(SDAPin, INPUT);
	set_P0S_4;
  sda_in_out = INPUT;
}

/*******I2C³õÊ¼»¯*******/
void initI2C()
{
  P03_PushPull_Mode;//pinMode(SCLPin, OUTPUT);
  P04_PushPull_Mode;//pinMode(SDAPin, OUTPUT);
  setSCL(HIGH);
  setSDA(HIGH);
}

/*******Æô¶¯ÐÅºÅ*******/
void startI2C()
{
  setSDA(HIGH);
  setSCL(HIGH);
  //Timer3_Delay10us(1);
  setSDA(LOW);
}

/*******Í£Ö¹ÐÅºÅ*******/
void stopI2C()
{
  setSCL(LOW);
  setSDA(LOW);
  setSCL(HIGH);
  //Timer3_Delay10us(1);
  setSDA(HIGH);
}

/*******Ó¦´ðÐÅºÅ*******/
unsigned char getAck()
{
	unsigned int timer_t =0;
	
  setSCL(LOW);
  setSDAInput();//pinMode(SDAPin, INPUT);
  setSCL(HIGH);
  while (1) {
    if (SDAPin == 0)      // get ack //!digitalRead(SDAPin)
    {
			//printf("send byte Ack\n");
			delay();
      return GETACK;
    }
    if (timer_t > 250)
		{
			//printf("send byte NAck\n");
			return GETNAK;
		}
		timer_t ++;
  }
}

/*******Ð´Ò»¸ö×Ö½Ú*******/
void sendByte(unsigned char ucDta)
{
	int i;
  for ( i = 0; i < 8; i++)
  {
    setSCL(LOW);
    setSDA(ucDta >> 7);
    ucDta = ucDta << 1;
    setSCL(HIGH);
		delay();
    //Timer3_Delay10us(1);
  }
}

/*******Ð´Ò»¸ö×Ö½Ú½ÓÊÕ·µ»ØÓ¦´ð*******/
unsigned char sendByteAck(unsigned char ucDta)
{
  //Ð´Ò»¸ö×Ö½Ú
  sendByte(ucDta);
  //µÈ´ýÓ¦´ð
  return getAck();
}

/*******¶ÁÒ»¸ö×Ö½Ú*******/
unsigned char readByte()
{
  unsigned char i,ucRt = 0;
	unsigned  char  ucBit;
	if(!recv_len)return 0;
  setSDAInput();//pinMode(SDAPin, INPUT);
  
  for (i = 0; i < 8; i++)
  {
    setSCL(LOW);
    setSCL(HIGH);
		ucBit = SDAPin;
    ucRt = (ucRt << 1) | ucBit;
		delay();
    //Timer3_Delay10us(1);
  }
  recv_len--;
  if(recv_len>0)          // send ACK
    {
        setSCL(LOW);                                                // sclSet(HIGH)    
        setSDA(LOW);                                                // sdaSet(LOW)                 
        setSCL(HIGH);                                               //  sclSet(LOW) 
        setSCL(LOW);
    }
    else                    // send NAK
    {
        setSCL(LOW);                                                // sclSet(HIGH)    
        setSDA(HIGH);                                               // sdaSet(LOW)                 
        setSCL(HIGH);                                               //  sclSet(LOW) 
        setSCL(LOW);
        stopI2C();
    }
   return ucRt;
}


/*******Ð´I2CÒ»¸ö×Ö½Ú*******/
unsigned char writeByteI2C(unsigned char dta)
{
    return sendByteAck(dta);
}

/*******¶ÁI2CÒ»¸öÊý×é*******/
unsigned char writeArrayI2C(unsigned char len, unsigned char *dta)
{
		unsigned char i;
    for(i=0; i<len; i++)
    {
        if(GETACK != writeByteI2C(dta[i]))
        {
            return GETNAK;
        }
    }
    return GETACK;
}

/*******Ñ¡¶¨´ÓÉè±¸½øÐÐÍ¨Ñ¶*******/
unsigned char beginToSlave(unsigned char addr)
{
	unsigned char ret;
  //·¢ÆðÊ¼ÐÅºÅ
  startI2C();
  //µÈ´ýÓ¦´ð
  ret = sendByteAck(addr<<1);
  return ret;
}

/*******Í£Ö¹´«Êä*******/
unsigned char endToSlave()
{
  stopI2C();
  return 0;
}

/*******¶ÁÈ¡´Ó»úN¸ö×Ö½Ú*******/
unsigned char requestFromSlave(unsigned char addr, unsigned char len)
{
		unsigned char ret;
    startI2C();                       // start signal
    recv_len = len;
    ret = sendByteAck((addr<<1)|1);       // send write address and get ack
    //setSCL(LOW);
    return ret;
}

unsigned char availableI2C()
{
  return recv_len;
}

//ÖØ¶¨Ïò
char putchar (char c)  {
  while (!TI);
  TI = 0;
  return (SBUF = c);
}

int bb = 0;
//========================================================================================================
void main(void)
{
		int c;
		char sta;
		initI2C();
		
    P12_PushPull_Mode;
    InitialUART0_Timer1(9600);
    while (1)
		{
//			requestFromSlave(SlaveADDR, 7);
//			while(availableI2C())
//			{
//				c = readByte();
//				printf("num: %d ",c);
//			}
//			printf("\n");
			
			beginToSlave(SlaveADDR);
			sta = sendByteAck(bb);
			endToSlave();
			bb++;
			//printf("send byte Ack: %d\n",sta);
			Timer0_Delay1ms(200);
			P12 = 1;
			Timer0_Delay1ms(200);
			P12 = 0;
		}
/* =================== */
}

