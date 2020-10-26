/*--------------------------------------------------------------------------
N76E003.H

Header file for Nuvoton N76E003 in IAR
--------------------------------------------------------------------------*/
__sfr __no_init volatile union
{
  unsigned char P0; /* Port 0 */
  struct /* Port 0 */
  {
  	#if 0
    unsigned char P00 : 1;
    unsigned char P01 : 1;
    unsigned char P02 : 1;
    unsigned char P03 : 1;
    unsigned char P04 : 1;
    unsigned char P05 : 1;
    unsigned char P06 : 1;
    unsigned char P07 : 1;
    #endif  
    unsigned char BIT0 : 1;
    unsigned char BIT1 : 1;
    unsigned char BIT2 : 1;
    unsigned char BIT3 : 1;
    unsigned char BIT4 : 1;
    unsigned char BIT5 : 1;
    unsigned char BIT6 : 1;
    unsigned char BIT7 : 1;
    
  } P0_bit;
} @ 0x80;
    
__sfr __no_init volatile unsigned char SP @ 0x81; /* Stack Pointer */
__sfr __no_init volatile unsigned char DPL @ 0x82; /* Data Pointer Low byte, LSB of DPTR */
__sfr __no_init volatile unsigned char DPH @ 0x83; /* Data Pointer High byte, MSB of DPTR */
__sfr __no_init volatile unsigned char RCTRIM0 @ 0x84;
__sfr __no_init volatile unsigned char RCTRIM1 @ 0x85;	
__sfr __no_init volatile unsigned char RWK @ 0x86;
__sfr __no_init volatile unsigned char PCON @ 0x87;

__sfr __no_init volatile union
{
  unsigned char TCON; /* Timer Control */
  struct /* Timer Control */
  {
  	#if 0
    unsigned char IT0 : 1;
    unsigned char IE0 : 1;
    unsigned char IT1 : 1;
    unsigned char IE1 : 1;
    unsigned char TR0 : 1;
    unsigned char TF0 : 1;
    unsigned char TR1 : 1;
    unsigned char TF1 : 1;
    #endif
    unsigned char BIT0 : 1;
    unsigned char BIT1 : 1;
    unsigned char BIT2 : 1;
    unsigned char BIT3 : 1;
    unsigned char BIT4 : 1;
    unsigned char BIT5 : 1;
    unsigned char BIT6 : 1;
    unsigned char BIT7 : 1;
    
  } TCON_bit;
} @ 0x88;
    
__sfr __no_init volatile unsigned char TMOD @ 0x89;
__sfr __no_init volatile unsigned char TL0 @ 0x8A; /* Timer0 Low */
__sfr __no_init volatile unsigned char TL1 @ 0x8B; /* Timer1 Low*/
__sfr __no_init volatile unsigned char TH0 @ 0x8C; /* Timer0 High*/
__sfr __no_init volatile unsigned char TH1 @ 0x8D; /* Timer1 High*/
__sfr __no_init volatile unsigned char CKCON @ 0x8E;
__sfr __no_init volatile unsigned char WKCON @ 0x8F;

__sfr __no_init volatile union
{
  unsigned char P1; /* Port 1 */
  struct /* Port 1 */
  {
  	#if 0
    unsigned char P10 : 1;
    unsigned char P11 : 1;
    unsigned char P12 : 1;
    unsigned char P13 : 1;
    unsigned char P14 : 1;
    unsigned char P15 : 1;
    unsigned char P16 : 1;
    unsigned char P17 : 1;
    #endif
    unsigned char BIT0 : 1;
    unsigned char BIT1 : 1;
    unsigned char BIT2 : 1;
    unsigned char BIT3 : 1;
    unsigned char BIT4 : 1;
    unsigned char BIT5 : 1;
    unsigned char BIT6 : 1;
    unsigned char BIT7 : 1;    
  } P1_bit;
} @ 0x90;

__sfr __no_init volatile unsigned char SFRS    @ 0x91; //TA Protection
__sfr __no_init volatile unsigned char CAPCON0 @ 0x92;
__sfr __no_init volatile unsigned char CAPCON1 @ 0x93;
__sfr __no_init volatile unsigned char CAPCON2 @ 0x94;
__sfr __no_init volatile unsigned char CKDIV   @ 0x95;
__sfr __no_init volatile unsigned char CKSWT   @ 0x96; //TA Protection
__sfr __no_init volatile unsigned char CKEN    @ 0x97; //TA Protection

__sfr __no_init volatile union
{
  unsigned char SCON; /* Serial Control */
  struct /* Serial Control */
  {
  	#if 0
    unsigned char RI : 1;
    unsigned char TI : 1;
    unsigned char RB8 : 1;
    unsigned char TB8 : 1;
    unsigned char REN : 1;
    unsigned char SM2 : 1;
    unsigned char SM1 : 1;
    unsigned char SM0 : 1;
    #endif
    unsigned char BIT0 : 1;
    unsigned char BIT1 : 1;
    unsigned char BIT2 : 1;
    unsigned char BIT3 : 1;
    unsigned char BIT4 : 1;
    unsigned char BIT5 : 1;
    unsigned char BIT6 : 1;
    unsigned char BIT7 : 1;
  } SCON_bit;
} @ 0x98;

__sfr __no_init volatile unsigned char SBUF @ 0x99; /* Serial Data Buffer */
__sfr __no_init volatile unsigned char SBUF_1 @ 0x9A; /* Serial 1 Data Buffer */
__sfr __no_init volatile unsigned char EIE @ 0x9B;
__sfr __no_init volatile unsigned char EIE1 @ 0x9C;
__sfr __no_init volatile unsigned char CHPCON @ 0x9F; //TA Protection

__sfr __no_init volatile union
{
  unsigned char P2; /* Port 2 */
  struct /* Port 2 */
  {
  	#if 0
    unsigned char P20 : 1;
    unsigned char P21 : 1;
    unsigned char P22 : 1;
    unsigned char P23 : 1;
    unsigned char P24 : 1;
    unsigned char P25 : 1;
    unsigned char P26 : 1;
    unsigned char P27 : 1;
    #endif
    unsigned char BIT0 : 1;
    unsigned char BIT1 : 1;
    unsigned char BIT2 : 1;
    unsigned char BIT3 : 1;
    unsigned char BIT4 : 1;
    unsigned char BIT5 : 1;
    unsigned char BIT6 : 1;
    unsigned char BIT7 : 1;
  } P2_bit;
} @ 0xA0;

__sfr __no_init volatile unsigned char AUXR1 @ 0xA2;
__sfr __no_init volatile unsigned char BODCON0 @ 0xA3; //TA Protection
__sfr __no_init volatile unsigned char IAPTRG @ 0xA4; //TA Protection
__sfr __no_init volatile unsigned char IAPUEN @ 0xA5;	//TA Protection
__sfr __no_init volatile unsigned char IAPAL @ 0xA6;
__sfr __no_init volatile unsigned char IAPAH @ 0xA7;
//__sfr __no_init volatile unsigned char IE @ 0xA8;
__sfr __no_init volatile union
{
  unsigned char IE; /* Interrupt Enable */
  struct /* Interrupt Enable */
  {
  	#if 0
    unsigned char EX0 : 1;
    unsigned char ET0 : 1;
    unsigned char EX1 : 1;
    unsigned char ET1 : 1;
    unsigned char ES : 1;
    unsigned char EBOD  : 1;
    unsigned char EADC  : 1;
    unsigned char EA : 1;
    #endif
    unsigned char BIT0 : 1;
    unsigned char BIT1 : 1;
    unsigned char BIT2 : 1;
    unsigned char BIT3 : 1;
    unsigned char BIT4 : 1;
    unsigned char BIT5 : 1;
    unsigned char BIT6 : 1;
    unsigned char BIT7 : 1;
  } IE_bit;
} @ 0xA8;

__sfr __no_init volatile unsigned char SADDR @ 0xA9;
__sfr __no_init volatile unsigned char WDCON @ 0xAA; //TA Protection
__sfr __no_init volatile unsigned char BODCON1 @ 0xAB; //TA Protection
__sfr __no_init volatile unsigned char P3M1 @ 0xAC;
__sfr __no_init volatile unsigned char P3S @ 0xAC; //Page1
__sfr __no_init volatile unsigned char P3M2 @ 0xAD;
__sfr __no_init volatile unsigned char P3SR @ 0xAD; //Page1
__sfr __no_init volatile unsigned char IAPFD @ 0xAE;
__sfr __no_init volatile unsigned char IAPCN @ 0xAF;

//__sfr __no_init volatile unsigned char P3   @ 0xB0;
__sfr __no_init volatile union
{
  unsigned char P3; /* Port 3 */
  struct /* Port 3 */
  {
  	#if 0
    unsigned char P30 : 1;
    unsigned char P31 : 1;
    unsigned char P32 : 1;
    unsigned char P33 : 1;
    unsigned char P34 : 1;
    unsigned char P35 : 1;
    unsigned char P36 : 1;
    unsigned char P37 : 1;
    #endif
    unsigned char BIT0 : 1;
    unsigned char BIT1 : 1;
    unsigned char BIT2 : 1;
    unsigned char BIT3 : 1;
    unsigned char BIT4 : 1;
    unsigned char BIT5 : 1;
    unsigned char BIT6 : 1;
    unsigned char BIT7 : 1;
  } P3_bit;
} @ 0xB0;

__sfr __no_init volatile unsigned char P0M1 @ 0xB1;
__sfr __no_init volatile unsigned char P0S  @ 0xB1; //Page1
__sfr __no_init volatile unsigned char P0M2 @ 0xB2;
__sfr __no_init volatile unsigned char P0SR @ 0xB2; //Page1
__sfr __no_init volatile unsigned char P1M1 @ 0xB3;
__sfr __no_init volatile unsigned char P1S  @ 0xB3; //Page1
__sfr __no_init volatile unsigned char P1M2 @ 0xB4;
__sfr __no_init volatile unsigned char P1SR @ 0xB4; //Page1
__sfr __no_init volatile unsigned char P2S @ 0xB5; 
__sfr __no_init volatile unsigned char IPH @ 0xB7;
__sfr __no_init volatile unsigned char PWMINTC @ 0xB7;	//Page1
//__sfr __no_init volatile unsigned char IP @ 0xB8;
__sfr __no_init volatile union
{
  unsigned char IP; /* IP  */
  struct /* IP  */
  {
#if 0
    unsigned char PX0 : 1;
    unsigned char PT0 : 1;
    unsigned char PX1 : 1;
    unsigned char PT1 : 1;
    unsigned char PS : 1;
    unsigned char PBOD : 1;
    unsigned char PADC : 1;
    unsigned char : 1;
#endif
        unsigned char BIT0 : 1;
    unsigned char BIT1 : 1;
    unsigned char BIT2 : 1;
    unsigned char BIT3 : 1;
    unsigned char BIT4 : 1;
    unsigned char BIT5 : 1;
    unsigned char BIT6 : 1;
    unsigned char BIT7 : 1;
  } IP_bit;
} @ 0xB8;
__sfr __no_init volatile unsigned char SADEN @ 0xB9;
__sfr __no_init volatile unsigned char SADEN_1 @ 0xBA;
__sfr __no_init volatile unsigned char SADDR_1 @ 0xBB;
__sfr __no_init volatile unsigned char I2DAT @ 0xBC;
__sfr __no_init volatile unsigned char I2STAT @ 0xBD;
__sfr __no_init volatile unsigned char I2CLK @ 0xBE;
__sfr __no_init volatile unsigned char I2TOC @ 0xBF;

//__sfr __no_init volatile unsigned I2CON @ 0xC0;
__sfr __no_init volatile union
{
  unsigned char I2CON; /* I2CON  */
  struct /* I2CON  */
  {
    #if 0
    unsigned char I2CPX : 1;
    unsigned char : 1;
    unsigned char AA : 1;
    unsigned char SI : 1;
    unsigned char STO : 1;
    unsigned char STA : 1;
    unsigned char I2CEN : 1;
    unsigned char : 1;
#endif
    unsigned char BIT0 : 1;
    unsigned char BIT1 : 1;
    unsigned char BIT2 : 1;
    unsigned char BIT3 : 1;
    unsigned char BIT4 : 1;
    unsigned char BIT5 : 1;
    unsigned char BIT6 : 1;
    unsigned char BIT7 : 1;
  } I2CON_bit;
} @ 0xC0;
__sfr __no_init volatile unsigned char I2ADDR @ 0xC1;
__sfr __no_init volatile unsigned char ADCRL @ 0xC2;
__sfr __no_init volatile unsigned char ADCRH @ 0xC3;
__sfr __no_init volatile unsigned char T3CON @ 0xC4;
__sfr __no_init volatile unsigned char PWM4H @ 0xC4; //Page1
__sfr __no_init volatile unsigned char RL3 @ 0xC5;
__sfr __no_init volatile unsigned char PWM5H @ 0xC5;	//Page1
__sfr __no_init volatile unsigned char RH3 @ 0xC6;
__sfr __no_init volatile unsigned char PIOCON1 @ 0xC6; //Page1
__sfr __no_init volatile unsigned char TA @ 0xC7;

__sfr __no_init volatile union
{
  unsigned char T2CON; /* Timer 2 Control */
  struct /* Timer 2 Control */
  {
#if 0
    unsigned char CM_RL2 : 1;
    unsigned char : 1;
    unsigned char TR2: 1;
    unsigned char : 1;
    unsigned char : 1;
    unsigned char : 1;
    unsigned char : 1;
    unsigned char TF2: 1;
#endif
        unsigned char BIT0 : 1;
    unsigned char BIT1 : 1;
    unsigned char BIT2 : 1;
    unsigned char BIT3 : 1;
    unsigned char BIT4 : 1;
    unsigned char BIT5 : 1;
    unsigned char BIT6 : 1;
    unsigned char BIT7 : 1;
  } T2CON_bit;
} @ 0xC8;

__sfr __no_init volatile unsigned char T2MOD @ 0xC9;
__sfr __no_init volatile unsigned char RCMP2L @ 0xCA;
__sfr __no_init volatile unsigned char RCMP2H @ 0xCB;
__sfr __no_init volatile unsigned char TL2 @ 0xCC; /* Timer2 Low */
__sfr __no_init volatile unsigned char PWM4L @ 0xCC; //Page1
__sfr __no_init volatile unsigned char TH2 @ 0xCD;
__sfr __no_init volatile unsigned char PWM5L @ 0xCD; //Page1
__sfr __no_init volatile unsigned char ADCMPL @ 0xCE;
__sfr __no_init volatile unsigned char ADCMPH @ 0xCF;

__sfr __no_init volatile union
{
  unsigned char PSW; /* Program Status Word */
  struct /* Program Status Word */
  {
  	#if 0
    unsigned char P : 1;
    unsigned char F1 : 1;
    unsigned char OV : 1;
    unsigned char RS0 : 1;
    unsigned char RS1 : 1;
    unsigned char F0 : 1;
    unsigned char AC : 1;
    unsigned char CY : 1;
    #endif
    unsigned char BIT0 : 1;
    unsigned char BIT1 : 1;
    unsigned char BIT2 : 1;
    unsigned char BIT3 : 1;
    unsigned char BIT4 : 1;
    unsigned char BIT5 : 1;
    unsigned char BIT6 : 1;
    unsigned char BIT7 : 1;    
  } PSW_bit;
} @ 0xD0;
__sfr __no_init volatile unsigned char PWMPH @ 0xD1;
__sfr __no_init volatile unsigned char PWM0H @ 0xD2;
__sfr __no_init volatile unsigned char PWM1H @ 0xD3;
__sfr __no_init volatile unsigned char PWM2H @ 0xD4;
__sfr __no_init volatile unsigned char PWM3H @ 0xD5;
__sfr __no_init volatile unsigned char PNP @ 0xD6;
__sfr __no_init volatile unsigned char FBD @ 0xD7;

//__sfr __no_init volatile unsigned char PWMCON0 @ 0xD8;
__sfr __no_init volatile union
{
  unsigned char PWMCON0; /* PWMCON0  */
  struct /* PWMCON0  */
  {
  	#if 0
    unsigned char  : 1;
    unsigned char  : 1;
    unsigned char  : 1;
    unsigned char  : 1;
    unsigned char CLRPWM : 1;
    unsigned char PWMF : 1;
    unsigned char LOAD : 1;
    unsigned char PWMRUN : 1;
    #endif
    unsigned char BIT0 : 1;
    unsigned char BIT1 : 1;
    unsigned char BIT2 : 1;
    unsigned char BIT3 : 1;
    unsigned char BIT4 : 1;
    unsigned char BIT5 : 1;
    unsigned char BIT6 : 1;
    unsigned char BIT7 : 1;    
  } PWMCON0_bit;
} @ 0xD8;

__sfr __no_init volatile unsigned char PWMPL @ 0xD9;
__sfr __no_init volatile unsigned char PWM0L @ 0xDA;
__sfr __no_init volatile unsigned char PWM1L @ 0xDB;
__sfr __no_init volatile unsigned char PWM2L @ 0xDC;
__sfr __no_init volatile unsigned char PWM3L @ 0xDD;
__sfr __no_init volatile unsigned char PIOCON0 @ 0xDE;
__sfr __no_init volatile unsigned char PWMCON1 @ 0xDF;

__sfr __no_init volatile union
{
  unsigned char ACC; /* Accumulator */
  struct /* Accumulator */
  {
#if 0  	
    unsigned char ACC0 : 1;
    unsigned char ACC1 : 1;
    unsigned char ACC2 : 1;
    unsigned char ACC3 : 1;
    unsigned char ACC4 : 1;
    unsigned char ACC5 : 1;
    unsigned char ACC6 : 1;
    unsigned char ACC7 : 1;
#endif
    unsigned char BIT0 : 1;
    unsigned char BIT1 : 1;
    unsigned char BIT2 : 1;
    unsigned char BIT3 : 1;
    unsigned char BIT4 : 1;
    unsigned char BIT5 : 1;
    unsigned char BIT6 : 1;
    unsigned char BIT7 : 1;    
  } ACC_bit;
} @ 0xE0;

__sfr __no_init volatile unsigned char ADCCON1 @ 0xE1;
__sfr __no_init volatile unsigned char ADCCON2 @ 0xE2;
__sfr __no_init volatile unsigned char ADCDLY @ 0xE3;
__sfr __no_init volatile unsigned char C0L @ 0xE4;
__sfr __no_init volatile unsigned char C0H @ 0xE5;
__sfr __no_init volatile unsigned char C1L @ 0xE6;
__sfr __no_init volatile unsigned char C1H @ 0xE7;
//__sfr __no_init volatile unsigned char ADCCON0 @ 0xE8;
__sfr __no_init volatile union
{
  unsigned char ADCCON0; /* ADCCON0  */
  struct /* ADCCON0  */
  {
#if 0  	
    unsigned char ADCHS0 : 1;
    unsigned char ADCHS1 : 1;
    unsigned char ADCHS2 : 1;
    unsigned char ADCHS3 : 1;
    unsigned char ETGSEL0 : 1;
    unsigned char ETGSEL1 : 1;
    unsigned char ADCS : 1;
    unsigned char ADCF : 1;
    #endif
    unsigned char BIT0 : 1;
    unsigned char BIT1 : 1;
    unsigned char BIT2 : 1;
    unsigned char BIT3 : 1;
    unsigned char BIT4 : 1;
    unsigned char BIT5 : 1;
    unsigned char BIT6 : 1;
    unsigned char BIT7 : 1;
  } ADCCON0_bit;
} @ 0xE8;
__sfr __no_init volatile unsigned char PICON @ 0xE9;
__sfr __no_init volatile unsigned char PINEN @ 0xEA;
__sfr __no_init volatile unsigned char PIPEN @ 0xEB;
__sfr __no_init volatile unsigned char PIF @ 0xEC;
__sfr __no_init volatile unsigned char C2L @ 0xED;
__sfr __no_init volatile unsigned char C2H @ 0xEE;
__sfr __no_init volatile unsigned char EIP @ 0xEF;

__sfr __no_init volatile union
{
  unsigned char B; /* B Register */
  struct /* B Register */
  {
  	#if 0  
    unsigned char B0 : 1;
    unsigned char B1 : 1;
    unsigned char B2 : 1;
    unsigned char B3 : 1;
    unsigned char B4 : 1;
    unsigned char B5 : 1;
    unsigned char B6 : 1;
    unsigned char B7 : 1;
    #endif
    unsigned char BIT0 : 1;
    unsigned char BIT1 : 1;
    unsigned char BIT2 : 1;
    unsigned char BIT3 : 1;
    unsigned char BIT4 : 1;
    unsigned char BIT5 : 1;
    unsigned char BIT6 : 1;
    unsigned char BIT7 : 1;
  } B_bit;
} @ 0xF0;
__sfr __no_init volatile unsigned char CAPCON3 @ 0xF1;
__sfr __no_init volatile unsigned char CAPCON4 @ 0xF2;
__sfr __no_init volatile unsigned char SPCR @ 0xF3;
__sfr __no_init volatile unsigned char SPCR2 @ 0xF3; //Page1
__sfr __no_init volatile unsigned char SPSR @ 0xF4;
__sfr __no_init volatile unsigned char SPDR @ 0xF5;
__sfr __no_init volatile unsigned char AINDIDS @ 0xF6;
__sfr __no_init volatile unsigned char EIPH @ 0xF7;
//__sfr __no_init volatile unsigned char SCON_1 @ 0xF8;
__sfr __no_init volatile union
{
  unsigned char SCON_1 ; /* SCON_1  Register */
  struct /* SCON_1  Register */
  {
  	#if 0
    unsigned char RI_1 : 1;
    unsigned char TI_1 : 1;
    unsigned char RB8_1 : 1;
    unsigned char TB8_1 : 1;
    unsigned char REN_1 : 1;
    unsigned char SM2_1 : 1;
    unsigned char SM1_1 : 1;
    unsigned char FE_1  : 1;
    #endif
    unsigned char BIT0 : 1;
    unsigned char BIT1 : 1;
    unsigned char BIT2 : 1;
    unsigned char BIT3 : 1;
    unsigned char BIT4 : 1;
    unsigned char BIT5 : 1;
    unsigned char BIT6 : 1;
    unsigned char BIT7 : 1;
  } SCON_1_bit;
} @ 0xF8;

__sfr __no_init volatile unsigned char PDTEN @ 0xF9; //TA Protection
__sfr __no_init volatile unsigned char PDTCNT @ 0xFA; //TA Protection
__sfr __no_init volatile unsigned char PMEN @ 0xFB;
__sfr __no_init volatile unsigned char PMD @ 0xFC;
__sfr __no_init volatile unsigned char EIP1 @ 0xFE;
__sfr __no_init volatile unsigned char EIPH1 @ 0xFF;

/*  BIT Registers  */
/*  SCON_1  */
#define SM0_1    SCON_1_bit.BIT7
#define FE_1     SCON_1_bit.BIT7 
#define SM1_1    SCON_1_bit.BIT6 
#define SM2_1    SCON_1_bit.BIT5 
#define REN_1    SCON_1_bit.BIT4 
#define TB8_1    SCON_1_bit.BIT3 
#define RB8_1    SCON_1_bit.BIT2 
#define TI_1     SCON_1_bit.BIT1 
#define RI_1     SCON_1_bit.BIT0 

/*  ADCCON0  */
#define ADCF        ADCCON0_bit.BIT7
#define ADCS        ADCCON0_bit.BIT6
#define ETGSEL1     ADCCON0_bit.BIT5
#define ETGSEL0     ADCCON0_bit.BIT4
#define ADCHS3      ADCCON0_bit.BIT3
#define ADCHS2      ADCCON0_bit.BIT2
#define ADCHS1      ADCCON0_bit.BIT1
#define ADCHS0      ADCCON0_bit.BIT0

/*  PWMCON0  */
#define PWMRUN      PWMCON0_bit.BIT7
#define LOAD        PWMCON0_bit.BIT6
#define PWMF        PWMCON0_bit.BIT5
#define CLRPWM      PWMCON0_bit.BIT4



/*  T2CON  */
#define TF2         T2CON_bit.BIT7
#define TR2         T2CON_bit.BIT2
#define CM_RL2      T2CON_bit.BIT0
 
/*  I2CON  */
#define I2CEN    I2CON_bit.BIT6
#define STA      I2CON_bit.BIT5
#define STO      I2CON_bit.BIT4
#define SI       I2CON_bit.BIT3
#define AA       I2CON_bit.BIT2
#define I2CPX	 I2CON_bit.BIT0

/*  IP  */  
#define PADC        IP_bit.BIT6
#define PBOD        IP_bit.BIT5
#define PS          IP_bit.BIT4
#define PT1         IP_bit.BIT3
#define PX1         IP_bit.BIT2
#define PT0         IP_bit.BIT1
#define PX0         IP_bit.BIT0

/*  P3  */  
#define P30		  P3_bit.BIT0


/*  IE  */
#define EA          IE_bit.BIT7
#define EADC        IE_bit.BIT6
#define EBOD        IE_bit.BIT5
#define ES          IE_bit.BIT4
#define ET1         IE_bit.BIT3
#define EX1         IE_bit.BIT2
#define ET0         IE_bit.BIT1
#define EX0         IE_bit.BIT0

/*  P2  */ 
#define P20         P2_bit.BIT0

/*  SCON  */
#define SM0         SCON_bit.BIT7
#define FE          SCON_bit.BIT7 
#define SM1         SCON_bit.BIT6 
#define SM2         SCON_bit.BIT5 
#define REN         SCON_bit.BIT4 
#define TB8         SCON_bit.BIT3 
#define RB8         SCON_bit.BIT2 
#define TI          SCON_bit.BIT1 
#define RI          SCON_bit.BIT0 

/*  P1  */     
#define P17	   P1_bit.BIT7
#define P16	   P1_bit.BIT6
#define TXD_1	   P1_bit.BIT6 
#define P15	   P1_bit.BIT5
#define P14	   P1_bit.BIT4
#define SDA	   P1_bit.BIT4    
#define P13	   P1_bit.BIT3
#define SCL	   P1_bit.BIT3  
#define P12        P1_bit.BIT2 
#define P11        P1_bit.BIT1
#define P10        P1_bit.BIT0

/*  TCON  */
#define TF1				 TCON_bit.BIT7
#define TR1				 TCON_bit.BIT6
#define TF0				 TCON_bit.BIT5
#define TR0				 TCON_bit.BIT4
#define IE1				 TCON_bit.BIT3
#define IT1				 TCON_bit.BIT2
#define IE0				 TCON_bit.BIT1
#define IT0				 TCON_bit.BIT0

/*  P0  */  
#define P07				 P0_bit.BIT7
#define RXD				 P0_bit.BIT7
#define P06				 P0_bit.BIT6
#define TXD				 P0_bit.BIT6
#define P05				 P0_bit.BIT5
#define P04				 P0_bit.BIT4
#define STADC			         P0_bit.BIT4
#define P03				 P0_bit.BIT3
#define P02				 P0_bit.BIT2
#define RXD_1			         P0_bit.BIT2
#define P01				 P0_bit.BIT1
#define MISO			         P0_bit.BIT1
#define P00				 P0_bit.BIT0
#define MOSI			         P0_bit.BIT0






                            


                            
               





























