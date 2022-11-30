#include "Engine/ALL.h"

Box box;
int x = 128,y = 128;
int Speed = 5;

void main(){
	
	initializeMemory();
	initializeScreen();
	initializeFont();
	initializePad();
	setScreenBackgroundColor(0,0,255); //(R,G,B) 
	
	box = createBox(createPolygonColor(255,0,0),32,32,64,64);//x1,y1,x2,y2 coordinates
	
	
	while(1)
	{
		padUpdate(); //updates the pad
		if(padCheck(Pad1Up)){y -= Speed;}
		if(padCheck(Pad1Down)){y += Speed;}
		if(padCheck(Pad1Left)){x -= Speed;}
		if(padCheck(Pad1Right)){x += Speed;}
		
		box = moveBox(box,x,y);
		clearDisplay();
		drawBox(box);
		display();
	}
	
	
}