#include "GameObject.h"
#include "TextureManager.h"
#include "Map.h"
#include "Game.h"

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
	delete destRect;
}

void GameObject::Update() {}
void GameObject::SetVelX(int vel) {};
void GameObject::SetVelY(int vel) {};

void GameObject::Render() {
	SDL_RenderCopy(Game::renderer, objTexture, NULL, destRect);
}