/*
 *  Sprite.H
 *
 *  Created on: Oct 23, 2022
 *  Author: SAK-007
 *
 *
 *  Contains: Sprites
 *
 */


#define ROT_ONE 4096
#define MAX_OBJECTS 100

#include <STDLIB.H>
#include <STDIO.H>
#include <LIBGTE.H>
#include <LIBGPU.H>
#include <LIBGS.H>
#include <LIBETC.H>
#include <LIBSPU.H>
#include <SYS/TYPES.H>
#include "CONFIG.H"

typedef struct {
	RECT rect;
	RECT crect;
	GsIMAGE tim_data;
	SPRITE sprite;
} Image;

typedef struct {
	RECT rect;
	RECT crect;
	GsIMAGE tim_data;
	GsSPRITE sprite;
}Sprite;

typedef struct {
	int r;
	int g;
	int b;
} Color;


struct {
	VECTOR	position;
	SVECTOR rotation;
	GsCOORDINATE2 coord2;
} Camera;



GsOT 		  OrderingTable[2];
short 		  CurrentBuffer;


Image createImage(unsigned char imageData[]) {


	Image image;
	GsGetTimInfo ((u_long *)(imageData+4),&image.tim_data);


	image.rect.x = image.tim_data.px;            	// tim start X coord to put image data in frame buffer
	image.rect.y = image.tim_data.py;            	// tim start Y coord to put image data in frame buffer
	image.rect.w = image.tim_data.pw;            	// data width
	image.rect.h = image.tim_data.ph;            	// data height
	LoadImage(&image.rect, image.tim_data.pixel);

	// Load the CLUT into the frame buffer
	image.crect.x = image.tim_data.cx;            	// x pos to put CLUT in frame buffer
	image.crect.y = image.tim_data.cy;           	// y pos to put CLUT in frame buffer
	image.crect.w = image.tim_data.cw;            	// width of CLUT
	image.crect.h = image.tim_data.ch;            	// height of CLUT
	LoadImage(&image.crect, image.tim_data.clut);

	// Initialize sprite
	image.sprite.attribute = 0x1000000; 			// (0x1 = 8-bit, 0x2 = 16-bit)
	image.sprite.x = 0;                         	// draw at x coord
	image.sprite.y = 0;                          	// draw at y coord
	image.sprite.w = image.tim_data.pw * 2;         // width of sprite
	image.sprite.h = image.tim_data.ph;             // height of sprite

	image.sprite.tpage = GetTPage(
			1,   								// 0=4-bit, 1=8-bit, 2=16-bit
			1,   								// semitransparency rate
			image.tim_data.px, 						// framebuffer pixel x
			image.tim_data.py  						// framebuffer pixel y
	);

	image.sprite.r = 128;							// color red blend
	image.sprite.g = 128;							// color green blend
	image.sprite.b = 128;							// color blue blend
	image.sprite.u=(image.tim_data.px - 320) * 2;   // position within timfile for sprite
	image.sprite.v=image.tim_data.py;				// position within timfile for sprite
	image.sprite.cx = image.tim_data.cx;            // CLUT location x
	image.sprite.cy = image.tim_data.cy;            // CLUT location y
	image.sprite.mx = 0;                            // rotation x coord
	image.sprite.my = 0;                            // rotation y coord
	image.sprite.scalex = ONE;                      // scale x (ONE = 100%)
	image.sprite.scaley = ONE;                      // scale y (ONE = 100%)
	image.sprite.rotate = 0;                        // rotation

	return image;
}

Image moveImage(Image image, int x, int y) {
	image.sprite.x = x;
	image.sprite.y = y;
	return image;
}


void drawImage(Image image) {
	CurrentBuffer = GsGetActiveBuff();
	GsSortSprite(&image.sprite, &OrderingTable[CurrentBuffer], 0);
}



void createSprite(unsigned char imageData[], int x, int y, GsSPRITE **sprite) {

	// Initialize image
	GsIMAGE* tim_data;
	RECT* rect;
	RECT* crect;
	tim_data = malloc3(sizeof(GsIMAGE));
	GsGetTimInfo ((u_long *)(imageData+4),tim_data);
	rect = malloc3(sizeof(RECT));
	crect = malloc3(sizeof(RECT));

	// Load the image into the GPU memory (frame buffer)
	rect->x = tim_data->px; // x position of image in frame buffer
	rect->y = tim_data->py; // y position of image in frame buffer
	rect->w = tim_data->pw; // width in frame buffer
	rect->h = tim_data->ph; // height in frame buffer
	printf("Framebuffer info {x=%d, y=%d, w=%d, h=%d}\n", rect->x, rect->y, rect->w, rect->h);
	LoadImage(rect, tim_data->pixel);

	// Load the color lookup table (CLUT) into the GPU memory (frame buffer)
	crect->x = tim_data->cx; // x position of CLUT in frame buffer
	crect->y = tim_data->cy; // y position of CLUT in frame buffer
	crect->w = tim_data->cw; // width of CLUT in frame buffer
	crect->h = tim_data->ch; // height of CLUT in frame buffer
	printf("CLUT info {x=%d, y=%d, w=%d, h=%d}\n", crect->x, crect->y, crect->w, crect->h);
	LoadImage(crect, tim_data->clut);

	// Initialize sprite (see GSSprite at PSYQ/DOCS/LIBREF.PDF)
	*sprite = malloc3(sizeof(GsSPRITE));
	(*sprite) -> attribute = 0x0000000;
	(*sprite) -> x = x;
	(*sprite) -> y = y;
	(*sprite) -> w = tim_data->pw * 4;
	(*sprite) -> h = tim_data->ph;
	(*sprite) -> tpage = GetTPage(
			0, 		 // 0=4-bit, 1=8-bit, 2=16-bit
			1,       // semitransparency rate
			rect->x, // framebuffer x position of image
			rect->y  // framebuffer y position of image
	);
	(*sprite)->r = 128;  						// Color red blend
	(*sprite)->g = 128;  						// Color green blend
	(*sprite)->b = 128;  						// Color blue blend
	(*sprite)->u = (tim_data->px * 4) % 256;	// Position within tpage for sprite (0-256)
	(*sprite)->v = (tim_data->py % 256);		// Position within tpage for sprite (0-256)
	(*sprite)->cx = tim_data->cx;               // CLUT location x
	(*sprite)->cy = tim_data->cy;               // CLUT location y
	(*sprite)->rotate = ROT_ONE * 0;            // Rotation, ROT_ONE * (0 to 360)
	(*sprite)->mx = 0;                          // Rotation x coord
	(*sprite)->my = 0;                          // Rotation y coord
	(*sprite)->scalex = ONE * 1;				// Sprite scale (width)
	(*sprite)->scaley = ONE * 1;				// Sprite scale (height)

	// Clean up
	free3(rect);
	free3(crect);
	free3(tim_data);
}



void SetSpriteMiddle(GsSPRITE* sprite, int relative_x, int relative_y) {
	sprite -> mx = relative_x;
	sprite -> my = relative_y;
}


void setSpritePosition(GsSPRITE *sprited, int x, int y) {
	sprited -> x = x;
	sprited -> y = y;
}


void setSpriteBlendColor(GsSPRITE* sprite, Color* color) {
	sprite -> r = color->r;
	sprite -> g = color->g;
	sprite -> b = color->b;
}

void setSpriteBlecndColorRGB(GsSPRITE* sprite, int r, int g, int b) {
	sprite -> r = r;
	sprite -> g = g;
	sprite -> b = b;
}


void drawSprite(GsSPRITE *sprite) {
	CurrentBuffer = GsGetActiveBuff();
	GsSortSprite(sprite, &OrderingTable[CurrentBuffer], 0);
}

void RotateSprite(GsSPRITE *spritesf,int rotation){
spritesf->rotate += ROT_ONE * rotation;
}



























// Maximum number of objects
#define MAX_OBJECTS 100

// Object handler
GsDOBJ2	Object[MAX_OBJECTS];
int ObjectCount=0;

// Sunlight Direction and color
GsF_LIGHT sunLight[1];
VECTOR sunDirection;
Color sunColor;
Color ambientLightColor;

void SetSunColor (int r, int g, int  b) {
	sunColor.r = r;
	sunColor.g = g;
	sunColor.b = b;
}

void SetSunDirection (int x, int y, int z) {
	sunDirection.vx = x;
	sunDirection.vy = y;
	sunDirection.vz = z;
}

void SetAmbientLight (int r, int g, int b) {
	ambientLightColor.r = r;
	ambientLightColor.g = g;
	ambientLightColor.b = b;
	//ambient light is 0-4096 so math is required to
	//convert 0-4096 to the standard rgb range of 0-255
	//Note: ONE is the same as 4096
	GsSetAmbient(
		ambientLightColor.r * (ONE/255),
		ambientLightColor.g * (ONE/255),
		ambientLightColor.b * (ONE/255)
	);
}

void CalculateCamera() {

	// This function simply calculates the viewpoint matrix based on the camera coordinates...
	// It must be called on every frame before drawing any objects.

	VECTOR	vec;
	GsVIEW2 view;

	// Copy the camera (base) matrix for the viewpoint matrix
	view.view = Camera.coord2.coord;
	view.super = WORLD;

	//Find rotation matrix from a rotation angle.
	//input SVECTOR, output MATRIX
	RotMatrix(&Camera.rotation, &view.view);
	//Multiply a vector by a matrix.
	//Input MATRIX, input VECTOR, output VECTOR
	ApplyMatrixLV(&view.view, &Camera.position, &vec);
	//Set the amount of parallel transfer
	//Output MATRIX, input VECTOR
	TransMatrix(&view.view, &vec);

	// Set the viewpoint matrix to the GTE
	GsSetView2(&view);

	// Set the light source coordinates
	sunLight[0].vx = sunDirection.vx;
	sunLight[0].vy = -sunDirection.vy;
	sunLight[0].vz = sunDirection.vz;

	sunLight[0].r =	sunColor.r;	sunLight[0].g = sunColor.g;	sunLight[0].b = sunColor.b;
	GsSetFlatLight(0, &sunLight[0]);

}

void RenderObject(VECTOR pos, SVECTOR rot, GsDOBJ2 *obj) {

	MATRIX lmtx,omtx;
	GsCOORDINATE2 coord;

	// Copy the camera (base) matrix for the model
	coord = Camera.coord2;

	//Flip the Y axis so a positive value
	//is up, and a negative value is down
	pos.vy *= -1;

	// Rotate and translate the matrix according to the specified coordinates
	RotMatrix(&rot, &omtx);
	TransMatrix(&omtx, &pos);
	CompMatrixLV(&Camera.coord2.coord, &omtx, &coord.coord);
	coord.flg = 0;

	// Apply coordinate matrix to the object
	obj->coord2 = &coord;

	// Calculate Local-World (for lighting) and Local-Screen (for projection) matrices and set both to the GTE
	GsGetLws(obj->coord2, &lmtx, &omtx);
	GsSetLightMatrix(&lmtx);
	GsSetLsMatrix(&omtx);

	// Sort the object!
	GsSortObject4(obj, &OrderingTable[CurrentBuffer], 14-OT_LENGTH, getScratchAddr(0));

}


int LoadTMD(u_long *tmd, GsDOBJ2 *obj, int enableLighting) {

	/*	This function prepares the specified TMD model for drawing and then
		links it to a GsDOBJ2 structure so it can be drawn using GsSortObject4().

		By default, light source calculation is disabled but can be re-enabled by
		simply setting the attribute variable in your GsDOBJ2 structure to 0.

		Parameters:
			*tmd - Pointer to a TMD model file loaded in memory.
			*obj - Pointer to an empty GsDOBJ2 structure.

		Returns:
			Number of objects found inside the TMD file.

	*/

	u_long *dop;
	int i,NumObj;

	// Copy pointer to TMD file so that the original pointer won't get destroyed
	dop = tmd;

	// Skip header and then remap the addresses inside the TMD file
	dop++;
	GsMapModelingData(dop);

	// Get object count
	dop++;
	NumObj = *dop;

	// Link object handler with the specified TMD
	dop++;
	for(i=0; i<NumObj; i++) {
		GsLinkObject4((u_long)dop, &obj[i], i);
		//connect the WORLD coordinate directly
		//GsInitCoordinate2(WORLD,obj[i].coord2);
		if (enableLighting == 0) {
			obj[i].attribute = (1<<6);	// Disables light source calculation
		}
	}

	// Return the object count found inside the TMD
	return(NumObj);

}

void loadTexture(unsigned char imageData[]) {

	// Initialize image
	GsIMAGE* tim_data;
	RECT* rect;
	RECT* crect;
	tim_data = malloc3(sizeof(GsIMAGE));
	GsGetTimInfo ((u_long *)(imageData+4),tim_data);
	rect = malloc3(sizeof(RECT));
	crect = malloc3(sizeof(RECT));

	// Load the image into the GPU memory (frame buffer)
	rect->x = tim_data->px; // x position of image in frame buffer
	rect->y = tim_data->py; // y position of image in frame buffer
	rect->w = tim_data->pw; // width in frame buffer
	rect->h = tim_data->ph; // height in frame buffer
	printf("Framebuffer info {x=%d, y=%d, w=%d, h=%d}\n", rect->x, rect->y, rect->w, rect->h);
	LoadImage(rect, tim_data->pixel);

	// Load the color lookup table (CLUT) into the GPU memory (frame buffer)
	crect->x = tim_data->cx; // x position of CLUT in frame buffer
	crect->y = tim_data->cy; // y position of CLUT in frame buffer
	crect->w = tim_data->cw; // width of CLUT in frame buffer
	crect->h = tim_data->ch; // height of CLUT in frame buffer
	printf("CLUT info {x=%d, y=%d, w=%d, h=%d}\n", crect->x, crect->y, crect->w, crect->h);
	LoadImage(crect, tim_data->clut);

	// Clean up
	free3(rect);
	free3(crect);
	free3(tim_data);
}

VECTOR pos;
MATRIX tempMatrixPos;
VECTOR returnPos;
VECTOR Translate (SVECTOR rot, int x, int y, int z) {

	pos.vx = x;
	pos.vy = y;
	pos.vz = z;

    RotMatrix(&rot, &tempMatrixPos);

	ApplyMatrixLV(&tempMatrixPos, &pos, &returnPos);

	return returnPos;

}
