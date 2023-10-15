#pragma once

#ifndef Game_h
#define Game_h

#include "SDL.h"
#include "SDL_image.h"

class Game {

public:
	Game();
	~Game();

	void Init(const char* title, int xPos, int yPos, int width, int height, bool fullscreen);
	void Update();
	void Render();
	void Clean();
	void HandleEvents();

	bool Running() { return isRunning; }
	int getHeight() { return height; }
	int getWidth() { return width; }

	static SDL_Renderer* renderer;

private:

	int height = 600;
	int width = 800;
	bool isRunning;
	SDL_Window* window;

};

#endif /* Game_h */