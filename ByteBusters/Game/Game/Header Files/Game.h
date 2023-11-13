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
	static bool Init(const char* title, int xPos, int yPos, int w, int h, int tR, bool fullscreen); //!< A játék inicializálása a képernyõn megfelelõ pozícióban,megfelelõ mérettel
	static void Render(); //!< A játék megjelenítése/ki renderelése
	static void Start(); //!< A játék indítása
	static void Clean(); //!< Az össze objektum törlése, sub system leállítása a játék bezárása elõtt
	static void HandleEvents(); //!< Az események lekezelése
	static void UpdateThread(); //!< Ezen a szállon fut a frissítés

	static bool Running() { return isPlaying; }
	static int getHeight() { return height; }
	static int getWidth() { return width; }

	static void SetPlaying(bool p);

	static SDL_Renderer* renderer;

private:

	static SDL_Window* window; //!<Mutató az ablakra

	static Map* map; //!< Mutató a mapra

	static Player* player; //!< Mutató a playerre

	static std::thread* gameUpdates; //!<Mutató a játék frissítésre

	static std::set<char> isPressed;

	static int height;
	static int width;
	static int tileRes;

	static bool isRunning;
	static bool isPlaying;	

};
