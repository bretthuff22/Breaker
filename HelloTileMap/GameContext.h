#ifndef INCLUDED_GAMECONTEXT_H
#define INCLUDED_GAMECONTEXT_H

class GameContext
{
public:
	GameContext();
	~GameContext();

	void SetLevel(int level)	{mLevel = level;}
	int GetLevel() const		{return mLevel;}

private:
	int mLevel;
};

#endif	//	INCLUDED_GAMECONTEXT_H