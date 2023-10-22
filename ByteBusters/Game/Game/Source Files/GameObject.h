#pragma once
#include "SDL.h"

class GameObject {

public:

	GameObject();
	GameObject(int startX, int startY, int targetResW, int targetResH);
	virtual  ~GameObject();

	virtual void Update();
	virtual void Render();

	SDL_Rect* getDestRect() {
		return destRect;
	};

	virtual void SetVelX(int vel);
	virtual void SetVelY(int vel);

	

protected:
	SDL_Rect* destRect;
	SDL_Texture* objTexture;
};