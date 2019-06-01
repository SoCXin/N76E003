
/* =================== DEFINES =================== */
#include "N76E003.h"
#include "Common.h"
#include "Delay.h"
#include "SFR_Macro.h"
#include "Function_define.h"
#include "SimpleModbus.h"

/* ================== VARIABLES ================== */
UINT16 holdingRegs[3];
UINT8 revByte = 0;
UINT8 nothing = 0;
/* ============= FUNCTIONS PROTOTYPES ============ */

/* ============= FUNCTIONS DEFINITIONS =========== */

/* ==================== MAIN ===================== */
void main() 
{
		modbus_configure(19200, 1, 3, 0);
//	InitialUART0_Timer1(19200);
		while(1) 
		{
			holdingRegs[2] = modbus_poll(holdingRegs);
			holdingRegs[0] += 1;
			holdingRegs[1] += 2;
			while (RI) 
			{
				char c = Receive_Data_From_UART0();
				Send_Data_To_UART0(c);
				revByte++;
			}
			if (revByte >= 10) 
			{
				Send_Data_To_UART0(0x67);
				revByte = 0;
			}
	}
}