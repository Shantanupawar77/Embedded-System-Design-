#include <lpc214x.h>
#include <stdio.h>
#include <stdint.h>
#define ADC0_1 (1<<1)
#define ADC_DIVIDER (4<<8) //we divide PCLK by 4 since ADC only works on clk less than 4.5Mhz
#define ADC0_Powerdown_mode_off (1<<21) // bit 1 here TURNS THE ADC ON

// start debugging then go to view->serial windows->uart #1
// to change the input analog voltage go to peripherals->A/D converter->A/D converter 0, in the popped up window change input voltage in AD01 (in analog inputs subsection) (0 to 3.3V)

// make sure freq of LPC is 12Mhz
char receive_string[50];

void delay_ms(uint16_t j) /* Function for delay in milliseconds  */
{
    uint16_t x,i;
	for(i=0;i<j;i++)
	{
    for(x=0; x<6000; x++);    /* loop to generate 1 millisecond delay with Cclk = 60MHz */
	}
}

void UART0_init(void)
{
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
	uint8_t i = 0;
	while( str[i] != '\0' )
	{
		UART0_TxChar(str[i]);
		i++;
	}
}

unsigned char UART0_RxChar(void) //A function to receive a byte on UART0
{
	while( (U0LSR & 0x01) == 0);	//Wait till RDR bit becomes 1 which tells that receiver contains valid data
		return U0RBR;
}

void UART0_RxString(void) //A function to receive string on UART0
{
	uint8_t i = 0;
	do{
	while( (U0LSR & 0x01) == 0);
			receive_string[i] = U0RBR;
		i++;
	}while( (U0RBR != 0x0D) );
}



void ADC_Init() {
    PINSEL1 = 0x01000000; /* P0.28 as AD0.1 */
		AD0CR = ADC0_1 | ADC_DIVIDER | ADC0_Powerdown_mode_off; /* ADC operational on 0.28 (ADC 0.1), 10-bits, 11 clocks for conversion */
}

unsigned int ADC_Read() {
    unsigned int result;
		AD0CR = AD0CR | (1<<24); /* Start Conversion */
		while ( !(AD0DR1 & 0x80000000) ); /* Wait till DONE */
		result = AD0DR1;
		result = (result>>6);
		result = (result & 0x000003FF); //Only take the last 10 bits
	return result;
}


// This pgm for 60Mhz clk & 15Mhz pclk
void set_pll()
{
  PLL0CON=0x01;             // PPLE=1 & PPLC=0 so it will be enabled  but not connected after FEED sequence
  PLL0CFG=0x24;          // set the multipler to 5 (i.e actually 4) i.e 12x5 = 60 Mhz (M - 1 = 4), Set P=2 since we want FCCO in range So , Assign PSEL =01 in PLL0CFG as per the table.
  PLL0FEED=0XAA;          //feed
  PLL0FEED=0X55;
  while((PLL0STAT&(1<<10))==0);      // check whether PLL has locked on to the  desired freq by reading the lock bit in the PPL0STAT register
  PLL0CON=0x03;          //enable & connect pll
  PLL0FEED=0XAA;
  PLL0FEED=0X55;
  VPBDIV = 0x00;          // PCLK is = 1/4 * CCLK i.e 15Mhz when VPBDIV = 00
}



int main() {
    unsigned int adc_val;
    char lcd_str[10];
	
		set_pll(); //PLL for proper PCLK of 15Mhz (optional I think?)
    
		UART0_init();
    ADC_Init();
	
		UART0_SendString("ADC started");
    
    while(1) {
				adc_val = ADC_Read();
				//adc_val = 0;
        sprintf(lcd_str, "%04d", adc_val);  // Convert ADC value to string
        UART0_SendString("ADC:");
        for(int i = 0; i < 4; i++)
            UART0_TxChar(lcd_str[i]);  // Display ADC value on LCD
				UART0_SendString("\r\n");
        delay_ms(100);
    }
		
		return 0;
}

