#include <lpc214x.h>
void initPWM(void);                        // Initialize PWM
void initClocks(void);           // Setup PLL and Clock Frequency
void delay(){
	for(int i=0; i<10000;i++){
		for(int j=0; j<1000; j++);
	}
}

int main(void)
{
  initClocks(); //Initialize CPU and Peripheral Clocks @ 60Mhz
  initPWM(); //Initialize PWM
  //IO1DIR = 0x1; This is not needed!
  //Also by default all pins are configured as Inputs after MCU Reset.
    while(1)
    {
    
      PWMMR4 = 2500; //T-ON=25% , Hence 25% Bright
      PWMLER = (1<<4); //Update Latch Enable bit for PWMMR4
    
    }
    //return 0; //normally this wont execute ever
}

void initPWM(void)
{
  PINSEL0 = (PINSEL0 & ~(1 << 16)) | (1 << 17); // Select PWM4 output for Pin0.8
  
  PWMPR = 60-1; // 1 micro-second resolution
  PWMMR0 = 10000; // 10000 micro-second period duration (10ms)
  
  PWMMCR = (1<<1); // Reset PWMTC on PWMMR0 match
  PWMLER = (1<<0)|(1<<4); // update MR0 and MR4
  PWMPCR = (1<<12); // enable PWM4 output
  PWMTCR = (1<<1) ; //Reset PWM TC & PR

  //Now , the final moment - enable everything
  PWMTCR = (1<<0) | (1<<3); // enable counters and PWM Mode

  //PWM Generation goes active now - LED must be 25% Bright after boot!!
  //Now you can get the PWM output at Pin P0.8!
}

void initClocks(void)
{
  PLL0CON = 0x01;   //Enable PLL
  PLL0CFG = 0x24;   //Multiplier and divider setup
  PLL0FEED = 0xAA;  //Feed sequence
  PLL0FEED = 0x55;
  
  while(!(PLL0STAT & 0x00000400)); //is locked?
    
  PLL0CON = 0x03;   //Connect PLL after PLL is locked
  PLL0FEED = 0xAA;  //Feed sequence
  PLL0FEED = 0x55;
  VPBDIV = 0x01;    // PCLK is same as CCLK i.e.60 MHz
}
