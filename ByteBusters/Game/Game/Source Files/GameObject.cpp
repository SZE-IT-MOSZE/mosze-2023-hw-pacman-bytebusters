#include "GameObject.h"
#include "TextureManager.h"

GameObject::GameObject(const char* textureSheet, int startX, int startY, int sourceResX, int sourceResY, int targetResX, int targetResY) {
	objTexture = TextureManager::LoadTexture(textureSheet);
	
	srcRect = new SDL_Rect;
	destRect = new SDL_Rect;

	srcRect->x = 0;
	srcRect->y = 0;
	srcRect->h = sourceResX;
	srcRect->w = sourceResY;

	destRect->x = startX;
	destRect->y = startY;
	destRect->w = targetResX;
	destRect->h = targetResY;

	xvel = 0;
	yvel = 0;
}

void GameObject::Update(){

	destRect->x += xvel;

	for (SDL_Rect* wall : Map::mapWalls)
	{
		if (SDL_HasIntersection(destRect, wall)) {
			destRect->x -= xvel;
			break;
		}
	}

	destRect->y += yvel;

	for (SDL_Rect* wall : Map::mapWalls)
	{
		if (SDL_HasIntersection(destRect, wall)) {
			destRect->y -= yvel;
			break;
		}
	}
	
}

void GameObject::Render() {
	SDL_RenderCopy(Game::renderer, objTexture, srcRect, destRect);
}

void GameObject::SetVelX(int vel) {
	xvel = vel;
}

void GameObject::SetVelY(int vel) {
	yvel = vel;
}