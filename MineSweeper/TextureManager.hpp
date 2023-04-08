#pragma once
#include "Game.hpp"

class TextureManager {
public:
	static SDL_Texture* LoadTexture(const char* file);
	static void Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest);
	static void Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest, int opacity);
};
