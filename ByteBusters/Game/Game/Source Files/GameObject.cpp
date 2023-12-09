#pragma once
#include "Game.h"
#include "GameObject.h"
#include "TextureManager.h"
#include "GameObjectManager.h" // forward declared in header
#include <iostream>

GameObject::GameObject(int x, int y) { 
	objTexture = TextureManager::err_;

	gom = GameObjectManager::GetInstance(0);
	if (auto lockedPtr = gom.lock())
	{
		tileRes = lockedPtr->getTileRes();
	}
	else
	{
		std::cout << "YOU CANNOT CREATE A GAMEOBJECT WITHOUT MANAGER\n";
	}

	dstRect.x = x;
	dstRect.y = y;
	dstRect.w = dstRect.h = tileRes;
		   
	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = srcRect.h = 64;

}

void GameObject::Render() {
	SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &dstRect);
}

SDL_Point GameObject::GetCenterPosition() {
	SDL_Point pos;
	pos.x = dstRect.x + dstRect.w / 2;
	pos.y = dstRect.y + dstRect.h / 2;
	return pos;
}