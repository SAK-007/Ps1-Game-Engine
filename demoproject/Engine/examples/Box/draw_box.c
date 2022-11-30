#include "Engine/ALL.h"

Box box;


void main(){
	
	initializeMemory();
	initializeScreen();
	initializeFont();
	setScreenBackgroundColor(0,0,255); //(R,G,B) 
	
	box = createBox(createPolygonColor(255,0,0),32,32,64,64);//x1,y1,x2,y2 coordinates
	
	while(1)
	{
		clearDisplay();
		drawBox(box);
		display();
	}
	
	
}