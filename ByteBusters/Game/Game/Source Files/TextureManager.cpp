#pragma once
#include "Game.h"
#include "Defines.h"
#include "TextureManager.h"
#include <string>
#include <fstream>
#include <iostream>


SDL_Texture* TextureManager::Deerly;

SDL_Texture* TextureManager::Enemy_Ape;
SDL_Texture* TextureManager::Enemy_Deer;
SDL_Texture* TextureManager::Enemy_Homeless;
SDL_Texture* TextureManager::Enemy_Rat;
SDL_Texture* TextureManager::Enemy_Soldier;

SDL_Texture* TextureManager::concrete01;
SDL_Texture* TextureManager::concrete02;
SDL_Texture* TextureManager::jungle;
SDL_Texture* TextureManager::lava;
SDL_Texture* TextureManager::water;
SDL_Texture* TextureManager::dirt;

SDL_Texture* TextureManager::Joseph_White;
SDL_Texture* TextureManager::Yusri;

SDL_Texture* TextureManager::paper;

SDL_Texture* TextureManager::projectile;

SDL_Texture* TextureManager::err_;

SDL_Texture* TextureManager::title;
SDL_Texture* TextureManager::start;
SDL_Texture* TextureManager::start_hover;
SDL_Texture* TextureManager::load;
SDL_Texture* TextureManager::load_hover;
SDL_Texture* TextureManager::quit;
SDL_Texture* TextureManager::quit_hover;
SDL_Texture* TextureManager::save;
SDL_Texture* TextureManager::save_hover;
SDL_Texture* TextureManager::menu;
SDL_Texture* TextureManager::menu_hover;

SDL_Texture* TextureManager::heart;

SDL_Texture* TextureManager::LoadTexture(const char* texture) {
	SDL_Surface* tempSurface = IMG_Load(texture);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
	SDL_FreeSurface(tempSurface);
	return tex;
}

void TextureManager::Draw(SDL_Texture* tex, SDL_Rect* srcRect, SDL_Rect* destRect) {
	SDL_RenderCopy(Game::renderer, tex, srcRect, destRect);
}

void TextureManager::LoadAllTextures() {
	
	TextureManager::Deerly			= LoadTexture("Assets/Deerly_vegleges_sprite_sheet.png");
	
	TextureManager::Enemy_Ape		= LoadTexture("Assets/Enemy_Ape_Sprite_sheet.png");
	TextureManager::Enemy_Deer		= LoadTexture("Assets/Enemy_Deer_Sprite_sheet.png");
	TextureManager::Enemy_Homeless	= LoadTexture("Assets/Enemy_Homeless_Sprite_sheet.png");
	TextureManager::Enemy_Rat		= LoadTexture("Assets/Enemy_Rat_Sprite_sheet.png");
	TextureManager::Enemy_Soldier	= LoadTexture("Assets/Enemy_Mercenary_sprite_sheet.png");
									
	TextureManager::concrete01		= LoadTexture("Assets/concrete01.png");
	TextureManager::concrete02		= LoadTexture("Assets/concrete02.png");
	TextureManager::jungle			= LoadTexture("Assets/jungle.png");
	TextureManager::lava			= LoadTexture("Assets/lava.png");
	TextureManager::water			= LoadTexture("Assets/water.png");
	TextureManager::dirt			= LoadTexture("Assets/dirt.png");
									
	TextureManager::Joseph_White	= LoadTexture("Assets/Josepf_White_Sprite_sheet.png");
	TextureManager::Yusri			= LoadTexture("Assets/Yusri_Sprite_sheet.png");
									
	TextureManager::paper			= LoadTexture("Assets/Burned_diary_page.png");

	TextureManager::projectile		= LoadTexture("Assets/Projectile_sprite_sheet.png");

	TextureManager::err_			= LoadTexture("Assets/err_.png");

	TextureManager::title			= LoadTexture("Assets/Menu_V3.png");
	TextureManager::start			= LoadTexture("Assets/Menu_New_Game_bsc.png");
	TextureManager::start_hover		= LoadTexture("Assets/Menu_New_Game_Deerly.png");
	TextureManager::load			= LoadTexture("Assets/Menu_Load_Game_bsc.png");
	TextureManager::load_hover		= LoadTexture("Assets/Menu_Load_Game_Deerly.png");
	TextureManager::quit			= LoadTexture("Assets/Menu_Quit_bsc.png");
	TextureManager::quit_hover		= LoadTexture("Assets/Menu_Quit_Deerly.png");
	TextureManager::save			= LoadTexture("Assets/Menu_Save_bsc.png");
	TextureManager::save_hover		= LoadTexture("Assets/Menu_Save_gold.png");
	TextureManager::menu			= LoadTexture("Assets/Menu_Menu_bsc.png");
	TextureManager::menu_hover		= LoadTexture("Assets/Menu_Menu_gold.png");

	TextureManager::heart			= LoadTexture("Assets/heart.png");
}