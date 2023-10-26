#include "GameObject.h"
#include "TextureManager.h"
#include "Map.h"
#include "Game.h"
#include <iostream>

int GameObject::TileSize;

GameObject::GameObject() {};

GameObject::GameObject(int x, int y) { 
	objTexture = TextureManager::err_;

	destRect = new SDL_Rect;

	destRect->x = x;
	destRect->y = y;

	destRect->w = destRect->h = TileSize;

	//destRect->w = w;
	//destRect->h = h;

}

GameObject::~GameObject() {
	std::cout << "base class destructor called" << std::endl;
	delete destRect;
}

void GameObject::Update() {
	std::cout << "base class update called" << std::endl;
}

//void GameObject::SetVelX(int vel) {}
//void GameObject::SetVelY(int vel) {}

void GameObject::Render() {
	//std::cout << "base class render" << std::endl;
	SDL_RenderCopy(Game::renderer, objTexture, NULL, destRect);
}

void GameObject::setTileSize(int s) {
	TileSize = s;
}