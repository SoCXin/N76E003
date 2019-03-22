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
//  File Function: N76E003 Read actually bandgap value by IAP command
//***********************************************************************************************************
#include "N76E003_iar.h"
#include "Common.h"
#include "Delay.h"
#include "SFR_Macro.h"
#include "Function_define.h"

double  Bandgap_Value,Bandgap_Voltage;			//please always use "double" mode for this
UINT8 BandgapHigh,BandgapLow;
		
void READ_BANDGAP()
{

		set_IAPEN;
		IAPAL = 0x0C;
    IAPAH = 0x00;
    IAPCN = READ_UID;
    set_IAPGO;
		BandgapHigh = IAPFD;
		IAPAL = 0x0d;
    IAPAH = 0x00;
    IAPCN = READ_UID;
    set_IAPGO;
		BandgapLow = IAPFD;
		BandgapLow = BandgapLow&0x0F;
		clr_IAPEN;
		Bandgap_Value = (BandgapHigh<<4)+BandgapLow;
		Bandgap_Voltage = 3072/(0x0fff/Bandgap_Value);
}

void main(void)
{
	InitialUART0_Timer3(115200);
	READ_BANDGAP();
	printf_UART("bandgap voltage = %d\n", Bandgap_Voltage); 
	printf_UART("Bandgap SFR  = 0x%x\n", BandgapHigh);
	printf_UART("Bandgap SFR  = 0x%x\n", BandgapLow);
	while(1);
}