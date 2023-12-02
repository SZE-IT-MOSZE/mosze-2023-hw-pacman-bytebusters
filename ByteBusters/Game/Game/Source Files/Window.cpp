#pragma once
#include "Defines.h"
#include "Window.h"
#include <iostream>

std::shared_ptr<Window> Window::instance_{ nullptr };
std::mutex Window::mutex_;

std::shared_ptr<Window> Window::GetInstance() {
	std::lock_guard<std::mutex> lock(mutex_);
	if (!instance_) {
		instance_ = std::shared_ptr<Window>(new Window());
		//cant use make_shared() without some "black magic" to make the private constructor visible for make_shared()
	}
	return instance_;
}

Window::Window()
{
	scaledScreenHeight = 720;
	scaledScreenWidth = 720;

	tileRes = 32;
	window = nullptr;

	windowHeight = 480;
	windowWidth = 704;
}

Window::~Window()
{
	SDL_DestroyWindow(window);
	SDL_Quit();
	std::cout << "Window destructor called\n";
}

int Window::Init(const char* title, const int xPos, const int yPos, const bool fullscreen) {
	if ((SDL_Init(SDL_INIT_VIDEO) == -1)) {
		printf("Could not initialize SDL: %s.\n", SDL_GetError());
		return -1;
	}

	SDL_DisplayMode dm;

	if (SDL_GetDesktopDisplayMode(0, &dm) != 0)
	{
		SDL_Log("SDL_GetDesktopDisplayMode failed: %s", SDL_GetError());
		return -1;
	}

	// these are scaled resolutions, not screen size in pixels
	scaledScreenWidth = dm.w;
	scaledScreenHeight = dm.h;

	if (scaledScreenHeight <= 480) {
		std::cout << "SCREEN TOO SMALL. GAME CANNOT BE STARTED." << std::endl;
		return -1;
	}
	else if (scaledScreenHeight <= 720) {
		tileRes = 32;
	}
	else if (scaledScreenHeight <= 960) {
		tileRes = 48;
	}
	else if (scaledScreenHeight <= 1200) {
		tileRes = 64;
	}
	else if (scaledScreenHeight <= 1440) {
		tileRes = 80;
	}
	else if (scaledScreenHeight <= 1680) {
		tileRes = 112;
	}
	else { // this fits 4K
		tileRes = 128;
	}
	windowHeight = tileRes * ROWS;
	windowWidth = tileRes * (COLS+2);

	//15*32 = 480
	//15*48 = 720
	//15*64 = 960
	//15*80 = 1200
	//15*96 = 1440
	//15*112 = 1680
	//15*128 = 1920

	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsystem:" << std::endl;

		window = SDL_CreateWindow(title, xPos, yPos, windowWidth, windowHeight, flags);
		if (window)
		{
			std::cout << "Window created!" << std::endl;
		}
		return 0;
	}
	else {
		return -1;
	}
}