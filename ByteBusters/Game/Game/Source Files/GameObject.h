#pragma once
#include "SDL.h"

class GameObject {

public:
	GameObject();
	GameObject(int startX, int startY, int targetResW, int targetResH);
	~GameObject();

	virtual void Update();

	virtual void SetVelX(int vel);
	virtual void SetVelY(int vel);

	void Render();

protected:
	SDL_Rect* destRect;
	SDL_Texture* objTexture;
};