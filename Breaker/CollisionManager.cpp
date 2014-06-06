#include "CollisionManager.h"
#include "Ball.h"
#include "Paddle.h"
#include "Tile.h"


CollisionManager& CollisionManager::Get()
{
	static CollisionManager sInstance;
	return sInstance;
}

void CollisionManager::Register(Collider *coll)
{
	mColliders.push_back(coll);
}

void CollisionManager::UnRegister(Collider *coll)
{
	for (std::vector<Collider*>::iterator it = mColliders.begin(); it != mColliders.end(); ++it)
	{
		Collider* collider = *it;
		if (collider == coll)
		{
			if (collider->GetShape() == Collider::brick)
			{
				collider->SetSpriteType(0);
				boomSound.Play();
				mExplosions[mExplosionIndex].SetPosition(collider->GetPosition() + SVector2(48.0f, 0.0f));
				mExplosions[mExplosionIndex].Start(100.0f, true);
				mExplosionIndex = (mExplosionIndex + 1) % 20;
			}
			mColliders.erase(it);
			return;
		}
	}
}

void CollisionManager::Load(const Map& map)
{
	//TILES
	Tile* tiles = map.GetTiles();

	const int size = map.GetHeight() * map.GetWidth()/(map.GetTileSize()*map.GetTileSize());

	for (int i = 0; i < size; ++i)
	{
		// Add tiles to mColliders
		if (!tiles[i].IsWalkable())
		{
			mColliders.push_back(&tiles[i]);
		}
	}

	//BRICKS
	Brick* bricks = map.GetBricks();

	const int brickSize = map.GetBrickHeight() * map.GetBrickWidth()/(map.GetBrickSize());

	for (int i = 0; i < brickSize; ++i)
	{
		// Add tiles to mColliders
		if (!bricks[i].IsWalkable())
		{
			mColliders.push_back(&bricks[i]);
		}
	}

	for (std::vector<Collider*>::iterator it = mColliders.begin(); it != mColliders.end(); ++it)
	{
		Collider* load = *it;
		load->Load();
	}

	//Sound
	blipSound.Load("blip.wav");
	boomSound.Load("boom.wav");
	clinkSound.Load("clink.wav");


	//Explosions
	for (int i = 0; i <  20; ++i)
	{
		mExplosions[i].Load("explosion.txt");
	}
}

void CollisionManager::Unload()
{
	int i = mColliders.size();
	for (std::vector<Collider*>::iterator it = mColliders.begin(); it != mColliders.end(); ++it)
	{
		Collider* unload = *it;
		//UnRegister(unload);
		unload->Unload();
	}

	//Sound
	blipSound.Unload();
	boomSound.Unload();
	clinkSound.Unload();

	//Explosions
	for (int i = 0; i < 20; ++i)
	{
		mExplosions[i].Unload();
	}
}

	
int CollisionManager::Update(float deltaTime, const Map& map)
{
	std::vector<Collider*> balls;
	int score = 0;

	for (std::vector<Collider*>::iterator it = mColliders.begin(); it != mColliders.end(); ++it)
	{
		Collider* temp = *it;
		if (temp->GetShape() == Collider::Shape::circle)
		{
			balls.push_back(temp);
		}

		if (temp->GetShape() == Collider::Shape::paddle)
		{
			const float kSpeed = 800.0f;

			//Widen
			if (mPaddleWiden)
			{
				temp->Widen();
				mPaddleWiden = false;
			}
			if (mPaddleShorten)
			{
				temp->Shorten();
				mPaddleShorten = false;
			}

			//Check horizontal movement
			if (Input_IsKeyDown(Keys::RIGHT))
			{
				temp->SetPosition(SVector2(temp->GetPosition().x + kSpeed * deltaTime, temp->GetPosition().y));
				const int kWinWidth = IniFile_GetInt("WinWidth", 800);
				// Right collision
				if (temp->GetPosition().x > kWinWidth - 32)
				{
					temp->SetPosition(SVector2(kWinWidth - 32, temp->GetPosition().y));
				}
			}
			else if (Input_IsKeyDown(Keys::LEFT))
			{
				temp->SetPosition(SVector2(temp->GetPosition().x - kSpeed * deltaTime, temp->GetPosition().y));
				// Left collision
				if (temp->GetPosition().x < 32)
				{
					temp->SetPosition(SVector2(32, temp->GetPosition().y));
				}
			}
		}
	}

	//std::vector<Collider*> ballsMoved;

	for (std::vector<Collider*>::iterator it = balls.begin(); it != balls.end(); ++it)
	{
		Collider* ball = *it;
		
		if (ball->GetVelocity().x != 0 && ball->GetVelocity().y != 0)
		{
			ball->CreateBoundingBox();
			SRect bb = ball->GetBoundingBox();
			SRect newbb = bb + SVector2(ball->GetVelocity().x * deltaTime, 0.0f);
			//for (std::vector<Collider*>::iterator itOther = mColliders.begin(); itOther != mColliders.end(); ++itOther)
			for (int i = 0; i < mColliders.size(); ++i)
			{
				Collider* other = mColliders[i];

				if (other->GetShape() == Collider::box || other->GetShape() == Collider::brick)
				{
					// Check left/right collision
					newbb = bb + SVector2(ball->GetVelocity().x*deltaTime, 0.0f);

					// Right collision
					if (other->GetBoundingBox().min.x < newbb.max.x 
						&& other->GetBoundingBox().max.x > newbb.min.x 
						&& (	( other->GetBoundingBox().min.y < newbb.min.y && other->GetBoundingBox().max.y > newbb.min.y ) 
							||	( other->GetBoundingBox().min.y < newbb.max.y && other->GetBoundingBox().max.y > newbb.max.y ) ) )
					{
						//ball->SetPosition(SVector2(ball->GetPosition().x + (int)(other->GetBoundingBox().min.x - bb.max.x) - 1.0f, ball->GetPosition().y));
						ball->SetVelocity(SVector2(ball->GetVelocity().x * -1, ball->GetVelocity().y));

						blipSound.Play();

						// DESTROY IF BRICK
						if (other->GetShape() == Collider::brick)
						{
							if (other->GetType() != Collider::METAL)
							{
								BrickCollision(other, ball);
								
								if (other->GetHits() == 0)
								{
									score += other->GetValue();
									UnRegister(other);
									i--;
								}
							}
							else
							{
								clinkSound.Play();
							}
						}
					}
					// Left collision
					else if (other->GetBoundingBox().max.x > newbb.min.x 
							&& other->GetBoundingBox().min.x < newbb.max.x 
							&& (	( other->GetBoundingBox().min.y < newbb.min.y && other->GetBoundingBox().max.y > newbb.min.y ) 
							||		( other->GetBoundingBox().min.y < newbb.max.y && other->GetBoundingBox().max.y > newbb.max.y ) ) )
					{
						//ball->SetPosition(SVector2(ball->GetPosition().x + (int)(other->GetBoundingBox().max.x - bb.min.x) + 1.0f, ball->GetPosition().y));
						ball->SetVelocity(SVector2(ball->GetVelocity().x * -1, ball->GetVelocity().y));

						blipSound.Play();
						
						// DESTROY IF BRICK
						if (other->GetShape() == Collider::brick)
						{
							if (other->GetType() != Collider::METAL)
							{
								BrickCollision(other, ball);
								
								if (other->GetHits() == 0)
								{
									score += other->GetValue();
									UnRegister(other);
									i--;
								}
							}
							else
							{
								clinkSound.Play();
							}
						}
					}
					
	
					// Check top/bottom intersection
					newbb =  bb + SVector2(0.0f, ball->GetVelocity().y*deltaTime);

					// Bottom collision
					if(other->GetBoundingBox().min.y < newbb.max.y
						&& other->GetBoundingBox().max.y > newbb.max.y
						&& (	( other->GetBoundingBox().min.x < newbb.min.x && other->GetBoundingBox().max.x > newbb.min.x ) 
							||	( other->GetBoundingBox().min.x < newbb.max.x && other->GetBoundingBox().max.x > newbb.max.x ) ) )
					{
						//ball->SetPosition(SVector2(ball->GetPosition().x, ball->GetPosition().y - (int)(other->GetBoundingBox().min.y - bb.max.y - 1.0f)));
						ball->SetVelocity(SVector2(ball->GetVelocity().x, ball->GetVelocity().y * -1));

						blipSound.Play();
						
						// DESTROY IF BRICK
						if (other->GetShape() == Collider::brick)
						{
							if (other->GetType() != Collider::METAL)
							{
								BrickCollision(other, ball);
								
								if (other->GetHits() == 0)
								{
									score += other->GetValue();
									UnRegister(other);
									i--;
								}
							}
							else
							{
								clinkSound.Play();
							}
						}
					}

					// Top collision
					else if(other->GetBoundingBox().max.y > newbb.min.y
							&& other->GetBoundingBox().max.y < newbb.max.y
							&& (	( other->GetBoundingBox().min.x < newbb.min.x && other->GetBoundingBox().max.x > newbb.min.x ) 
								||	( other->GetBoundingBox().min.x < newbb.max.x && other->GetBoundingBox().max.x > newbb.max.x ) ) )
					{
						//ball->SetPosition(SVector2(ball->GetPosition().x, ball->GetPosition().y - (int)(other->GetBoundingBox().max.y - bb.min.y - 1.0f)));
						ball->SetVelocity(SVector2(ball->GetVelocity().x, ball->GetVelocity().y * -1));

						blipSound.Play();
						
						// DESTROY IF BRICK
						if (other->GetShape() == Collider::brick)
						{
							if (other->GetType() != Collider::METAL)
							{
								BrickCollision(other, ball);
								
								if (other->GetHits() == 0)
								{
									score += other->GetValue();
									UnRegister(other);
									i--;
								}
							}
							else
							{
								clinkSound.Play();
							}
						}
					}
					
				}
				else if (other->GetShape() == Collider::paddle)
				{
					// Check bottom intersection
					newbb =  bb + SVector2(0.0f, ball->GetVelocity().y*deltaTime);
					other->CreateBoundingBox();

					// Bottom collision
					if(other->GetBoundingBox().min.y < newbb.max.y
						&& other->GetBoundingBox().max.y > newbb.max.y
						&& (	( other->GetBoundingBox().min.x < newbb.min.x && other->GetBoundingBox().max.x > newbb.min.x ) 
							||	( other->GetBoundingBox().min.x < newbb.max.x && other->GetBoundingBox().max.x > newbb.max.x ) ) )
					{
						//ball->SetPosition(SVector2(ball->GetPosition().x, ball->GetPosition().y - (int)(other->GetBoundingBox().min.y - bb.max.y - 1.0f)));
						float paddleCenter = other->GetPosition().x;
						float ballCenter = ball->GetPosition().x;
						float ballDistFromCenter = ballCenter - paddleCenter;
						float ballQuadrant = ballDistFromCenter/(other->GetBoundingBox().GetWidth()/2.0f);

						float magnitude = ball->GetVelocity().Length();

						if (abs(ballQuadrant) < 0.25f)
						{
							ball->SetVelocity(SVector2(5.0f*magnitude/13.0f, -12.0f*magnitude/13.0f));
						}
						else if (abs(ballQuadrant) < 0.50f)
						{
							ball->SetVelocity(SVector2(3.0f*magnitude/5.0f, -4.0f*magnitude/5.0f));
						}
						else if (abs(ballQuadrant) < 0.90f)
						{
							ball->SetVelocity(SVector2(4.0f*magnitude/5.0f, -3.0f*magnitude/5.0f));
						}
						else
						{
							ball->SetVelocity(SVector2(12.0f*magnitude/13.0f, -5.0f*magnitude/13.0f));
						}

						if (ballQuadrant < 0.0f)
						{
							ball->SetVelocity(SVector2(ball->GetVelocity().x * -1, ball->GetVelocity().y));
						}
						
						blipSound.Play();
					}
				}
			}

			ball->SetPosition(SVector2(ball->GetPosition().x + (int)ball->GetVelocity().x * deltaTime, ball->GetPosition().y + (int)ball->GetVelocity().y * deltaTime ));
		}

		ball->Update(deltaTime);

		// DELETE BALL IF IT IS OFF THE SCREEN
		const int kWinHeight = IniFile_GetInt("WinHeight", 600);

		if (ball->GetPosition().y > kWinHeight + ball->GetPosition().x + (int)ball->GetVelocity().x * deltaTime, ball->GetPosition().y + (int)ball->GetVelocity().y * deltaTime)		// erasing ball if not mBall (would have been reset already)
		{
			for (int i = 0; i < mColliders.size(); ++i)
			{
				Collider* ballFound = mColliders[i];
				if (ballFound == ball)
				{
					ball->SetVelocity(SVector2(0.0f, 0.0f));
					UnRegister(ballFound);
				}
				break;
			}
		}
	}
	

	// Explosions
	for (int i = 0; i < 20; ++i)
	{
		mExplosions[i].Update(deltaTime);
	}

	return score;
}

void CollisionManager::Render(const SVector2& offset)
{
	// RENDER NON BRICKS
	for (std::vector<Collider*>::iterator it = mColliders.begin(); it != mColliders.end(); ++it)
	{
		Collider* collider = *it;
		if (collider->GetShape() != Collider::brick)
		{
			collider->Render(offset);
		}
		//delete collider;
	}


	// Explosions
	for (int i = 0; i < 20; ++i)
	{
		mExplosions[i].Render(true);
	}
}

void CollisionManager::BrickCollision(Collider* brick, Collider* ball)
{
	if (brick->GetType() == Collider::WIDEN)
	{
		mPaddleWiden = true;
	}
	if (brick->GetType() == Collider::SHORT)
	{
		mPaddleShorten = true;
	}
	if (brick->GetType() == Collider::PLUS)
	{
		ball->ChangeSpeed(1.5f);
	}
	if (brick->GetType() == Collider::MINUS)
	{
		ball->ChangeSpeed(0.75f);
	}
	if (brick->GetType() == Collider::BOMB)
	{
		Ball* ball1 = new Ball();
		Ball* ball2 = new Ball();
		Ball* ball3 = new Ball();
		ball1->SetPosition(SVector2(brick->GetPosition().x - 25.0f, brick->GetPosition().y));
		ball2->SetPosition(SVector2(brick->GetPosition().x, brick->GetPosition().y));
		ball3->SetPosition(SVector2(brick->GetPosition().x + 25.0f, brick->GetPosition().y));
		ball1->Load();
		ball2->Load();
		ball3->Load();
		ball1->SetAlive(true);
		ball2->SetAlive(true);
		ball3->SetAlive(true);
		ball1->SetRandomVelocity();
		ball2->SetRandomVelocity();
		ball3->SetRandomVelocity();
		Register(ball1);
		Register(ball2);
		Register(ball3);
	}
	if (brick->GetType() == Collider::TRIHIT)
	{
		if (brick->GetSpriteType() == 6 || brick->GetSpriteType() == 7)
		{
			brick->SetSpriteType(brick->GetSpriteType() + 1);
		}
	}
	brick->DecreaseHits();
}

/*SRect CollisionManager::GetBoundingBoxFromSegment(const SLineSegment& line) const
{
	// Validate the line segment
	if (line.from.x < 0.0f || line.from.x > GetWidth() ||
		line.from.y < 0.0f || line.from.y > GetHeight() ||
		line.to.x < 0.0f || line.to.x > GetWidth() ||
		line.to.y < 0.0f || line.to.y > GetHeight())
	{
		// Line segment is out of bounds
		return SRect();
	}

	// Convert position to indices
	const int fromX = (int)line.from.x / mTileSize;
	const int fromY = (int)line.from.y / mTileSize;
	const int toX = (int)line.to.x / mTileSize;
	const int toY = (int)line.to.y / mTileSize;

	// Calculate tile count
	const int countX = toX - fromX + 1;
	const int countY =  toY - fromY + 1;

	// Get region
	SRect region;
	for (int y = 0; y < countY; ++y)
	{
		for (int x = 0; x < countX; ++x)
		{
			const int index = (fromX + x) + ((fromY + y) * mColumns);
			if (!mTiles[index].IsWalkable())
			{
				region += mTiles[index].GetBoundingBox();
			}
		}
	}
	return region;
}*/