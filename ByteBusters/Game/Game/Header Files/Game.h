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
	Game(); //!< �res objektum l�trehoz�sa
	~Game(); 

	bool Init(const char* title, int xPos, int yPos, int w, int h, int tR, bool fullscreen); //!< A j�t�k inicializ�l�sa a k�perny�n megfelel� poz�ci�ban,megfelel� m�rettel
	void Update(); 
	void Render(); //!< A j�t�k megjelen�t�se/ki renderel�se
	void Start(); //!< A j�t�k ind�t�sa
	void Clean(); //!< Az �ssze objektum t�rl�se, sub system le�ll�t�sa a j�t�k bez�r�sa el�tt
	void HandleEvents(); //!< Az esem�nyek lekezel�se
	void UpdateThread(); //!< Ezen a sz�llon fut a friss�t�s

	bool Running() { return isRunning; }
	int getHeight() { return height; }
	int getWidth() { return width; }

	static SDL_Renderer* renderer;

private:

	SDL_Window* window; //!<Mutat� az ablakra

	Map* map; //!< Mutat� a mapra

	Player* player; //!< Mutat� a playerre

	std::thread* gameUpdates; //!<Mutat� a j�t�k friss�t�sre


	int height; // default is smallest res
	int width;
	int tileRes;
	bool isRunning;
	bool quitGame = false; //this is a stupid quick fix. i just dont want to get distracted right now. will do this properly later.
	

};
