#include "Engine/ALL.h"

void main(){
	initializeMemory();
	initializeScreen();
	initializeFont();
	setScreenBackgroundColor(0,0,255); //(R,G,B) 
	
	while(1)
	{
		FntPrint("Hello world \n\n Game engine !!");
		
		clearDisplay();
		display();
	}
	
	
}