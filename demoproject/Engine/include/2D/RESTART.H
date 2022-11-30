/*
*
*  Audio.H
*
*  Author:SAK-007
*
*  Contains:Restarts the console
*
*  Thanks to Shadow
*
*/

void RestartConsole()
{
	((void (*)())0xBFC00000)();
}

void ResetConsole()
{
	((void (*)())0xBFC00000)();
}

void Restart()
{
	((void (*)())0xBFC00000)();
}

void Reboot()
{
	((void (*)())0xBFC00000)();
}