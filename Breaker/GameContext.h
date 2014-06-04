#ifndef INCLUDED_GAMECONTEXT_H
#define INCLUDED_GAMECONTEXT_H

class GameContext
{
public:
	GameContext();
	~GameContext();

	void SetLevel(int level)	{mLevel = level;}
	int GetLevel() const		{return mLevel;}

	void SetScore(int score)	{mScore = score;}
	int GetScore()				{return mScore;}

private:
	int mLevel;
	int mScore;
};

#endif	//	INCLUDED_GAMECONTEXT_H