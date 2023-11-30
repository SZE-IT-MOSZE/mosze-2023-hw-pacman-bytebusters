#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "GameObject.h"
#include "Map.h"
#include <set>
#include "GameObjectManager.h"
#include <iostream>
#include "TextureManager.h"
#include "GameObject.h"
#include <thread>
#include "Player.h"
#include "Enemy.h"

#include "Button.h"

#include "UI.h"
#include <mutex>

class Game {

public:

	static std::shared_ptr<Game> GetInstance();
	Game(Game& other) = delete;
	void operator=(const Game&) = delete;

	int Init(); //!< A j�t�k inicializ�l�sa a k�perny�n megfelel� poz�ci�ban,megfelel� m�rettel
	void HandleKeyEvents(SDL_Event* event); //!< Az esem�nyek lekezel�se
	void UpdateThread(); //!< Ezen a sz�llon fut a friss�t�s

	void StopUpdate();
	void PauseUpdate();
	void ResumeUpdate();

	void MainLoop();

	static SDL_Renderer* renderer;
	
	~Game();
	Game();
private:
	static std::shared_ptr<Game> pinstance_;
	static std::mutex mutex_;
	

	Window* window;
	UI* ui;
	Map* map; //!< Mutat� a mapra
	Player* player; //!< Mutat� a playerre
	std::thread* gameUpdates; //!<Mutat� a j�t�k friss�t�sre

	int tileRes;

	bool isRunning;
	bool inMenu;
	bool isPlaying;

	bool update;
	bool paused;
	bool confirmPause;

};
