#pragma once
#include "Defines.h"

#include "GameObject.h"
#include "TextureManager.h"
#include "Map.h"
#include "Game.h"
#include <iostream>

#include "GameObjectManager.h" // forward declared in header

int GameObject::tileRes = 32;
std::weak_ptr<GameObjectManager> GameObject::gom;

GameObject::GameObject(int x, int y) { 
	objTexture = TextureManager::err_;

	gom = GameObjectManager::GetInstance(0);

	destRect = new SDL_Rect;
	destRect->x = x;
	destRect->y = y;
	destRect->w = destRect->h = tileRes;

	srcRect = new SDL_Rect;
	srcRect->x = 0;
	srcRect->y = 0;
	srcRect->w = srcRect->h = 64;

}

GameObject::~GameObject() {
	delete destRect;
	delete srcRect;
}

void GameObject::Render() {
	SDL_RenderCopy(Game::renderer, objTexture, srcRect, destRect);
}

void GameObject::setTileSize(int s) {
	tileRes = s;
}