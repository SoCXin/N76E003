/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* Copyright(c) 2017 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

//***********************************************************************************************************
//  Nuvoton Technoledge Corp. 
//  Website: http://www.nuvoton.com
//  E-Mail : MicroC-8bit@nuvoton.com
//  Date   : Apr/21/2017
//***********************************************************************************************************

//***********************************************************************************************************
//  File Function: N76E003 APROM program DATAFLASH (APROM) demo code
//***********************************************************************************************************

#include "N76E003.h"





#define     CID_READ            0x0B
#define     DID_READ            0x0C

/*
	Since the DATAFLASH is in the APROM. Program command is same as program APROM
*/
#define     PAGE_ERASE_LD       0x62
#define     BYTE_READ_LD        0x40
#define     BYTE_PROGRAM_LD	    0x61
#define     PAGE_SIZE           128


#define     ERASE_FAIL          0x70
#define     PROGRAM_FAIL        0x71
#define     IAPFF_FAIL          0x72
#define     IAP_PASS            0x00

//---------------------------------------------------------------
// Following define by customer
// Please confirm the start addresss not over your code size
//---------------------------------------------------------------
#define     DATA_SIZE           1024   
#define     DATA_START_ADDR     0x0000 					

/********************************************************************************************
 Following IAP command register is also define in SFR_Macro.h
 
	#define set_IAPEN   BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;CHPCON |= SET_BIT0 ;EA=BIT_TMP
	#define clr_IAPEN   BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;CHPCON &= ~SET_BIT0;EA=BIT_TMP
	#define set_APUEN   BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;IAPUEN |= SET_BIT0 ;EA=BIT_TMP
	#define clr_APUEN   BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;IAPUEN &= ~SET_BIT0;EA=BIT_TMP
	
**********************************************************************************************/
void IAP_ERROR_LED(void)
{
	while (1)
	{
		clr_P03;
		Timer0_Delay1ms(100);
		set_P03;
		Timer0_Delay1ms(100);
	}

}

//-----------------------------------------------------------------------------------------------------------/
void Trigger_IAP(void)
{   
    set_IAPGO;																	//trigger IAP
    if((CHPCON&SET_BIT6)==SET_BIT6)             // if fail flag is set, toggle error LED and IAP stop
		{
			clr_IAPFF;
			IAP_ERROR_LED();
		}
}
/*
		WARNING:
	No matter read or writer, when IAPFF is set 1, 
	this step process is fail. DATA should be ignore.
*/
//-----------------------------------------------------------------------------------------------------------/

/*****************************************************************************************************************
Erase APROM subroutine:
	

******************************************************************************************************************/		
void Erase_LDROM(void)
{   
    UINT16 u16Count;

    set_IAPEN;													// Enable IAP function
		IAPFD = 0xFF;												// IMPORTANT !! To erase function must setting IAPFD = 0xFF 
    IAPCN = PAGE_ERASE_LD;
    set_LDUEN;													//  APROM modify Enable
	
    for(u16Count=0x0000;u16Count<DATA_SIZE/PAGE_SIZE;u16Count++)		//
    {        
        IAPAL = LOBYTE(u16Count*PAGE_SIZE + DATA_START_ADDR);
        IAPAH = HIBYTE(u16Count*PAGE_SIZE + DATA_START_ADDR);
        Trigger_IAP(); 
    } 
//    clr_LDUEN;
//    clr_IAPEN;
}
//-----------------------------------------------------------------------------------------------------------
void Erase_LDROM_Verify(void)
{   
    UINT16 u16Count;
    set_IAPEN;
    IAPAL = LOBYTE(DATA_START_ADDR);
    IAPAH = HIBYTE(DATA_START_ADDR);
    IAPCN = BYTE_READ_LD;

    for(u16Count=0;u16Count<DATA_SIZE;u16Count++)
    {   
        IAPFD = 0x00;    
        Trigger_IAP();
        if(IAPFD != 0xFF)
					IAP_ERROR_LED();
        IAPAL++;
        if(IAPAL == 0x00)
          IAPAH++;
    } 
		
    clr_IAPEN;
    
}
//-----------------------------------------------------------------------------------------------------------
void Program_LDROM(void)
{   
    UINT16 u16Count;

    set_IAPEN;
    set_LDUEN;    
    IAPAL = LOBYTE(DATA_START_ADDR);
    IAPAH = HIBYTE(DATA_START_ADDR);
    IAPCN = BYTE_PROGRAM_LD;
    
    for(u16Count=0;u16Count<DATA_SIZE;u16Count++)
    {   
        IAPFD++;     
        Trigger_IAP();
       
        IAPAL++;
        if(IAPAL == 0)
        {
            IAPAH++;
        }
    } 
		
    clr_LDUEN;
    clr_IAPEN;
}
//-----------------------------------------------------------------------------------------------------------
void Program_LDROM_Verify(void)
{   
    UINT16 u16Count;
    UINT8  u8Read_Data;

    set_IAPEN;
    IAPAL = LOBYTE(DATA_START_ADDR);
    IAPAH = HIBYTE(DATA_START_ADDR);
    IAPCN = BYTE_READ_LD;
    u8Read_Data = 0x00;

    for(u16Count=0;u16Count<DATA_SIZE;u16Count++)
    {   
        Trigger_IAP();
        if(IAPFD != u8Read_Data)
					IAP_ERROR_LED();
        IAPAL++;
        if(IAPAL == 0)
        {
            IAPAH++;
        }
        u8Read_Data ++;
    } 

    clr_IAPEN;
}
//-----------------------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------------------
void main (void) 
{

  Set_All_GPIO_Quasi_Mode;
//---------toggle GPIO1---------	
	clr_GPIO1;
	Timer0_Delay1ms(100);
	set_GPIO1;
	Timer0_Delay1ms(100);
	clr_GPIO1;
	Timer0_Delay1ms(100);
	set_GPIO1;
	Timer0_Delay1ms(100);
//---------end toggle GPIO1---------
	
    Erase_LDROM();
		Erase_LDROM_Verify();
    Program_LDROM();
    Program_LDROM_Verify();

//---------toggle GPIO1---------	
	clr_GPIO1;
//---------end toggle GPIO1---------

    while(1);
}
//-----------------------------------------------------------------------------------------------------------
