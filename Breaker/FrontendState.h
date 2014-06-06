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
	SGE_Sprite mBackground;
	SGE_Cursor mCursor;
	SGE_Button mStartButton;
	SGE_Sound mClick;
	
};

#endif // #ifndef INCLUDED_FrontendState_H