#pragma once
#include "Defines.h"

#include "GameObject.h"
#include "TextureManager.h"
#include "Map.h"
#include "Game.h"
#include <iostream>

int GameObject::TileSize = 0; // what is the default tilesize, hmm?

GameObject::GameObject(int x, int y) { 
	objTexture = TextureManager::err_;

	destRect = new SDL_Rect;
	destRect->x = x;
	destRect->y = y;
	destRect->w = destRect->h = TileSize;

	srcRect = new SDL_Rect;
	srcRect->x = 0;
	srcRect->y = 0;
	srcRect->w = srcRect->h = 64; // omg why is this here it shouldnt be here

}

GameObject::~GameObject() {
	delete destRect;
	delete srcRect;
}

void GameObject::Render() {
	SDL_RenderCopy(Game::renderer, objTexture, srcRect, destRect);
}

void GameObject::setTileSize(int s) {
	TileSize = s;
}