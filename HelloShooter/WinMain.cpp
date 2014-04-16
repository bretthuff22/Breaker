#include <SGE.h>
using namespace SGE;

#include "Fighter.h"
#include "Enemy.h"
#include "Bullet.h"

const int kMaxBullets = 1000;
Bullet bullets[kMaxBullets];
int bulletIndex = 0;

const int kMaxEnemies = 100;
Enemy enemies[kMaxEnemies];
int enemyIndex = 0;

const int kMaxExplosions = 20;
SGE_Emitter explosions[kMaxExplosions];
int explosionIndex = 0;

Fighter fighter;

SGE_Sound bulletSound;
SGE_Sound explosionSound;

SGE_Sprite background;

float spawnDelay = 0.0f;

void FireBullets()
{
	if (Input_IsKeyPressed(Keys::SPACE))
	{
		const int index0 = bulletIndex;
		const int index1 = (bulletIndex + 1) % kMaxBullets;
		const int index2 = (bulletIndex + 2) % kMaxBullets;
		
		if (!bullets[index0].IsAlive() &&
			!bullets[index1].IsAlive() &&
			!bullets[index2].IsAlive())
		{
			SVector2 pos = fighter.GetPosition();
			SVector2 vel0(-100.0f, -500.0f);
			SVector2 vel1(0.0f, -500.0f);
			SVector2 vel2(100.0f, -500.0f);
			bullets[index0].Fire(pos, vel0);
			bullets[index1].Fire(pos, vel1);
			bullets[index2].Fire(pos, vel2);
			bulletIndex = (index2 + 1) % kMaxBullets;
			bulletSound.Play();
		}
	}
}

void SpawnEnemies(float deltaTime)
{
	spawnDelay -=  deltaTime;
	if (spawnDelay <= 0.0f)
	{
		if (!enemies[enemyIndex].IsAlive())
		{
			const int kWinWidth = IniFile_GetInt("WinWidth", 800);
			SVector2 spawnPos(RandomFloat(100.0f, kWinWidth -100.0f), -100.0f);
			enemies[enemyIndex].Spawn(spawnPos);
			enemyIndex = (enemyIndex + 1) % kMaxEnemies;
			spawnDelay = RandomFloat(0.2f, 1.0f);
		}

	}
}

void CheckCollision()
{
	for (int b = 0; b < kMaxBullets; ++b)
	{
		if (bullets[b].IsAlive())
		{
			for (int e = 0; e < kMaxEnemies; ++e)
			{
				if(enemies[e].IsAlive())
				{
					SCircle bulletCircle = bullets[b].GetBoundingCircle();
					SCircle enemyCircle = enemies[e].GetBoundingCircle();
					//const float xDiff = bulletCircle.center.x = enemyCircle.center.x;
					//const float yDiff = bulletCircle.center.y = enemyCircle.center.y;
					//const float distanceSqr = xDiff * xDiff + yDiff * yDiff; // expensive to find root
					//const float radii = bulletCircle.radius + enemyCircle.radius;
					//if (distanceSqr < radii*radii)
					if(Intersect(bulletCircle, enemyCircle))
					{
						enemies[e].Kill();
						bullets[b].Kill();

						explosions[explosionIndex].SetPosition(enemyCircle.center);
						explosions[explosionIndex].Start(100.0f, true);
						explosionIndex = (explosionIndex + 1) % kMaxExplosions;

						explosionSound.Play();
						break;
					}
				}
			}
		}
	}
}

void UpdateGameObjects(float deltaTime)
{
	fighter.Update(deltaTime);

	for (int i = 0; i < kMaxBullets; ++i)
	{
		bullets[i].Update(deltaTime);
	}

	for (int i = 0; i < kMaxEnemies; ++i)
	{
		enemies[i].Update(deltaTime);
	}

	for (int i = 0; i < kMaxExplosions; ++i)
	{
		explosions[i].Update(deltaTime);
	}
}


void SGE_Initialize()
{
	const int kWinWidth = IniFile_GetInt("WinWidth", 800);
	const int kWinHeight = IniFile_GetInt("WinHeight", 600);
	fighter.Load();
	fighter.SetPosition(SVector2(kWinWidth * 0.5f, kWinHeight - 200.0f));

	for (int i = 0; i < kMaxBullets; ++i)
	{
		bullets[i].Load();
	}

	for (int i = 0; i < kMaxEnemies; ++i)
	{
		enemies[i].Load();
	}

	for (int i = 0; i < kMaxExplosions; ++i)
	{
		explosions[i].Load("explosion.txt");
	}

	bulletSound.Load("photongun1.wav");
	explosionSound.Load("explosion.wav");
	background.Load("space.jpg");
}

void SGE_Terminate()
{
	fighter.Unload();
	for (int i = 0; i < kMaxBullets; ++i)
	{
		bullets[i].Unload();
	}
	for (int i = 0; i < kMaxEnemies; ++i)
	{
		enemies[i].Unload();
	}

	for (int i = 0; i < kMaxExplosions; ++i)
	{
		explosions[i].Unload();
	}

	bulletSound.Unload();
	explosionSound.Unload();
	background.Unload();
}

bool SGE_Update(float deltaTime)
{
	FireBullets();
	SpawnEnemies(deltaTime);
	CheckCollision();
	UpdateGameObjects(deltaTime);
	return Input_IsKeyPressed(Keys::ESCAPE);
}

void SGE_Render()
{
	background.Render();
	
	for (int i = 0; i < kMaxBullets; ++i)
	{
		bullets[i].Render();
	}

	for (int i = 0; i < kMaxEnemies; ++i)
	{
		enemies[i].Render();
	}

	fighter.Render();

	for (int i = 0; i < kMaxExplosions; ++i)
	{
		explosions[i].Render(true);
	}


}

