#include<lpc214x.h>
//Frequency of oscillator 12MHz
//PCLK=15MHz for UART peripheral
// 1/4 cclk
void set_pll(){
	//Enable PLL
	PLL0CON=0x01;
	//Set multiplier 5(i.e. actually 4) 12x5=60
	//p=2
	PLL0CFG=0x24;
	//Feed -key
	PLL0FEED=0xAA;
	PLL0FEED=0x55;
	//Check whether pll has locked on the desired frequency
	while((PLL0STAT&(1<<10))==0);
	//Now connect and enable
	PLL0CON=0x03;
	PLL0FEED=0xAA;
	PLL0FEED=0x55;
	VPBDIV=0x00; //PCLK=1/4*cclk i.e 15hz when VPBDIV=00
	
}
void UART0_init(){
	PINSEL0 = PINSEL0 | 0x00000005;	// Enable UART0 Rx0 and Tx0 pins of UART0
	U0LCR = 0x83;	// DLAB = 1, 1 stop bit, 8-bit character length
	U0DLM = 0x00;	// For baud rate of 9600 with Pclk = 15MHz
	U0DLL = 0x61;	// We get these values of U0DLL and U0DLM from formula
	U0LCR = 0x03; // DLAB = 0

}
void UART0_TxChar(char ch) //A function to send a byte on UART0
{
	U0THR = ch;
	while( (U0LSR & 0x40) == 0 );	//Wait till THRE bit becomes 1 which tells that transmission is completed
}

void UART0_SendString(char* str) //A function to send string on UART0
{
	unsigned int i = 0;
	while( str[i] != '\0' )
	{
		UART0_TxChar(str[i]);
		i++;
	}
}

int main(){
	set_pll();
	UART0_init();
	UART0_SendString("PLL frequency locked, PLL enabled, PLL connected\r\n");

}