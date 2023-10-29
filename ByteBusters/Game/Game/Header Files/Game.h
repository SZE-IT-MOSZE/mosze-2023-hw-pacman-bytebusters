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

	bool Init(const char* title, int xPos, int yPos, int w, int h, int tR, bool fullscreen);
	void Update();
	void Render();
	void Start();
	void Clean();
	void HandleEvents();
	void UpdateThread();

	bool Running() { return isRunning; }
	int getHeight() { return height; }
	int getWidth() { return width; }

	static SDL_Renderer* renderer;

private:

	SDL_Window* window;

	Map* map;

	Player* player;

	std::thread* gameUpdates;


	int height; // default is smallest res
	int width;
	int tileRes;
	bool isRunning;
	bool quitGame = false; //this is a stupid quick fix. i just dont want to get distracted right now. will do this properly later.
	

};
