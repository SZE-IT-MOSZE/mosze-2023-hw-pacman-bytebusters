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
	~Game();

	int Init(); //!< A j�t�k inicializ�l�sa a k�perny�n megfelel� poz�ci�ban,megfelel� m�rettel
	void HandleKeyEvents(SDL_Event* event); //!< Az esem�nyek lekezel�se
	void UpdateThread(); //!< Ezen a sz�llon fut a friss�t�s

	void StopUpdate();
	void PauseUpdate();
	void ResumeUpdate();

	void MainLoop();

	static SDL_Renderer* renderer;
	

private:
	Game();
	static std::weak_ptr<Game> instance_;
	static std::mutex mutex_;
	

	std::shared_ptr<Window> window;
	std::shared_ptr<UI> ui;
	std::shared_ptr<Map> map; //!< Mutat� a mapra
	std::shared_ptr<GameObjectManager> gom;

	Player* player; //!< Mutat� a playerre
	std::unique_ptr<std::thread> gameUpdates;

	int tileRes;

	bool isRunning;
	bool inMenu;
	bool isPlaying;

	bool update;
	bool paused;
	bool confirmPause;

};
