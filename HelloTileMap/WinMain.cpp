#include <SGE.h>
using namespace SGE;

#include "Map.h"

Map map;

void SGE_Initialize()
{
	map.Load("level01.txt", "texturepack01.txt");
}

void SGE_Terminate()
{
	map.Unload();
}

bool SGE_Update(float deltaTime)
{
	map.Update(deltaTime);
	return Input_IsKeyPressed(Keys::ESCAPE);
}

void SGE_Render()
{
	map.Render();
}

