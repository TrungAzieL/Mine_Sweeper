#pragma once
#include "SDL.h"
#include "TextureManager.hpp"	

class Object {
public:

	Object();
	Object(const char* texturesheet);
	~Object();

	void Init(const char* texturesheet, int width, int height, int xpos, int ypos);
	void changePos(int width, int height, int xpos, int ypos);
	void Render();
	void Render(int opacity);

	SDL_Rect srcRect, destRect;

	bool getObjState();

private:
	SDL_Texture* objTexture;
};