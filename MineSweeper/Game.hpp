#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

#include <iostream>

#define GAME_SIZE_HEIGHT 16
#define GAME_SIZE_WIDTH 30
#define GAME_MINES 99

using namespace std;

class Game {
public:
	Game();
	~Game();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	void handleEvents();
	void update();
	void render();
	void clean();

	bool running() {
		return isRunning;
	}


	bool pausing() {
		return isPausing;
	}

	static SDL_Renderer* renderer;
	static SDL_Event event;

	static bool isRunning;
	static bool isPausing;

	static SDL_Color COLOR[];

private:
	SDL_Window* window;
};