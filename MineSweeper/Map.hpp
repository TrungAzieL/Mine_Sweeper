#pragma once
#include "SDL.h"

class Map {
public:
	bool map[GAME_SIZE_HEIGHT][GAME_SIZE_WIDTH] = { 0 };

	int mine[GAME_SIZE_HEIGHT][GAME_SIZE_WIDTH] = { 0 };

	bool hasFlag[GAME_SIZE_HEIGHT][GAME_SIZE_WIDTH] = { 0 };

	void Draw();
	void RandomMine(int x, int y);
	void ChangeState(int x, int y);

	bool isGenerated = false;
	bool generated() {
		return isGenerated;
	}

	const int tilesTotal = GAME_SIZE_HEIGHT * GAME_SIZE_WIDTH, minesTotal = GAME_MINES;
	int tilesLeft = tilesTotal;


	int getMineCnt(int x, int y);
	bool getMapState(int x, int y);

private:
	SDL_Rect srcRect, destRect;
};