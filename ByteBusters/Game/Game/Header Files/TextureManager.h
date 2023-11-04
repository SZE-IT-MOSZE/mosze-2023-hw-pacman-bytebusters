#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <limits>


//struct rowData {
//	int row = 0;
//	int frameCount = 1;
//	int frameDelay = INT_MAX;
//};
//
//struct sheetData {
//	int spriteSize;
//	rowData idle_R;
//	rowData idle_L;
//	rowData move_R;
//	rowData move_L;
//	rowData hit_R;
//	rowData hit_L;
//	rowData shoot_R;
//	rowData shoot_L;
//};


class TextureManager {
public:

	static SDL_Texture* LoadTexture(const char* fileName);
	static void LoadAllTextures();
	static void Draw(SDL_Texture* tex, SDL_Rect* srcRect, SDL_Rect* destRect);
	//static void readSheetData();

	//player
	static SDL_Texture* Deerly;
	//enemy
	static SDL_Texture* Enemy_Ape;
	static SDL_Texture* Enemy_Deer;
	static SDL_Texture* Enemy_Guard;
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

	//err
	static SDL_Texture* err_;

	static SDL_Texture* anim;
};