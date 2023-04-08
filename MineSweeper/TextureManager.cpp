#include "Game.hpp"
#include "TextureManager.hpp"

SDL_Texture* TextureManager::LoadTexture(const char* texture) {
	SDL_Surface* tmpSurface = IMG_Load(texture);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);

	return tex;
}

void TextureManager::Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest)
{
	SDL_SetTextureAlphaMod(tex, 255);
	SDL_RenderCopyEx(Game::renderer, tex, &src, &dest, NULL, NULL, SDL_FLIP_NONE);
}

void TextureManager::Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest, int opacity)
{
	SDL_SetTextureAlphaMod(tex, opacity);
	SDL_RenderCopyEx(Game::renderer, tex, &src, &dest, NULL, NULL, SDL_FLIP_NONE);
}
