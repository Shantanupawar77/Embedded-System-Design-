#include<lpc214x.h>
int main(void){
	unsigned int result;
	PINSEL1=0x01000000;
	AD0CR=0x00200402;
	while(1){
		AD0CR=AD0CR|(1<<24);
		while(!(AD0DR1 & 0x80000000));
		result=AD0DR1;
		result=(result>>6);
		result=(result & 0x000003FF);
	}
}