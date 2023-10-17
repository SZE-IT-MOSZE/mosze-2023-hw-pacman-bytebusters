#pragma once
#include "Game.h"

class GameObject {

public:
	GameObject(const char* textureSheet, int startX, int startY, int sourceResX, int sourceResY, int targetResX, int targetResY);
	~GameObject();

	void Update();
	void Render();

	void SetVelX(int vel);
	void SetVelY(int vel);

private:
	int xvel, yvel;
	SDL_Texture* objTexture;
	SDL_Rect srcRect, destRect;


};