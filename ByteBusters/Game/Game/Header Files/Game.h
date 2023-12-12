#pragma once
#include "UI.h"
#include "Map.h"
#include "SDL.h"
#include "Enemy.h"
#include "Button.h"
#include "Player.h"
#include "Window.h"
#include "SDL_image.h"
#include "GameObject.h"
#include "TextureManager.h"
#include "GameObjectManager.h"
#include <set>
#include <mutex>
#include <thread>
#include <iostream>

class Game {

public:

	static std::shared_ptr<Game> GetInstance(); //!< Singleton GetInstance
	Game(Game& other) = delete; //!< Törölt copy konstruktor
	void operator=(const Game&) = delete; //!< Törölt = operátor
	~Game(); //!< Destruktor

	int Init(); //!< A játék inicializálása, ablak létrehozása, textúrák betöltése, Map és GemeObjectManager osztály inicializálása
	void HandleKeyEvents(SDL_Event* event); //!< Események lekezelése
	void UpdateThread(); //!< Funkció, ami külön szálon frissíti a játékbeli objektumokat

	void StopUpdate(); //!< Frissítés megállítésa
	void PauseUpdate(); //!< Frissítés szüneteltetése
	void ResumeUpdate(); //!< Frissítés újraindítása

	void MainLoop(); //!< A fõ cilus, amiben a menü is van

	static SDL_Renderer* renderer; //!< Rendered, amit az objektumok használnak
	

private:
	Game(); //!< Privát konstruktor
	static std::weak_ptr<Game> instance_; //!< Singleton instance
	static std::mutex mutex_; //!< Thread guard
	

	std::shared_ptr<Window> window; //!< Ablak osztály példánya
	std::shared_ptr<UI> ui; //!< UI osztály példánya
	std::shared_ptr<Map> map; //!< Map osztály példánya
	std::shared_ptr<GameObjectManager> gom; //!< GameObjectManager osztály példánya

	Player* player; //!< Mutató a Player-re input-okhoz
	std::unique_ptr<std::thread> gameUpdates; //!< Frissítési szál

	int tileRes; //!< Cella mérete

	bool isRunning; //!< Fut-e az applikáció
	bool inMenu; //!< A menüben van-e a felhsználó
	bool isPlaying; //!< Játszik-e a felhasználó

	bool update; //!< A frissítés megy
	bool paused; //!< A frisítés szüneteltetve van
	bool confirmPause; //!< A frissítés szüneteltetésének megerõsítése

	std::set<char> isPressed;
};
