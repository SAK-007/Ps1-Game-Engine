#include "Engine/include/3D/ALL.H"
#define DEBUGGING 1

int isr = 0;
int isr2 = 0;

void Initialize();
void Start();
void Update();
void Render();
void Controls();

int CubeSpeed   = 30;
int MoveSpeed   = 60;
int RunSpeed    = 120;
int CameraSpeed = 30;

unsigned long* cdData[10];


Mesh Grid,OBJ,Cube,Grid2,Player;
int PhysicsSpeed = 90;


int main()
{

    Initialize();
    Start();


    while(1)
    {
        Update();
        Render();
    }

    return 0;
}


void Initialize()
{

    initializeMemory();

    initializeScreen();

    initializePad();


    cd_open();


    cd_read_file("CAR.TMD",  &cdData[0]);
    cd_read_file("GRID.TMD",  &cdData[1]);
    cd_read_file("OBJ.TMD",  &cdData[2]);
    cd_read_file("CRASH.TIM",  &cdData[3]);
    cd_read_file("PS1.TIM",  &cdData[4]);
    cd_read_file("GRID.TMD",  &cdData[5]);
    cd_read_file("PLAYER.TMD",  &cdData[6]);



    cd_close();

    loadTexture((u_char *)cdData[3]);
    loadTexture((u_char *)cdData[4]);


}


void Start()
{

    ObjectCount += LoadTMD(cdData[1], &Object[0], 1);
    ObjectCount += LoadTMD(cdData[0], &Object[1], 1);
    ObjectCount += LoadTMD(cdData[2], &Object[2], 1);
    ObjectCount += LoadTMD(cdData[5], &Object[3], 1);
    ObjectCount += LoadTMD(cdData[6], &Object[4], 1);

    Grid2.position.vx = 20400;

    Camera.position.vx = -6380;
    Camera.position.vy = 2500;
    Camera.position.vz = 5120;

    Camera.rotation.vx = 10;
    Camera.rotation.vy = -20;
    Camera.rotation.vz = 0;


    Cube.position.vx = 3500;
    Cube.position.vy = 1200;
    Cube.position.vz = -3500;

    Cube.rotation.vy = 900;


    OBJ.position.vx = 3500;
    OBJ.position.vy = 1200;
    OBJ.position.vz = 0;

    Player.position.vx = 6500;
    Player.position.vy = 1200;
    Player.position.vz = 0;

    Grid2.rotation.vz = -1020;
    Grid2.position.vy = 10230;
    Grid2.position.vx = 10230;




    Cube.rotation.vy = 900;


    SetBGColor(0,0,255);


    SetAmbientLight(67, 67, 67);


    SetSunColor(255, 255, 255);


    SetSunDirection(0, -1, 1);



}


void Update ()
{
#ifdef DEBUGGING
  FntPrint("%d %d %d",Player.position.vx,Player.position.vy,Player.position.vz);

    FntPrint("\nCamera position : %d %d %d",Camera.position.vx,Camera.position.vy,Camera.position.vz);
/*
    FntPrint("\n\nGrid rotation: %d",Grid2.rotation.vz);
    FntPrint("\n\nGrid position y: %d",getPositionY(Grid2));
    FntPrint("\n\nGrid position z: %d",getPositionZ(Grid2));
    FntPrint("\n\nGrid position x: %d",getPositionX(Grid2));
    */
#endif

    Cube.rotation.vx += 20;
    Cube.rotation.vy += 20;

    OBJ.rotation.vx += 20;
    OBJ.rotation.vy += 20;

    if(!isr){Cube.position.vy += 40;}
    if(isr){Cube.position.vy -= 40;}
    if(Cube.position.vy > 4500){isr = 1;}
    if(Cube.position.vy < 1501){isr = 0;}
    if(!isr2){OBJ.position.vy += 40;}
    if(isr2){OBJ.position.vy -= 40;}
    if(OBJ.position.vy > 4500){isr2 = 1;}
    if(OBJ.position.vy < 1501){isr2 = 0;}


    if(Player.position.vz > 11150){Player.position.vy -= PhysicsSpeed;}
    else{Player.position.vz += 40;}

    if(Camera.position.vz > 11400 ||
       Camera.position.vx > 11020 ||
       Camera.position.vz < -10840
       ){
            Camera.position.vy -= PhysicsSpeed;
    }

    if(Camera.position.vy < -35000)
    {
      Camera.position.vx = -6380;
      Camera.position.vy = 2500;
      Camera.position.vz = 5120;
    }


    padUpdate();


    Controls();

}


void Render ()
{

    clearDisplay();

    CalculateCamera();


    RenderObject(Grid.position, Grid.rotation, &Object[0]);
    RenderObject(Grid2.position,Grid2.rotation,&Object[3]);
    RenderObject(Cube.position, Cube.rotation, &Object[1]);
    RenderObject(OBJ.position, OBJ.rotation,   &Object[2]);
    RenderObject(Player.position,Player.rotation,&Object[4]);


    display();

}


void Controls ()
{
    padUpdate();


    if(padCheck(Pad1Up))
    {
        if(padCheck(Pad1L1)){ Camera.position.vz -= RunSpeed;}
        else {Camera.position.vz -= MoveSpeed;}
    }

    if(padCheck(Pad1Down))
    {
        if(padCheck(Pad1L1)){ Camera.position.vz += RunSpeed;}
        else {Camera.position.vz += MoveSpeed;}
    }

    if(padCheck(Pad1Left))
    {
        if(padCheck(Pad1L1)){ Camera.position.vx += RunSpeed;}
        else {Camera.position.vx += MoveSpeed;}
    }

    if(padCheck(Pad1Right)&& Camera.position.vx > -8800)
    {
        if(padCheck(Pad1L1)){ Camera.position.vx -= RunSpeed;}
        else {Camera.position.vx -= MoveSpeed;}
    }





    if(padCheck(Pad1Cross) && Camera.rotation.vx < 1000)
    {
        Camera.rotation.vx += CameraSpeed;
    }

    if(padCheck(Pad1Triangle)&& Camera.rotation.vx > -1000)
    {
        Camera.rotation.vx -= CameraSpeed;
    }

    if(padCheck(Pad1Square))
    {
        Camera.rotation.vy += CameraSpeed;
    }

    if(padCheck(Pad1Circle))
    {
        Camera.rotation.vy -= CameraSpeed;
    }


}

