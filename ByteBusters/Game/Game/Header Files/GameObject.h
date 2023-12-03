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

	//SDL_Rect GetDestRect() { return dstRect; }
	const SDL_Rect* GetDestRectPtr() { return &dstRect; }
	SDL_Point GetCenterPosition();

protected:
	static int tileRes;
	static std::weak_ptr<GameObjectManager> gom;

	SDL_Rect dstRect;
	SDL_Rect srcRect;

	SDL_Texture* objTexture;

};