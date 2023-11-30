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

	int Init(); //!< A játék inicializálása a képernyõn megfelelõ pozícióban,megfelelõ mérettel
	void HandleKeyEvents(SDL_Event* event); //!< Az események lekezelése
	void UpdateThread(); //!< Ezen a szállon fut a frissítés

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
	Map* map; //!< Mutató a mapra
	Player* player; //!< Mutató a playerre
	std::thread* gameUpdates; //!<Mutató a játék frissítésre

	int tileRes;

	bool isRunning;
	bool inMenu;
	bool isPlaying;

	bool update;
	bool paused;
	bool confirmPause;

};
