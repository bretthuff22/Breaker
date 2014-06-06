#ifndef INCLUDED_LevelSelectSTATE_H
#define INCLUDED_LevelSelectSTATE_H

#include <SGE.h>
using namespace SGE;

#include "AppState.h"

class LevelSelectState : public AppState
{
public: 
	LevelSelectState(GameContext& gc);
	virtual ~LevelSelectState();

	virtual void Load();
	virtual void Unload();
	virtual GameState Update(float deltaTime);
	virtual void Render();

private:

	SGE_Sprite mBackground;
	SGE_Cursor mCursor;
	SGE_Button mLevel01;
	SGE_Button mLevel02;
	SGE_Button mLevel03;
	SGE_Button mLevel04;
	SGE_Button mLevel05;
	SGE_Button mLevel06;
	SGE_Button mLevel07;
	SGE_Button mLevel08;
	SGE_Button mLevel09;
	SGE_Button mLevel10;

	SGE_Sound mClick;
	
	
};

#endif // #ifndef INCLUDED_LevelSelectState_H