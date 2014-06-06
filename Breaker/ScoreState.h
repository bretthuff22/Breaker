#ifndef INCLUDED_ScoreSTATE_H
#define INCLUDED_ScoreSTATE_H

#include <SGE.h>
using namespace SGE;

#include "AppState.h"

class ScoreState : public AppState
{
public: 
	ScoreState(GameContext& gc);
	virtual ~ScoreState();

	virtual void Load();
	virtual void Unload();
	virtual GameState Update(float deltaTime);
	virtual void Render();

private:
	SGE_Sprite mBackground;
	SGE_Font mScoreFont;
	SGE_Cursor mCursor;
	SGE_Button mStartButton;
	SGE_Sound mClick;
	
};

#endif // #ifndef INCLUDED_ScoreState_H