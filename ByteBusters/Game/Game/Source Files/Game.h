#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "GameObject.h"
#include "Map.h"
#include <set>
#include "GameObjectManager.h"

class Game {

public:
	Game();
	~Game();

	void Init(const char* title, int xPos, int yPos, int w, int h, int tR, bool fullscreen);
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


	int height; // default is smallest res
	int width;
	int tileRes;
	bool isRunning;
	

};
