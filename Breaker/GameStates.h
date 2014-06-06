#ifndef INCLUDED_GAMESTATES_H
#define INCLUDED_GAMESTATES_H

enum class GameState
{
	Invalid,
	Frontend,
	LevelSelect,
	Gameplay,
	Score,
	Quit
};

#endif		//INCLUDED_GAMESTATES_H