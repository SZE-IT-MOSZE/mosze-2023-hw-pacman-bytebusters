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

class Game {

public:

	Game();
	~Game();

	int Init(SDL_Window* window, const int tileRes); //!< A j�t�k inicializ�l�sa a k�perny�n megfelel� poz�ci�ban,megfelel� m�rettel
	void Render(); //!< A j�t�k megjelen�t�se/ki renderel�se
	void Start(); //!< A j�t�k ind�t�sa
	void Clean(); //!< Az �ssze objektum t�rl�se, sub system le�ll�t�sa a j�t�k bez�r�sa el�tt
	void HandleEvents(SDL_Event* event); //!< Az esem�nyek lekezel�se
	void UpdateThread(); //!< Ezen a sz�llon fut a friss�t�s

	void StopUpdate();
	void StartUpdate(); // not the best name, it just sets the variable that lets it run when update is created
	void PauseUpdate();
	void ResumeUpdate();


	bool isPlayerDead();



	static SDL_Renderer* renderer;

private:

	//UI* ui;

	SDL_Window* window; //!<Mutat� az ablakra
	//Map* map; //!< Mutat� a mapra
	Player* player; //!< Mutat� a playerre
	//std::thread* gameUpdates; //!<Mutat� a j�t�k friss�t�sre

	std::set<char> pressedKeys;

	int tileRes;

	bool update;
	bool paused;

};
