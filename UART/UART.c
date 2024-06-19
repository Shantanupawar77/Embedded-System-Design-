#include<lpc21xx.h>
void transmit(unsigned char ch){
	while(!(U0LSR&0x01<<5));
	U0THR=ch;
}
unsigned char receive(){
	while(!(U0LSR & 0X01));
	return U0RBR;
}
int main(){
	unsigned char key;
	//int i;
	//unsigned char temp[20]="Hello I am Shantanu";
	PINSEL0=0x00000005;//UART P0.0 AND P0.1
	U0LCR=0x83;//DLAB=1 TO set baudrate 8 bit data
	U0DLM=0x00;
	U0DLL=97;
	U0LCR=0x03; //DLAB=0 to access tx and rx registers
	//for(i=0;temp[i]!='\0';i++){
	//	transmit(temp[i]);
	//}
	while(1){
	key=receive();
	transmit(key);
	}
	return 0;
}