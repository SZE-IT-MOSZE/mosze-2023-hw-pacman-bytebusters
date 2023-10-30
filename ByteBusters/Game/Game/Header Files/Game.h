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
	Game(); //!< Üres objektum létrehozása
	~Game(); 

	bool Init(const char* title, int xPos, int yPos, int w, int h, int tR, bool fullscreen); //!< A játék inicializálása a képernyõn megfelelõ pozícióban,megfelelõ mérettel
	void Update(); 
	void Render(); //!< A játék megjelenítése/ki renderelése
	void Start(); //!< A játék indítása
	void Clean(); //!< Az össze objektum törlése, sub system leállítása a játék bezárása elõtt
	void HandleEvents(); //!< Az események lekezelése
	void UpdateThread(); //!< Ezen a szállon fut a frissítés

	bool Running() { return isRunning; }
	int getHeight() { return height; }
	int getWidth() { return width; }

	static SDL_Renderer* renderer;

private:

	SDL_Window* window; //!<Mutató az ablakra

	Map* map; //!< Mutató a mapra

	Player* player; //!< Mutató a playerre

	std::thread* gameUpdates; //!<Mutató a játék frissítésre


	int height; // default is smallest res
	int width;
	int tileRes;
	bool isRunning;
	bool quitGame = false; //this is a stupid quick fix. i just dont want to get distracted right now. will do this properly later.
	

};
