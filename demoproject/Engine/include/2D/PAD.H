//Thanks to ORION for his amazing PSX library.
//This is almost directly taken from his library, from System.h and System.c.
//A good resource from ORION -> http://onorisoft.free.fr/retro.htm?psx/tutorial/tuto.htm
#include "CONFIG.H"

int	SysPad, SysPadT;


void initializePad() {
	PadInit(0);
}

void padReset(void) {
	SysPad = 0;
	SysPadT = 0;
}

void padUpdate(void){
	int	pad = PadRead(0);
	SysPadT = pad & (pad ^ SysPad);
	SysPad = pad;
}
