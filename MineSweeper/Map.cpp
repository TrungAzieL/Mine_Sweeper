#include "TextureManager.hpp"
#include "Map.hpp"
#include <string>

SDL_Texture* mapTexture ;

void Map::Draw() {
	mapTexture = TextureManager::LoadTexture("assets/map.png");

	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.h = 32;
	srcRect.w = 32;

	destRect.h = destRect.w = 32;

	for (int i = 0; i < GAME_SIZE_HEIGHT; ++i) {
		for (int j = 0; j < GAME_SIZE_WIDTH; ++j) {
			srcRect.x = 32 * map[i][j];
			destRect.x = 32 * j;
			destRect.y = 32 * i + 50;
			TextureManager::Draw(mapTexture, srcRect, destRect);
		}
	}

}

void Map::ChangeState(int x, int y) {
	if (x < 0 || x > GAME_SIZE_HEIGHT - 1) return;
	if (y < 0 || y > GAME_SIZE_WIDTH - 1) return;
	if (map[x][y] == 1) return;

	tilesLeft--;
	map[x][y] = 1;
	if (mine[x][y] == 0) {
		ChangeState(x - 1, y);
		ChangeState(x, y - 1);
		ChangeState(x + 1, y);
		ChangeState(x, y + 1);

		ChangeState(x - 1, y - 1);
		ChangeState(x + 1, y - 1);
		ChangeState(x - 1, y + 1);
		ChangeState(x + 1, y + 1);
	}
	else return;
}

void Map::RandomMine(int x, int y) {
	srand(time(NULL));
	int minesLeft = minesTotal;
	int tilesLeft = tilesTotal;

	for (int i = 0; i < GAME_SIZE_HEIGHT; ++i) {
		for (int j = 0; j < GAME_SIZE_WIDTH; ++j) {
			if (abs(i - x) <= 2 && abs(j - y) <= 2) {
				tilesLeft--;
				continue;
			}

			int r = rand() % (100 + 1); // [0..100]
			if (r * tilesLeft <= 100 * minesLeft) {
				minesLeft--;
				mine[i][j] = -1;
			}
			tilesLeft--;
		}
	}

	for (int i = 0; i < GAME_SIZE_HEIGHT; ++i) {
		for (int j = 0; j < GAME_SIZE_WIDTH; ++j) {
			if (mine[i][j] == -1) continue;
			
			for (int n = max(i - 1, 0); n <= min(i + 1, GAME_SIZE_HEIGHT - 1); ++n) {
				for (int m = max(j - 1, 0); m <= min(j + 1, GAME_SIZE_WIDTH - 1); ++m) {
					if (mine[n][m] == -1)
						mine[i][j]++;
				}
			}
		}
	}

	//for (int i = 0; i < GAME_SIZE_HEIGHT; ++i) {
	//	for (int j = 0; j < GAME_SIZE_WIDTH; ++j) {
	//		if (mine[i][j] == -1)
	//			cout << mine[i][j] << " ";
	//		else 
	//			cout << " " << mine[i][j] << " ";
	//	}
	//	cout << '\n';
	//}

	isGenerated = true;
}

int Map::getMineCnt(int x, int y) {
	return mine[x][y];
}

bool Map::getMapState(int x, int y) {
	return map[x][y];
}