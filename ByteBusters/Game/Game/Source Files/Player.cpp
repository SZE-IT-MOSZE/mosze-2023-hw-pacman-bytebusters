#pragma once

#include "Player.h"
#include "TextureManager.h"
#include "Map.h"

Player::Player(int startX, int startY, int targetResW, int targetResH) {

	objTexture = TextureManager::Deerly;

	destRect = new SDL_Rect;

	destRect->x = startX;
	destRect->y = startY;
	destRect->w = targetResW;
	destRect->h = targetResH;

	xvel = 0;
	yvel = 0;

}

Player::~Player() {
	delete destRect;
}

void Player::Update() {
	destRect->x += xvel;
	
	for (SDL_Rect* wall : Map::mapWalls)
	{
		if (SDL_HasIntersection(destRect, wall)) {
			destRect->x -= xvel;
			break;
		}
	}
	
	destRect->y += yvel;
	
	for (SDL_Rect* wall : Map::mapWalls)
	{
		if (SDL_HasIntersection(destRect, wall)) {
			destRect->y -= yvel;
			break;
		}
	}
}

void Player::SetVelX(int vel) {
	xvel = vel;
}

void Player::SetVelY(int vel) {
	yvel = vel;
}