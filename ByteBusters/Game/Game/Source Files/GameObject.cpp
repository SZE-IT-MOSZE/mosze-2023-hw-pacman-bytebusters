#include "GameObject.h"
#include "TextureManager.h"
#include "Map.h"
#include "Game.h"
#include <iostream>

int GameObject::TileSize;

GameObject::GameObject(int x, int y) { 
	objTexture = TextureManager::err_;

	destRect = new SDL_Rect;

	destRect->x = x;
	destRect->y = y;

	destRect->w = destRect->h = TileSize;

}

GameObject::~GameObject() {
	delete destRect;
}

void GameObject::Update() {
}

void GameObject::Render() {
	SDL_RenderCopy(Game::renderer, objTexture, NULL, destRect);
}

void GameObject::setTileSize(int s) {
	TileSize = s;
}