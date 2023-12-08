#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <limits>


class TextureManager {
public:

	static SDL_Texture* LoadTexture (const char* fileName); //!< Textúra beolvasása png-bõl
	static void LoadAllTextures(); //!< Összes textúra betöltése
	static void Draw(SDL_Texture* tex, SDL_Rect* srcRect, SDL_Rect* destRect); //!< Textúra kirajzolása képernyõre

	//player
	static SDL_Texture* Deerly;
	//enemy
	static SDL_Texture* Enemy_Ape;
	static SDL_Texture* Enemy_Deer;
	static SDL_Texture* Enemy_Homeless;
	static SDL_Texture* Enemy_Rat;
	static SDL_Texture* Enemy_Soldier;
	//map
	static SDL_Texture* concrete01;
	static SDL_Texture* concrete02;
	static SDL_Texture* jungle;
	static SDL_Texture* lava;
	static SDL_Texture* water;
	static SDL_Texture* dirt;
	//misc
	static SDL_Texture* Joseph_White;
	static SDL_Texture* Yusri;

	static SDL_Texture* paper;

	static SDL_Texture* projectile;

	//err
	static SDL_Texture* err_;

	//menu
	static SDL_Texture* title;
	static SDL_Texture* start;
	static SDL_Texture* start_hover;
	static SDL_Texture* load;
	static SDL_Texture* load_hover;
	static SDL_Texture* quit;
	static SDL_Texture* quit_hover;
	static SDL_Texture* save;
	static SDL_Texture* save_hover;
	static SDL_Texture* menu;
	static SDL_Texture* menu_hover;

	static SDL_Texture* heart;

};