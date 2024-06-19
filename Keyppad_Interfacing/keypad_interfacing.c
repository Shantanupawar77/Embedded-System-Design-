#include<lpc214x.h>

//Define all the pins 

#define r0 0x00080000 //p1.19
#define r1 0x00100000 //p1.20
#define r2 0x00200000 //p1.21
#define r3 0x00400000 //p1.22

#define c0 0x00010000  //p1.16
#define c1 0x00020000  //p1.17
#define c2 0x00040000  //p1.18

unsigned int seg[10]={
	0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,
	0x80,0x90,0xC0
};

int main(){
	//Pins 19, 20, 21,and 22 of Port 1 are configured as outputs,
	//while pins 16, 17, and 18 are inputs.
	IODIR1=0x00780000;
	
	
	//To display on the 7 segment led 
	//we will configure 
	IODIR0=IODIR0|(0x000000FF);//configured as output
	
	while(1){
		//clear row0 and set all the other rows
		IOCLR1=IOCLR1|r0;
		IOSET1=IOSET1|(r1|r2|r3);
		//Before pressing the key 
		//IOPIN1=111111
		//C0=0000...001
		
		//All columns are on 
		//check column 0 is pressed 
		if(!(IOPIN1&c0)){
			//After pressing the key 
			//IOPIN1=111110
		//C0=0000...001
			//Wait until the key is released
			while(!(IOPIN1&c0));
			//clear all segments and set the segment to display '1'
			IOCLR0=(seg[1]|seg[2]|seg[3]|seg[4]|seg[5]|seg[6]|seg[7]|seg[8]|seg[9]);
			IOSET0=seg[0];
			//IOPIN0=seg[0];
		}
		
		//check column 1 is pressed 
		if(!(IOPIN1&c1)){
			//After pressing the key 
			//IOPIN1=111110
		//C0=0000...001
			//Wait until the key is released
			while(!(IOPIN1&c1));
			//clear alle segments and set the segment to display '2'
			IOCLR0=(seg[0]|seg[2]|seg[3]|seg[4]|seg[5]|seg[6]|seg[7]|seg[8]|seg[9]);
			IOSET0=seg[1];
			//IOPIN0=seg[1];
		}
		//check column 2 is pressed 
		if(!(IOPIN1&c2)){
			//After pressing the key 
			//IOPIN1=111110
		//C0=0000...001
			//Wait until the key is released
			while(!(IOPIN1&c2));
			//clear alle segments and set the segment to display '3'
			IOCLR0=(seg[0]|seg[1]|seg[3]|seg[4]|seg[5]|seg[6]|seg[7]|seg[8]|seg[9]);
			IOSET0=seg[2];
			//IOPIN0=seg[2];
		}
		
		
		//clear row1 and set all the other rows
		IOCLR1=IOCLR1|r1;
		IOSET1=IOSET1|(r0|r2|r3);
		//Before pressing the key 
		//IOPIN1=111111
		//C0=0000...001
		
		//All columns are on 
		//check column 0 is pressed 
		if(!(IOPIN1&c0)){
			//After pressing the key 
			//IOPIN1=111110
		//C0=0000...001
			//Wait until the key is released
			while(!(IOPIN1&c0));
			//clear alle segments and set the segment to display '1'
			IOCLR0=(seg[1]|seg[2]|seg[0]|seg[4]|seg[5]|seg[6]|seg[7]|seg[8]|seg[9]);
			IOSET0=seg[3];
			//IOPIN0=seg[3];
		}
		
		//check column 1 is pressed 
		if(!(IOPIN1&c1)){
			//After pressing the key 
			//IOPIN1=111110
		//C0=0000...001
			//Wait until the key is released
			while(!(IOPIN1&c1));
			//clear alle segments and set the segment to display '2'
			IOCLR0=(seg[0]|seg[1]|seg[2]|seg[3]|seg[5]|seg[6]|seg[7]|seg[8]|seg[9]);
			IOSET0=seg[4];
			//IOPIN0=seg[4];
		}
		//check column 2 is pressed 
		if(!(IOPIN1&c2)){
			//After pressing the key 
			//IOPIN1=111110
		//C0=0000...001
			//Wait until the key is released
			while(!(IOPIN1&c2));
			//clear alle segments and set the segment to display '3'
			IOCLR0=(seg[0]|seg[1]|seg[3]|seg[4]|seg[2]|seg[6]|seg[7]|seg[8]|seg[9]);
			IOSET0=seg[5];
			//IOPIN0=seg[5];
		}
		
		
		
		//clear row2 and set all the other rows
		IOCLR1=IOCLR1|r2;
		IOSET1=IOSET1|(r0|r1|r3);
		//Before pressing the key 
		//IOPIN1=111111
		//C0=0000...001
		
		//All columns are on 
		//check column 0 is pressed 
		if(!(IOPIN1&c0)){
			//After pressing the key 
			//IOPIN1=111110
		//C0=0000...001
			//Wait until the key is released
			while(!(IOPIN1&c0));
			//clear alle segments and set the segment to display '1'
			IOCLR0=(seg[1]|seg[2]|seg[0]|seg[4]|seg[5]|seg[3]|seg[7]|seg[8]|seg[9]);
			IOSET0=seg[6];
			//IOPIN0=seg[6];
		}
		
		//check column 1 is pressed 
		if(!(IOPIN1&c1)){
			//After pressing the key 
			//IOPIN1=111110
		//C0=0000...001
			//Wait until the key is released
			while(!(IOPIN1&c1));
			//clear alle segments and set the segment to display '2'
			IOCLR0=(seg[0]|seg[1]|seg[2]|seg[3]|seg[4]|seg[5]|seg[6]|seg[8]|seg[9]);
			IOSET0=seg[7];
			//IOPIN0=seg[7];
		}
		//check column 2 is pressed 
		if(!(IOPIN1&c2)){
			//After pressing the key 
			//IOPIN1=111110
		//C0=0000...001
			//Wait until the key is released
			while(!(IOPIN1&c2));
			//clear alle segments and set the segment to display '3'
			IOCLR0=(seg[0]|seg[1]|seg[2]|seg[3]|seg[4]|seg[5]|seg[6]|seg[7]|seg[9]);
			IOSET0=seg[8];
			//IOPIN0=seg[8];
		}
		
		//clear row2 and set all the other rows
		IOCLR1=IOCLR1|r3;
		IOSET1=IOSET1|(r0|r1|r2);
		//Before pressing the key 
		//IOPIN1=111111
		//C0=0000...001
		
		//All columns are on 
		//check column 0 is pressed 
		if(!(IOPIN1&c1)){
			//After pressing the key 
			//IOPIN1=111110
		//C0=0000...001
			//Wait until the key is released
			while(!(IOPIN1&c1));
			//clear alle segments and set the segment to display '1'
			IOCLR0=(seg[0]|seg[1]|seg[2]|seg[3]|seg[4]|seg[5]|seg[6]|seg[7]|seg[8]);
			IOSET0=seg[9];
			//IOPIN0=seg[9];
		}
		
		
		
	}

	
}