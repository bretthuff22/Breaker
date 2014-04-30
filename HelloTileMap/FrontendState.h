#ifndef INCLUDED_FrontendSTATE_H
#define INCLUDED_FrontendSTATE_H

#include <SGE.h>
using namespace SGE;

#include "AppState.h"

class FrontendState : public AppState
{
public: 
	FrontendState(GameContext& gc);
	virtual ~FrontendState();

	virtual void Load();
	virtual void Unload();
	virtual GameState Update(float deltaTime);
	virtual void Render();

private:
	SGE_Font mFont;
	SGE_Cursor mCursor;
	SGE_Button mStartButton;
	SGE_Button mStartButton2;
	
};

#endif // #ifndef INCLUDED_FrontendState_H