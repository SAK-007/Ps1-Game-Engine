#include "Engine/ALL.h"
#include "sprites.h"

Image player;
int x = 128,y = 128;
int Speed = 5;

void main(){
	
	initializeMemory();
	initializeScreen();
	initializeFont();
	initializePad();
	setScreenBackgroundColor(0,0,255); //(R,G,B) 
	player = createImage(img_crash);
	
	
	while(1)
	{
		padUpdate(); //updates the pad
		if(padCheck(Pad1Up)){y -= Speed;}
		if(padCheck(Pad1Down)){y += Speed;}
		if(padCheck(Pad1Left)){x -= Speed;}
		if(padCheck(Pad1Right)){x += Speed;}
		
		player = moveImage(player,x,y);
		
		clearDisplay();
		drawImage(player);
		display();
	}
	
	
}