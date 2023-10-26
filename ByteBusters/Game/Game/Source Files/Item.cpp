#include "Item.h"
#include <iostream>
#include "Game.h"

Item::Item(int x, int y, SDL_Texture* t, Player* p) : GameObject(x, y) {
	objTexture = t;

	player = p;

	playerRect = player->getDestRect();

	std::cout << "Item created at " << destRect->x << ", " << destRect->y << std::endl;

}

Item::~Item() {

}

void Item::Update() {
	SDL_RenderDrawRect(Game::renderer, destRect);
	if (SDL_HasIntersection(destRect, playerRect))
	{
		std::cout << "PICKUP" << std::endl;
	}
}