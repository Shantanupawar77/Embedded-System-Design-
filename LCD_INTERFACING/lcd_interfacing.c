#include<lpc214x.h>
#define RS 1<<20
#define E 1<<21

void delay(){
	for(int i=0;i<1000;i++){
		for(int j=0;j<1000;j++);
	}
}
void lcd_cmd(unsigned char cmd){
	IOCLR0=0xFF<<12;//Clear data lines
	IOSET0=cmd<<12;//send command
	IOCLR1=RS; //WHY RS=0 Need to configure as command
	delay();
	//Enable working high to low
	IOSET1=E;//High
	delay();
	IOCLR1=E;//Low
	delay();
}
void LCD_DATA(unsigned char data){
	IOCLR0=0xFF<<12;//Clear data lines
	IOSET0=data<<12;//send command
	IOSET1=RS; //WHY RS=1 Need to configure as DATA
	delay();
	//Enable working high to low
	IOSET1=E;//High
	delay();
	IOCLR1=E;//Low
	delay();
}
void sendMessage(char *message){
	unsigned int i=0;
	while(message[i]!='/0'){
		//Send the character by character data on the lcd
		LCD_DATA(message[i]);
		i++;
	}
}
void LCD_init(){
	//P0.12 to P0.21 are set as output pins
	IODIR0=0xFF<<12;
	//P1.20 to P1.21 are set as output pins
	IODIR1=3<<20;
	//8 bit lcd mode
	lcd_cmd(0x38);
	//Clear data
	lcd_cmd(0x01);
	//Display on cursor blinking
	lcd_cmd(0x0F);
	//Shift cursor to the right
	lcd_cmd(0x06);
}
int main(){
	//Initialize all the require lcd lines 
	LCD_init();
	//send the first command
	lcd_cmd(0x80); //1st line oth position
	sendMessage("Hello");
	//send the second command
	lcd_cmd(0xc0); //2st line oth position
	sendMessage("Shantanu");
	
}