#pragma once

#ifndef Game_h
#define Game_h

#include "SDL.h"
#include "SDL_image.h"
#include "Map.h"
#include "GameObject.h"
#include <set>

class Game {

public:
	Game();
	~Game();

	void Init(const char* title, int xPos, int yPos, int width, int height, int tileRes, bool fullscreen);
	//void Update();
	void Render();
	void Clean();
	void HandleEvents();
	void UpdateThread();

	bool Running() { return isRunning; }
	int getHeight() { return height; }
	int getWidth() { return width; }

	static SDL_Renderer* renderer;

private:

	SDL_Window* window;

	

	int height; // default is smallest res
	int width;
	int tileRes;
	bool isRunning;
	

};

#endif /* Game_h */