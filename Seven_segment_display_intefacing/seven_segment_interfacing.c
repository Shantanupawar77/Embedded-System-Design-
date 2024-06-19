#include<lpc214x.h>
unsigned int a[16]={
	0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,
	0x80,0x90,0x88,0x83,0xC6,0xA1,0x86,0x8E
};
void delayms(unsigned int count){
	for(int i=0;i<count;i++){
		for(int j=0;j<2000;j++);
	}
}
int main(){
	PINSEL0=0x00000000;//Configured as gpio
	IODIR0=IODIR0|(0x000000FF);//configured as output
	unsigned int i;
	while(1){
		for(int i=0;i<16;i++){
			IOPIN0=a[i];
			delayms(1000);
		}
	}
	return 0;
	
}