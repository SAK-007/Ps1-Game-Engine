/*
 *
 *  DISPLAY.H
 *
 *
 *  Author:SAK-007
 *
 *
 *  All display funcs
 *
 */


#include <stdlib.h>
#include <stdio.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>
#include <libetc.h>
#include <sys/types.h>
#include "CONFIG.H"


void initializeOrderingTable();
void FlushRAM();


int 		SCREEN_WIDTH, SCREEN_HEIGHT;
GsOT 		OrderingTable[2];
GsOT_TAG  	minorOrderingTable[2][1<<OT_LENGTH];
PACKET 		GPUOutputPacket[2][PACKETMAX];
short 		CurrentBuffer;

int red = 255;
int green = 255;
int blue = 255;




//Set the screen mode to either SCREEN_MODE_PAL or SCREEN_MODE_NTSC
void setScreenMode(int mode) {
	if (mode == SCREEN_MODE_PAL) { // SCEE string address
    	// PAL MODE
    	SCREEN_WIDTH = 320;
    	SCREEN_HEIGHT = 256;
    	SetVideoMode(1);
   	} else {
     	// NTSC MODE
     	SCREEN_WIDTH = 320;
     	SCREEN_HEIGHT = 240;

     	SetVideoMode(0);
   }
	GsInitGraph(SCREEN_WIDTH, SCREEN_HEIGHT, GsINTER|GsOFSGPU, 1, 0);
	GsDefDispBuff(0, 0, 0, SCREEN_HEIGHT);
}




void setScreenBackgroundColor(int r,int g,int b) {

	if(r > 255 || g > 255 || b > 255)
	{
		red = 0;
		green = 0;
		blue = 0;
		printf("R,G,B Value must be less than 256.");
	}

	else
	{
	red = r;
	green = g;
	blue = b;
	}
}


void setDisplayBackgroundColor(int r,int g,int b) {

	if(r > 255 || g > 255 || b > 255)
	{
		red = 0;
		green = 0;
		blue = 0;
	}

	else
	{
	red = r;
	green = g;
	blue = b;
	}
}






void initializeScreen() {
	if (*(char *)0xbfc7ff52=='E') setScreenMode(SCREEN_MODE_PAL);
   	else setScreenMode(SCREEN_MODE_NTSC);

	SetDispMask(1);
	ResetGraph(0);
	FlushRAM();
	GsInitGraph(SCREEN_WIDTH, SCREEN_HEIGHT, GsINTER|GsOFSGPU, 1, 0); //Set up interlation..
	GsDefDispBuff(0, 0, 0, SCREEN_HEIGHT);	//..and double buffering.
	initializeOrderingTable();
}



void initializeDisplay() {
	if (*(char *)0xbfc7ff52=='E') setScreenMode(SCREEN_MODE_PAL);
   	else setScreenMode(SCREEN_MODE_NTSC);

	SetDispMask(1);
	ResetGraph(0);
	FlushRAM();
	GsInitGraph(SCREEN_WIDTH, SCREEN_HEIGHT, GsINTER|GsOFSGPU, 1, 0); //Set up interlation..
	GsDefDispBuff(0, 0, 0, SCREEN_HEIGHT);	//..and double buffering.
	initializeOrderingTable();
}





void initializeOrderingTable(){
	GsClearOt(0,0,&OrderingTable[GsGetActiveBuff()]);

	OrderingTable[0].length = OT_LENGTH;
	OrderingTable[1].length = OT_LENGTH;
	OrderingTable[0].org = minorOrderingTable[0];
	OrderingTable[1].org = minorOrderingTable[1];

	GsClearOt(0,0,&OrderingTable[0]);
	GsClearOt(0,0,&OrderingTable[1]);
}






void FlushRAM() {
	RECT rectTL;
	setRECT(&rectTL, 0, 0, 1024, 512);
	ClearImage2(&rectTL, 0, 0, 0);
    DrawSync(0);
    return;
}

void clearDisplay() {
	CurrentBuffer = GsGetActiveBuff();
	FntFlush(-1);
	GsSetWorkBase((PACKET*)GPUOutputPacket[CurrentBuffer]);
	GsClearOt(0, 0, &OrderingTable[CurrentBuffer]);
}



void display() {
	CurrentBuffer = GsGetActiveBuff();
	DrawSync(0);
	VSync(0);
	GsSwapDispBuff();
	GsSortClear(red, green, blue, &OrderingTable[CurrentBuffer]);
	GsDrawOt(&OrderingTable[CurrentBuffer]);
}

