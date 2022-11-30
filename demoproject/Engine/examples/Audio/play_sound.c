#include "Engine/ALL.h"
#include "Audio.h"

int r = 0,c = 0;
void main(){
	
	initializeMemory();
	initializeScreen();
	initializeFont();
	setScreenBackgroundColor(0,0,255); //(R,G,B) 
	
	
	audioInit();
	audioTransferVagToSPU(&hpup,hpup_size,SPU_00CH);
	
	
	
	while(1)
	{
		c++;
		if(c > r)
		{
			audioPlay(SPU_00CH);
			r = c + 100;
		}
		FntPrint("\t\t   Playing Sound");


		

		
		clearDisplay();

		display();
	}
	
	
}