#include<lpc214x.h>
#include<stdint.h>
void delayms(uint16_t count){
		for(int i=0;i<count;i++){
			for(int j=0;j<200;j++);
		}
}
void generateSqaureWave(){
	uint16_t value;
	PINSEL1=0x00080000;//p0.25 as analog output from dac
	while(1){
		//set dac to max 1023 o/p  for 100ms
		value=1023;
		DACR=((1<<16)|(value<<6));
		delayms(100);
		//set dac to max 0 o/p  for 100ms
		value=0;
		DACR=((1<<16)|(value<<6));
		delayms(100);
		
	}

}
void sawtooth_genrator()
{
	uint16_t value;
    PINSEL1 = 0x00080000; // P0.25 as DAC output

    while (1) {
        // Increasing part of the sawtooth wave
        value = 0;
        while (value != 1023) {
            DACR = ((1 << 16) | (value << 6));
            value++;
        }

        // Decreasing part of the sawtooth wave
        value = 1023;
        while (value != 0) {
            DACR = ((1 << 16) | (value << 6));
            value--;
        }
    }
}
void sine_genrator(){
	
	uint16_t sin_wave[42] = {512, 591, 665, 742, 808, 873, 926, 968, 998, 1017, 1023, 1017, 998, 968, 926, 873, 808, 742, 665, 591, 512, 436, 359, 282, 216, 211, 151, 97, 55, 25, 6, 0, 6, 25, 55, 97, 151, 211, 216, 282, 359, 436};
    uint16_t value;
    uint8_t i = 0;
    PINSEL1 = 0x00080000; // P0.25 as DAC output
    while (1) {
        while (i != 42) {
            value = sin_wave[i];
            DACR = ((1 << 16) | (value << 6));
            delayms(1);
            i++;
        }
        i = 0;
    }
	
}


int main(){
	//generateSqaureWave();
	//sawtooth_genrator();
	sine_genrator();
}