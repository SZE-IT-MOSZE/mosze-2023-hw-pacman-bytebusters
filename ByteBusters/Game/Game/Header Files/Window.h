#pragma once
#include "SDL.h"
#include <mutex>

class Window
{
public:
	static std::shared_ptr<Window> GetInstance(); //!< Singleton GetInstance
	Window(Window& other) = delete; //!< Törölt copy konstruktor
	void operator=(const Window&) = delete; //!< Törölt = operátor
	~Window(); //!< Destruktor


	int Init(const char* title, const int xPos, const int yPos, const bool fullscreen); //!< Ablak inicializálása
	SDL_Window* GetWindow() { return window; }
	int GetTileRes() { return tileRes; } //!< Cella mérete

private:
	Window(); //!< Destruktor
	static std::weak_ptr<Window> instance_; //!< Singleton instance
	static std::mutex mutex_; //!< Thread guard

	int scaledScreenHeight, scaledScreenWidth; //!< Képernyõ praktikus mérete
	int windowWidth, windowHeight; //!< Ablak mérete
	int tileRes; //!< Cella méret
	SDL_Window* window; //!<Mutató az ablakra
};

