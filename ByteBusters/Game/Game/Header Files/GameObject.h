#pragma once
#include "SDL.h"
#include <memory>

class GameObjectManager;

class GameObject {

public:

	GameObject(int x, int y);
	virtual ~GameObject();

	virtual void Update() {};
	virtual void Render();

	static void setTileSize(int s);

	SDL_Rect* GetDestRect() { return destRect; }

protected:
	static int tileRes;
	static std::weak_ptr<GameObjectManager> gom;

	SDL_Rect* destRect;
	SDL_Rect* srcRect;

	SDL_Texture* objTexture;

};