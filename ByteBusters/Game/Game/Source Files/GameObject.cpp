#include "GameObject.h"
#include "TextureManager.h"
#include "Map.h"
#include "Game.h"
#include <iostream>

GameObject::GameObject() {};

GameObject::GameObject(int startX, int startY, int targetResW, int targetResH) {
	objTexture = TextureManager::err_;

	destRect = new SDL_Rect;

	destRect->x = startX;
	destRect->y = startY;
	destRect->w = targetResW;
	destRect->h = targetResH;

}

GameObject::~GameObject() {
	std::cout << "base class destructor" << std::endl;
	delete destRect;
}

void GameObject::Update() {}
void GameObject::SetVelX(int vel) {}
void GameObject::SetVelY(int vel) {}

void GameObject::Render() {
	//std::cout << "base class render" << std::endl;
	SDL_RenderCopy(Game::renderer, objTexture, NULL, destRect);
}