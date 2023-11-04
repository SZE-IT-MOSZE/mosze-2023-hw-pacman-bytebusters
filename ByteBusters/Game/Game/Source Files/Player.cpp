#pragma once

#include "Player.h"
#include "TextureManager.h"
#include "Map.h"
#include "Game.h"
#include <iostream>
#include "GameObjectManager.h"

struct rowData {
	int row = 0;
	int frameCount = 1;
	int frameDelay = INT_MAX;
};

struct sheetData {
	int spriteSize;
	rowData idle_R;
	rowData idle_L;
	rowData move_R;
	rowData move_L;
	rowData hit_R;
	rowData hit_L;
	rowData shoot_R;
	rowData shoot_L;
};

/*
Idle_R 5 200
Idle_L 5 200
Move_R 3 200
Move_L 3 200
Hit_R 7 100
Hit_L 7 100
Shoot_R 5 100
Shoot_L 5 100

*/

Player::Player(int x, int y, SDL_Texture* t, std::forward_list<Wall*>& w, std::forward_list<Item*>& i) : walls(w), items(i), GameObject(x, y) {
	std::cout << "player tilesize " << TileSize << std::endl;

	objTexture = t;

	objTexture = TextureManager::anim;

	xvel = 0;
	yvel = 0;

	srcRect = new SDL_Rect;
	srcRect->x = 0;
	srcRect->y = 0;

	srcRect->w = srcRect->h = 64;



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

/*
row = offset by size
name 	row	frames	delay
Idle_R 	0	5 		200
Idle_L 	1	5 		200
Move_R 	2	3 		200
Move_L 	3	3 		200
Hit_R 	4	7 		100
Hit_L 	5	7 		100
Shoot_R	6	5 		100
Shoot_L	7	5 		100
*/

int textureSize = 64; // rectangular sprite size in pixels
int currentDefault = 0; // currently default idle animation
bool facingRight = true;
bool facingLeft = false;
bool facingDown = false;
bool facingUp = false;
int sheetData[8][2] = {
	{5, 200},
	{5, 200},
	{3, 200},
	{3, 200},
	{7, 100},
	{7, 100},
	{5, 100},
	{5, 100},
};

Uint32 frameStart = SDL_GetTicks();	// start of render
int frameDelay = 0;					// length between two renders of this object in milliseconds
int i = 0;
int row = 0;

void Player::Render() {
	//std::cout << "Row: " << row << std::endl;
	frameDelay = SDL_GetTicks() - frameStart;
	if (frameDelay > sheetData[row][1]) // if time to display next frame
	{
		frameStart = SDL_GetTicks();

		srcRect->y = row * textureSize;

		i++; // increment frames
		if (i >= sheetData[row][0]) // dont go past last frame 
		{
			i = 0; // return to first frame
			if (facingRight)
			{
				row = 0;
			}
			else
			{
				row = 1;
			}
		}
		srcRect->x = i * textureSize;
	}

	SDL_RenderCopy(Game::renderer, objTexture, srcRect, destRect);
	
	
}

void Player::SetVelX(int v) { 
	
	xvel = v;

	switch (v)
	{
	case 1:
		std::cout << "setvelx row 2" << std::endl;
		row = 2;
		facingRight = true;
		break;
	case 0:
		if (facingRight) //default
		{
			row = 0;
		} 
		else
		{
			row = 1;
		}
		break;
	case -1:
		std::cout << "setvelx row 3" << std::endl;
		row = 3;
		facingRight = false;
		break;
	default:
		break;
	}
}

void Player::SetVelY(int v) {
	yvel = v;

	switch (v)
	{
	case 1:
	case -1:
		std::cout << "setvely" << std::endl;
		if (facingRight)
		{
			row = 2;
		}
		else
		{
			row = 3;
		}
		break;
	case 0:
		if (facingRight) //default
		{
			row = 0;
		}
		else
		{
			row = 1;
		}
		break;
	default:
		break;
	}
}

void Player::Shoot() { // no up or down shoot animation
	xvel = 0;
	yvel = 0;

	if (facingRight)
	{
		row = 6;
	}
	else 
	{
		row = 7;
	}
}

void Player::Hit() { // no up or down hit animation
	xvel = 0;
	yvel = 0;

	if (facingRight)
	{
		row = 4;
	}
	else
	{
		row = 5;
	}
}

/*
row = offset by size
name 	row	frames	delay
Idle_R 	0	5 		200
Idle_L 	1	5 		200
Move_R 	2	3 		200
Move_L 	3	3 		200
Hit_R 	4	7 		100
Hit_L 	5	7 		100
Shoot_R	6	5 		100
Shoot_L	7	5 		100
*/


void Player::Reset() {
	destRect->x = TileSize*9;
	destRect->y = TileSize*13;
}



