#include "TextureManager.h"
#include "Game.h"

SDL_Texture* TextureManager::LoadTexture(const char* texture) {
	SDL_Surface* tempSurface = IMG_Load(texture);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
	SDL_FreeSurface(tempSurface);

	return tex;
}

void TextureManager::Draw(SDL_Texture* tex, SDL_Rect* srcRect, SDL_Rect* destRect) {
	SDL_RenderCopy(Game::renderer, tex, srcRect, destRect);
}