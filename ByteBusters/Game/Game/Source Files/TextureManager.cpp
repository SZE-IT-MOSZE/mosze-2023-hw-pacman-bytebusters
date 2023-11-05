#pragma once
#include "TextureManager.h"
#include "Game.h"
#include <iostream>
#include <fstream>
#include <string>

SDL_Texture* TextureManager::Deerly;

SDL_Texture* TextureManager::Enemy_Ape;
SDL_Texture* TextureManager::Enemy_Deer;
SDL_Texture* TextureManager::Enemy_Guard;
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

SDL_Texture* TextureManager::err_;

SDL_Texture* TextureManager::anim;

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
	
	TextureManager::Deerly			= LoadTexture("Assets/Deerly_ultimate_sprite_sheet.png");
	
	TextureManager::Enemy_Ape		= LoadTexture("Assets/Enemy_Ape.png");
	TextureManager::Enemy_Deer		= LoadTexture("Assets/Enemy_Deer.png");
	TextureManager::Enemy_Guard		= LoadTexture("Assets/Enemy_Guard.png");
	TextureManager::Enemy_Homeless	= LoadTexture("Assets/Enemy_Homeless.png");
	TextureManager::Enemy_Rat		= LoadTexture("Assets/Enemy_Rat.png");
	TextureManager::Enemy_Soldier	= LoadTexture("Assets/Enemy_Soldier.png");
									
	TextureManager::concrete01		= LoadTexture("Assets/concrete01.png");
	TextureManager::concrete02		= LoadTexture("Assets/concrete02.png");
	TextureManager::jungle			= LoadTexture("Assets/jungle.png");
	TextureManager::lava			= LoadTexture("Assets/lava.png");
	TextureManager::water			= LoadTexture("Assets/water.png");
	TextureManager::dirt			= LoadTexture("Assets/dirt.png");
									
	TextureManager::Joseph_White	= LoadTexture("Assets/Joseph_White.png");
	TextureManager::Yusri			= LoadTexture("Assets/Yusri.png");
									
	TextureManager::paper			= LoadTexture("Assets/Burned_diary_page.png");

	TextureManager::err_			= LoadTexture("Assets/err_.png");
}