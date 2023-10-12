#pragma once

#ifndef Game_h
#define Game_h

#include "SDL.h"
#include "SDL_image.h"

class Game {
public:
	Game();
	~Game();

	void init(const char* title, int xPos, int yPos, int width, int height, bool fullscreen);
	void update();
	void render();
	void clean();
	void handleEvents();

	bool running() { return isRunning; }

private:
	bool isRunning;
	SDL_Window* window;
	SDL_Renderer* renderer;
};

#endif /* Game_h */