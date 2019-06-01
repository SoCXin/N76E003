/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* Copyright(c) 2017 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

//***********************************************************************************************************
//  Website: http://www.nuvoton.com
//  E-Mail : MicroC-8bit@nuvoton.com
//  Date   : Jan/21/2017
//***********************************************************************************************************

//***********************************************************************************************************
//  File Function: N76E003 APROM program DATAFLASH as EEPROM way 
//***********************************************************************************************************
#include "N76E003_iar.h"
#include "SFR_Macro.h"
#include "Function_define.h"
#include "Common.h"
#include "Delay.h"

volatile unsigned char __xdata page_buffer[128];

/*****************************************************************************************************************
Read_APROM_BYTE :
user direct read APROM flash area value
******************************************************************************************************************/	
UINT8 read_APROM_BYTE(UINT16 __code *u16_addr)
{
	UINT8 rdata;
	rdata = *u16_addr;
	return rdata;
}

/*****************************************************************************************************************
write_DATAFLASH_BYTE :
user can copy all this subroutine into project, then call this function in main.
******************************************************************************************************************/		
void write_DATAFLASH_BYTE(UINT16 u16_addr,UINT8 u8_data)
{
  unsigned char looptmp=0;
  unsigned int u16_addrl_r,tmp=0;


//Check page start address
  u16_addrl_r=(u16_addr/128)*128;
//Save APROM data to XRAM0
  for(looptmp=0;looptmp<0x80;looptmp++)
  {
   tmp = read_APROM_BYTE((unsigned int __code *)(u16_addrl_r+looptmp));
  page_buffer[looptmp]=tmp;
  }
// Modify customer data in XRAM
  page_buffer[u16_addr&0x7f] = u8_data;
  
//Erase APROM DATAFLASH page
    IAPAL = u16_addrl_r&0xff;
    IAPAH = (u16_addrl_r>>8)&0xff;
    IAPFD = 0xFF;
    set_IAPEN; 
    set_APUEN;
    IAPCN = 0x22;     
     set_IAPGO; 
    
//Save changed RAM data to APROM DATAFLASH
    
    set_IAPEN; 
    set_APUEN;
    IAPCN = 0x21;
    for(looptmp=0;looptmp<0x80;looptmp++)
    {
      IAPAL = (u16_addrl_r&0xff)+looptmp;
      IAPAH = (u16_addrl_r>>8)&0xff;
      IAPFD = page_buffer[looptmp];
      set_IAPGO;      
    }
    clr_APUEN;
    clr_IAPEN;
}  

/******************************************************************************************************************/	


void main (void) 
{
		unsigned char datatemp;
/* -------------------------------------------------------------------------*/
/*  Dataflash use APROM area, please ALWAYS care the address of you code    */
/*	APROM 0x3800~0x38FF demo as dataflash 	       			*/
/* 	Please use Memory window key in C:0x3800 to check earse result					*/	      
/* -------------------------------------------------------------------------*/
                while(P12);                                     //wait P1.2 toggle low
                
//call write byte 
		write_DATAFLASH_BYTE (0x3800,0x55);
		write_DATAFLASH_BYTE (0x3882,0x56);
		write_DATAFLASH_BYTE (0x3855,0xaa);
		write_DATAFLASH_BYTE (0x3856,0x66);
//call read byte
		datatemp = read_APROM_BYTE((unsigned int __code *)0x3800);

    while(1);
}
//-----------------------------------------------------------------------------------------------------------
