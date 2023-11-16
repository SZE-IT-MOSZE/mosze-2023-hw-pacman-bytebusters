#pragma once
#include "SDL.h"

class Window
{
public:
	Window();
	~Window();
	int Init(const char* title, const int xPos, const int yPos, const bool fullscreen); // 0 on success, negative on failure
	SDL_Window* GetWindow() { return window; }
	int GetTileRes() { return tileRes; }

private:
	int scaledScreenHeight, scaledScreenWidth;
	int windowWidth, windowHeight;
	int tileRes;
	SDL_Window* window; //!<Mutató az ablakra
};

