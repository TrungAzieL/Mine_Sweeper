#include "EventsHandler.hpp"
#include "Game.hpp"
#include "Object.hpp"
#include "TextManager.hpp"
#include "Map.hpp"

#include <string>

Object tools, target;

Object flags[GAME_SIZE_HEIGHT][GAME_SIZE_WIDTH];
Object dynamine[GAME_SIZE_HEIGHT][GAME_SIZE_WIDTH];

Text cntMines[GAME_SIZE_HEIGHT][GAME_SIZE_WIDTH];
int mouseX, mouseY, graphX, graphY;

Map graph;

Text endingText;

int flagsLeft = GAME_MINES;


void EventsHandler::handleKeyPress() {
	if (Game::event.key.keysym.sym == SDLK_ESCAPE) {
		Game::isRunning = false;
	}
	else if (Game::event.key.keysym.sym == SDLK_d) {
		tools.srcRect.x = 32;
		tools.destRect.y = 32 * graphX + 50 + 16;
		tools.destRect.x = 32 * graphY - 16;
	}
	else if (Game::event.key.keysym.sym == SDLK_f) {
		tools.srcRect.x = 0;
		tools.destRect.y = 32 * graphX + 50;
		tools.destRect.x = 32 * graphY;
	}
}

void EventsHandler::handleMouseMotion() {
	SDL_GetMouseState(&mouseX, &mouseY);

	if (mouseY >= 50) {
		graphY = mouseX / 32;
		graphX = (mouseY - 50) / 32;

		target.changePos(32, 32, 32 * graphY, 32 * graphX + 50);

		tools.changePos(32, 32, 32 * graphY - (tools.srcRect.x / 2), 32 * graphX + 50 + (tools.srcRect.x / 2));
	}
	else {
		tools.srcRect.w = tools.srcRect.h = 0;
		target.srcRect.w = target.srcRect.h = 0;
	}
}

void EventsHandler::handleMouseClick() {
	if (Game::isPausing) return;
	
	SDL_GetMouseState(&mouseX, &mouseY);
	if (mouseY >= 50) {
		graphY = mouseX / 32;
		graphX = (mouseY - 50) / 32;


		if (tools.getObjState() == 0) {
			if (graph.getMapState(graphX, graphY) == 0) {
				if (!graph.hasFlag[graphX][graphY]) {
					if (flagsLeft > 0) {
						flags[graphX][graphY].Init("assets/flag.png", 32, 32, 32 * graphY, 32 * graphX + 50);
						flagsLeft--;
						graph.hasFlag[graphX][graphY] = true;

						// WIN
					}
				}
				else {
					flags[graphX][graphY].changePos(0, 0, 0, 0);
					flagsLeft++;
					graph.hasFlag[graphX][graphY] = false;
				}
			}
		}
		else {

			if (!graph.generated()) {
				graph.RandomMine(graphX, graphY);
				for (int i = 0; i < GAME_SIZE_HEIGHT; ++i) {
					for (int j = 0; j < GAME_SIZE_WIDTH; ++j) {
						int mineCnt = graph.getMineCnt(i, j);
						if (mineCnt == -1)
							dynamine[i][j].Init("assets/mine.png", 32, 32, 32 * j, 32 * i + 50);
						else if (mineCnt > 0)
							cntMines[i][j].Init(to_string(mineCnt), 20, 32, j * 32 + 6, i * 32 + 52, Game::COLOR[mineCnt - 1]);
					}
				}
			}

			// LOSE
			if (graph.getMineCnt(graphX, graphY) == -1) {
				Game::isPausing = true;
				endingText.Init("You Lose!", 316, 64, GAME_SIZE_WIDTH * 16 - 158, GAME_SIZE_HEIGHT * 16 - 32, { 255, 0, 0 });
			}
			graph.ChangeState(graphX, graphY);
		}

		//WIN
		if (graph.tilesLeft == GAME_MINES && flagsLeft == 0) {
			Game::isPausing = true;
			endingText.Init("You Win!", 300, 64, GAME_SIZE_WIDTH * 16 - 150, GAME_SIZE_HEIGHT * 16 - 32, { 255, 0, 0 });
		}

	}
}
