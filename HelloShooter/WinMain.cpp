#include <SGE.h>
using namespace SGE;

#include "Fighter.h"

Fighter fighter;
bool quit = false;

void SGE_Initialize()
{
	fighter.Load();
}

void SGE_Terminate()
{
	fighter.Unload();
}

bool SGE_Update(float deltaTime)
{
	fighter.Update(deltaTime);

	if (Input_IsKeyPressed(Keys::ESCAPE))
	{
		quit = true;
	}
	return quit;
}

void SGE_Render()
{
	fighter.Render();
}