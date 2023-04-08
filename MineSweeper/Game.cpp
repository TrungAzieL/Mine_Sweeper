#include "Game.hpp"

#include "TextManager.hpp"
#include "TextureManager.hpp"
#include "Map.hpp"
#include "Object.hpp"
#include "EventsHandler.hpp"

#include <string>

EventsHandler eventsHandler;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

SDL_Rect navRect;

extern Object tools, target;

extern Object flags[GAME_SIZE_HEIGHT][GAME_SIZE_WIDTH];
extern Object dynamine[GAME_SIZE_HEIGHT][GAME_SIZE_WIDTH];

extern Text cntMines[GAME_SIZE_HEIGHT][GAME_SIZE_WIDTH];

extern int mouseX, mouseY, graphX, graphY;
extern int flagsLeft;

extern Map graph;

extern Text endingText;

Text navText[2];
Object navTools[3];
Object endingLayer;

SDL_Color Game::COLOR[8] = { { 0, 0, 255 }, { 0, 255, 0 } , { 255, 0, 0 } , { 0, 0, 179 } , { 126, 0, 1 } , {0, 127, 126}, {0, 0, 0}, {128, 128, 128} };

bool Game::isRunning = false;
bool Game::isPausing = false;

Game::Game() {

}

Game::~Game() {

}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
	int flags = 0;

	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);

		isRunning = true;
	}
	if (TTF_Init() < 0)
	{
		SDL_Log("%s", TTF_GetError());
	}

	navRect.x = 0;
	navRect.y = 0;
	navRect.w = 32 * GAME_SIZE_WIDTH;
	navRect.h = 50;

	tools.Init("assets/tools.png", 0, 0, 0, 0);
	target.Init("assets/target.png", 0, 0, 0, 0);

	navText[0].Init(":" + to_string(flagsLeft), 64, 32, 40, 9, { 255, 0, 0 });
	navText[1].Init("D:   F:", 100, 32, 32 * GAME_SIZE_WIDTH - 150, 9, { 255, 0, 0 });

	navTools[0].Init("assets/shovel.png", 32, 32, 32 * GAME_SIZE_WIDTH - 120, 9);
	navTools[1].Init("assets/flag.png", 32, 32, 32 * GAME_SIZE_WIDTH - 50, 9);
	navTools[2].Init("assets/flag.png", 32, 32, 10, 9);

	endingLayer.Init("assets/layer.png", GAME_SIZE_WIDTH * 32, GAME_SIZE_HEIGHT * 32 * 50, 0, 0);
}


void Game::handleEvents() {
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			isRunning = false;
			break;

		case SDL_KEYDOWN:
			eventsHandler.handleKeyPress();
			break;

		case SDL_MOUSEMOTION:
			eventsHandler.handleMouseMotion();
			break;

		case SDL_MOUSEBUTTONDOWN:
			eventsHandler.handleMouseClick();
			break;
		}
	}
}

void Game::update() {
	for (int i = 0; i < GAME_SIZE_HEIGHT; ++i) {
		for (int j = 0; j < GAME_SIZE_WIDTH; ++j) {
			if (graph.getMapState(i, j) == 0) // have not dig
				continue;
			if (graph.hasFlag[i][j]) {
				flagsLeft++;
				graph.hasFlag[i][j] = 0;
			}
		}
	}

	if (flagsLeft >= 10)
		navText[0].Init(":" + to_string(flagsLeft), 64, 32, 40, 9, { 255, 0, 0 });
	else
		navText[0].Init(":" + to_string(flagsLeft), 32, 32, 40, 9, { 255, 0, 0 });
	//enddingText.Init("You Win!", 300, 64, GAME_SIZE_WIDTH * 16 - 150, GAME_SIZE_HEIGHT * 16 - 32, { 255, 0, 0 });
}

void Game::render() {
	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, 178, 194, 190, 255);
	SDL_RenderFillRect(renderer, &navRect);

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	graph.Draw();

	for (int i = 0; i < GAME_SIZE_HEIGHT; ++i) {
		for (int j = 0; j < GAME_SIZE_WIDTH; ++j) {
			if (graph.getMapState(i, j) == 0) { // have not dig
				flags[i][j].Render();
				continue;
			}
			cntMines[i][j].Render();
			dynamine[i][j].Render();
		}
	}

	target.Render();
	tools.Render();
	navText[0].Render();
	navText[1].Render();

	navTools[0].Render();
	navTools[1].Render();
	navTools[2].Render();

	if (pausing()) endingLayer.Render(120);
	endingText.Render();

	SDL_RenderPresent(renderer);
}

void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);

	TTF_Quit();
	SDL_Quit();
}
