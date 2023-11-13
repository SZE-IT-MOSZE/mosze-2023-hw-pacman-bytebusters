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
	static bool Init(const char* title, int xPos, int yPos, int w, int h, int tR, bool fullscreen); //!< A j�t�k inicializ�l�sa a k�perny�n megfelel� poz�ci�ban,megfelel� m�rettel
	static void Render(); //!< A j�t�k megjelen�t�se/ki renderel�se
	static void Start(); //!< A j�t�k ind�t�sa
	static void Clean(); //!< Az �ssze objektum t�rl�se, sub system le�ll�t�sa a j�t�k bez�r�sa el�tt
	static void HandleEvents(); //!< Az esem�nyek lekezel�se
	static void UpdateThread(); //!< Ezen a sz�llon fut a friss�t�s

	static bool Running() { return isPlaying; }
	static int getHeight() { return height; }
	static int getWidth() { return width; }

	static void SetPlaying(bool p);

	static SDL_Renderer* renderer;

private:

	static SDL_Window* window; //!<Mutat� az ablakra

	static Map* map; //!< Mutat� a mapra

	static Player* player; //!< Mutat� a playerre

	static std::thread* gameUpdates; //!<Mutat� a j�t�k friss�t�sre

	static std::set<char> isPressed;

	static int height;
	static int width;
	static int tileRes;

	static bool isRunning;
	static bool isPlaying;	

};
