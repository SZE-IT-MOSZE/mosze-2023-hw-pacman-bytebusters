#pragma once
#include "SDL.h"
#include <mutex>

class Window
{
public:
	static std::shared_ptr<Window> GetInstance();
	Window(Window& other) = delete;
	void operator=(const Window&) = delete;
	~Window();


	int Init(const char* title, const int xPos, const int yPos, const bool fullscreen); // 0 on success, negative on failure
	SDL_Window* GetWindow() { return window; }
	int GetTileRes() { return tileRes; }

private:
	Window();
	static std::shared_ptr<Window> instance_;
	static std::mutex mutex_;

	int scaledScreenHeight, scaledScreenWidth;
	int windowWidth, windowHeight;
	int tileRes;
	SDL_Window* window; //!<Mutató az ablakra
};

