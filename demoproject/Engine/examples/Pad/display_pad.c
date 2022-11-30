#include "Engine/ALL.h"


void main(){
	
	initializeMemory();
	initializeScreen();
	initializeFont();
	initializePad();
	setScreenBackgroundColor(0,0,255); //(R,G,B) 
	
	
	while(1)
	{
		padUpdate(); //updates the pad
		if(padCheck(Pad1Up)){FntPrint("Pad1Up\n\n");}
		if(padCheck(Pad1Left)){FntPrint("Pad1Left\n\n");}
		if(padCheck(Pad1Right)){FntPrint("Pad1Right\n\n");}
		if(padCheck(Pad1Down)){FntPrint("Pad1Down\n\n");}
		if(padCheck(Pad1Cross)){FntPrint("Pad1Cross\n\n");}
		if(padCheck(Pad1Circle)){FntPrint("Pad1Circle\n\n");}
		if(padCheck(Pad1Square)){FntPrint("Pad1Square\n\n");}
		if(padCheck(Pad1Triangle)){FntPrint("Pad1Triangle\n\n");}
		
		
		if(padCheck(Pad2Up)){FntPrint("Pad2Up\n\n");}
		if(padCheck(Pad2Left)){FntPrint("Pad2Left\n\n");}
		if(padCheck(Pad2Right)){FntPrint("Pad2Right\n\n");}
		if(padCheck(Pad2Down)){FntPrint("Pad2Down\n\n");}
		if(padCheck(Pad2Cross)){FntPrint("Pad2Cross\n\n");}
		if(padCheck(Pad2Circle)){FntPrint("Pad2Circle\n\n");}
		if(padCheck(Pad2Square)){FntPrint("Pad2Square\n\n");}
		if(padCheck(Pad2Triangle)){FntPrint("Pad2Triangle\n\n");}
		


		

		
		clearDisplay();

		display();
	}
	
	
}