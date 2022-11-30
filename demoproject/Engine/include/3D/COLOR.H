/*
*
*  COLOR.H
*
*  Author:SAK-007
*
*  Contains:All function for Playstation Games colors
*
*
*/

typedef struct{
	int r;
	int g;
	int b;
}COLOR;

typedef struct{
	int r;
	int g;
	int b;
}Colour;


COLOR createCOLOR(int r, int g, int b) {
	COLOR color = {.r = r, .g = g, .b = b};
	return color;
}

Colour createColour(int r, int g, int b) {
	Colour color = {.r = r, .g = g, .b = b};
	return color;
}


