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
	Game(Game& other) = delete; //!< T�r�lt copy konstruktor
	void operator=(const Game&) = delete; //!< T�r�lt = oper�tor
	~Game(); //!< Destruktor

	int Init(); //!< A j�t�k inicializ�l�sa, ablak l�trehoz�sa, text�r�k bet�lt�se, Map �s GemeObjectManager oszt�ly inicializ�l�sa
	void HandleKeyEvents(SDL_Event* event); //!< Esem�nyek lekezel�se
	void UpdateThread(); //!< Funkci�, ami k�l�n sz�lon friss�ti a j�t�kbeli objektumokat

	void StopUpdate(); //!< Friss�t�s meg�ll�t�sa
	void PauseUpdate(); //!< Friss�t�s sz�neteltet�se
	void ResumeUpdate(); //!< Friss�t�s �jraind�t�sa

	void MainLoop(); //!< A f� cilus, amiben a men� is van

	static SDL_Renderer* renderer; //!< Rendered, amit az objektumok haszn�lnak
	

private:
	Game(); //!< Priv�t konstruktor
	static std::weak_ptr<Game> instance_; //!< Singleton instance
	static std::mutex mutex_; //!< Thread guard
	

	std::shared_ptr<Window> window; //!< Ablak oszt�ly p�ld�nya
	std::shared_ptr<UI> ui; //!< UI oszt�ly p�ld�nya
	std::shared_ptr<Map> map; //!< Map oszt�ly p�ld�nya
	std::shared_ptr<GameObjectManager> gom; //!< GameObjectManager oszt�ly p�ld�nya

	Player* player; //!< Mutat� a Player-re input-okhoz
	std::unique_ptr<std::thread> gameUpdates; //!< Friss�t�si sz�l

	int tileRes; //!< Cella m�rete

	bool isRunning; //!< Fut-e az applik�ci�
	bool inMenu; //!< A men�ben van-e a felhszn�l�
	bool isPlaying; //!< J�tszik-e a felhaszn�l�

	bool update; //!< A friss�t�s megy
	bool paused; //!< A fris�t�s sz�neteltetve van
	bool confirmPause; //!< A friss�t�s sz�neteltet�s�nek meger�s�t�se

	std::set<char> isPressed;
};
