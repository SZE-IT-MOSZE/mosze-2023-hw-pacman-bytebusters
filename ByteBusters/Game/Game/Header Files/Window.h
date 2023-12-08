#pragma once
#include "SDL.h"
#include <mutex>

class Window
{
public:
	static std::shared_ptr<Window> GetInstance(); //!< Singleton GetInstance
	Window(Window& other) = delete; //!< T�r�lt copy konstruktor
	void operator=(const Window&) = delete; //!< T�r�lt = oper�tor
	~Window(); //!< Destruktor


	int Init(const char* title, const int xPos, const int yPos, const bool fullscreen); //!< Ablak inicializ�l�sa
	SDL_Window* GetWindow() { return window; }
	int GetTileRes() { return tileRes; } //!< Cella m�rete

private:
	Window(); //!< Destruktor
	static std::weak_ptr<Window> instance_; //!< Singleton instance
	static std::mutex mutex_; //!< Thread guard

	int scaledScreenHeight, scaledScreenWidth; //!< K�perny� praktikus m�rete
	int windowWidth, windowHeight; //!< Ablak m�rete
	int tileRes; //!< Cella m�ret
	SDL_Window* window; //!<Mutat� az ablakra
};

