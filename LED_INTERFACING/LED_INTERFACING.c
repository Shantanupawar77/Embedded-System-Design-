#include<lpc214x.h>
void delay(){
	for(int i=0;i<10000;i++){
		for(int j=0;j<1000;j++);
	}
}
int main(){
	//Set the direction as an output
	//p1.24 p1.25 p1.26 p1.27 p1.28 p1.29 p1.30 p1.31 
	//Blinking all the leds simultaneously
	//IODIR1=IODIR1|(0xFF000000);
	//while(1){
		
		//IOSET1=IOSET1|(0xFF000000);
		//Give some delay
		//delay();
		
		//IOCLR1=IOCLR1|(0xFF000000);
		//delay();
	//}
	//Set the direction as an output
	//p1.24 p1.25 p1.26 p1.27 p1.28 p1.29 p1.30 p1.31 
	
	//Blinking all the leds Alternatevely
	IODIR1=IODIR1|(0xFF000000);
	while(1){
		IOSET1=IOSET1|(0xAA000000);
		IOCLR1=IOCLR1|(0x55000000);
		delay();
		IOSET1=IOSET1|(0x55000000);
		IOCLR1=IOCLR1|(0xAA000000);
		delay();
	}
	
}