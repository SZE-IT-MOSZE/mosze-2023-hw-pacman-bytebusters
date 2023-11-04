#pragma once
#include "SDL.h"

class GameObject {

public:

	GameObject(int x, int y);
	virtual ~GameObject();

	virtual void Update();
	virtual void Render();

	static void setTileSize(int s);

	SDL_Rect* GetDestRect() { return destRect; }

protected:
	static int TileSize;

	SDL_Rect* destRect;
	SDL_Rect* srcRect;
	SDL_Rect* hitbox;

	SDL_Texture* objTexture;

};