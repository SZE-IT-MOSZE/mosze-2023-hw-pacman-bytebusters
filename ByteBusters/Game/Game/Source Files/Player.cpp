#pragma once

#include "Player.h"
#include "TextureManager.h"
#include "Map.h"
#include "Game.h"
#include <iostream>

Player::Player(int x, int y, SDL_Texture* t) : GameObject(x, y) {
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
	
	for (SDL_Rect* wall : Map::mapWalls) // replace with better alternative
	{
		if (SDL_HasIntersection(destRect, wall)) {
			destRect->x -= xvel;
			break;
		}
	}
	
	destRect->y += yvel;
	
	for (SDL_Rect* wall : Map::mapWalls) //replace with better alternative
	{
		if (SDL_HasIntersection(destRect, wall)) {
			destRect->y -= yvel;
			break;
		}
	}
}

void Player::Render() { // necessary for animations???
	//std::cout << "player render, obj texture: " << objTexture << std::endl;
	SDL_RenderCopy(Game::renderer, objTexture, NULL, destRect);
	SDL_RenderDrawRect(Game::renderer, destRect);
}

void Player::SetVelX(int vel) {
	xvel = vel;
}

void Player::SetVelY(int vel) {
	yvel = vel;
}