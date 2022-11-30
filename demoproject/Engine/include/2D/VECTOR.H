/*
*
*  VECTOR.H
*
*  Author:SAK-007
*
*  Contains:All complex data types for Playstation Games
*
*
*/

typedef struct{
	float x;
	float y;
}Vector2f;

typedef struct{
	float x;
	float y;
	float z;
}Vector3f;

typedef struct{
	float x1;
	float y1;
	float x2;
	float y2;
}Vector4f;


typedef struct{
	int x;
	int y;
}Vector2i;

typedef struct{
	int x;
	int y;
	int z;
}Vector3i;

typedef struct{
	int x1;
	int y1;
	int x2;
	int y2;
}Vector4i;



Vector2f createVector2f(float x,float y)
{
	Vector2f vector2f = {.x = x, .y = y};
	return vector2f;
}


Vector3f createVector3f(float x,float y,float z)
{
	Vector3f vector3f = {.x = x, .y = y, .z = z};
	return vector3f;
}


Vector4f createVector4f(float x1,float y1,float x2,float y2)
{
	Vector4f vector4f = {.x1 = x1,.y1 = y1,.x2 = x2,.y2 = y2};
	return vector4f;
}



Vector2i createVector2i(int x,int y)
{
	Vector2i vector2f = {.x = x, .y = y};
	return vector2f;
}


Vector3i createVector3i(int x,int y,int z)
{
	Vector3i vector3f = {.x = x, .y = y, .z = z};
	return vector3f;
}


Vector4i createVector4i(int x1,int y1,int x2,int y2)
{
	Vector4i vector4f = {.x1 = x1,.y1 = y1,.x2 = x2,.y2 = y2};
	return vector4f;
}