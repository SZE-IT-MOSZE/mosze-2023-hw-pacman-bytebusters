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

	dstRect.x = x;
	dstRect.y = y;
	dstRect.w = dstRect.h = tileRes;
		   
	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = srcRect.h = 64;

}

GameObject::~GameObject() {

}

void GameObject::Render() {
	SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &dstRect);
}

void GameObject::setTileSize(int s) {
	tileRes = s;
}

SDL_Point GameObject::GetCenterPosition() {
	SDL_Point pos;
	pos.x = dstRect.x + dstRect.w / 2;
	pos.y = dstRect.y + dstRect.h / 2;
	return pos;
}