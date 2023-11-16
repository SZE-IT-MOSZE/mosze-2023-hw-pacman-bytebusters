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

class Game {

public:

	Game();
	~Game();

	int Init(SDL_Window* window, const int tileRes); //!< A játék inicializálása a képernyõn megfelelõ pozícióban,megfelelõ mérettel
	void Render(); //!< A játék megjelenítése/ki renderelése
	void Start(); //!< A játék indítása
	void Clean(); //!< Az össze objektum törlése, sub system leállítása a játék bezárása elõtt
	void HandleEvents(); //!< Az események lekezelése
	void UpdateThread(); //!< Ezen a szállon fut a frissítés

	bool Running() const { return isPlaying; }

	void SetPlaying(bool p);

	static SDL_Renderer* renderer;

private:

	SDL_Window* window; //!<Mutató az ablakra
	Map* map; //!< Mutató a mapra
	Player* player; //!< Mutató a playerre
	std::thread* gameUpdates; //!<Mutató a játék frissítésre

	std::set<char> pressedKeys;

	int tileRes;

	bool isRunning;
	bool isPlaying;	

};
