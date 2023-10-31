#pragma once

#include "Player.h"
#include "TextureManager.h"
#include "Map.h"
#include "Game.h"
#include <iostream>
#include "GameObjectManager.h"

Player::Player(int x, int y, SDL_Texture* t, std::forward_list<Wall*>& w, std::forward_list<Item*>& i) : walls(w), items(i), GameObject(x, y) {
	std::cout << "player tilesize " << TileSize << std::endl;

	objTexture = t;

	xvel = 0;
	yvel = 0;
}

Player::~Player() {
	std::cout << "player destructor called" << std::endl;
}

void Player::Update() {

	destRect->x += xvel;
	for (Wall* wall : walls)
	{
		if (SDL_HasIntersection(destRect, wall->GetDestRect())) {
			destRect->x -= xvel;
			break;
		}
	}

	destRect->y += yvel;
	for (Wall* wall : walls)
	{
		if (SDL_HasIntersection(destRect, wall->GetDestRect())) {
			destRect->y -= yvel;
			break;
		}
	}

	for (Item* item : items)
	{
		if (SDL_HasIntersection(destRect, item->GetDestRect())) {
			std::cout << "Item Pickup" << std::endl;
			items.remove(item);
			delete item;
			break;
		}
	}
}

void Player::Render() {
	SDL_RenderCopy(Game::renderer, objTexture, NULL, destRect);
}

void Player::SetVelX(int v) {
	xvel = v;
}

void Player::SetVelY(int v) {
	yvel = v;
}

void Player::Reset() {
	destRect->x = TileSize*9;
	destRect->y = TileSize*13;
}