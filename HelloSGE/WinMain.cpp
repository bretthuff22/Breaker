#include <SGE.h>
using namespace SGE;

SGE_Sprite player;
SVector2 position;
bool quit = false;

void SGE_Initialize()
{
	player.Load("Cyclops.png");
	position.x = 100.0f;
	position.y = 100.0f;
}

void SGE_Terminate()
{
	player.Unload();
}

bool SGE_Update(float deltaTime)
{
	const float kSpeed = 100.0f;
	if (Input_IsKeyDown(Keys::RIGHT))
	{
		position.x += kSpeed * deltaTime;
	}
	if (Input_IsKeyDown(Keys::LEFT))
	{
		position.x -= kSpeed * deltaTime;
	}

	if (Input_IsKeyDown(Keys::UP))
	{
		position.y -= kSpeed * deltaTime;
	}
	if (Input_IsKeyDown(Keys::DOWN))
	{
		position.y += kSpeed * deltaTime;
	}
	if (Input_IsKeyPressed(Keys::ESCAPE))
	{
		quit = true;
	}
	return quit;
}

void SGE_Render()
{
	player.SetPosition(position);
	player.Render();
}