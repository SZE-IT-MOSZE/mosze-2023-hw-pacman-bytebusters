#pragma once

#include "Player.h"
#include "TextureManager.h"
#include "Map.h"
#include "Game.h"
#include <iostream>
#include "GameObjectManager.h"
#include "Defines.h"



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

Player::Player(int x, int y, int s, SDL_Texture* t, std::forward_list<Wall*>& w, std::forward_list<Item*>& i) : walls(w), items(i), GameObject(x, y) {
	objTexture = t;

	xvel = 0;
	yvel = 0;

	srcRect = new SDL_Rect;
	srcRect->x = 0;
	srcRect->y = 0;

	srcRect->w = srcRect->h = PLAYERSPRITESIZE;

	uninterruptibleAnimation = false;

	frameStart = SDL_GetTicks();	// start of render
	frameDelay = 0;					// length between two renders of this object in milliseconds
	frameCounter = 0;				// frame counter
	row = 0;						// animation to display

	speed = s * TileSize/DIVIDEBYTHIS;
}

Player::~Player() {
	std::cout << "player destructor called" << std::endl;
}


void Player::Update() {

	//place enemy collision/hit check above here

	if (uninterruptibleAnimation) return; // if an uninterruptible animation is playing the character does not move
		
	destRect->x += xvel * speed;
	for (Wall* wall : walls)
	{
		if (SDL_HasIntersection(destRect, wall->GetDestRect())) {
			destRect->x -= xvel * speed;
			break;
		}
	}

	destRect->y += yvel * speed;
	for (Wall* wall : walls)
	{
		if (SDL_HasIntersection(destRect, wall->GetDestRect())) {
			destRect->y -= yvel * speed;
			break;
		}
	}

	for (Item* item : items)
	{
		if (SDL_HasIntersection(destRect, item->GetDestRect())) {
			std::cout << "Item Pickup" << std::endl;
			items.remove(item);
			delete item;
			break; // ABSOLUTELY NECESSARY
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

bool facingRight = true;

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

enum anim {
	Idle_R	= 0,
	Idle_L	= 1,
	Run_R	= 2,
	Run_L	= 3,
	Hit_R	= 4,
	Hit_L	= 5,
	Shoot_R = 6,
	Shoot_L = 7
};

void Player::Render() {
	frameDelay = SDL_GetTicks() - frameStart;
	if (frameDelay > sheetData[row][1]) // if time to display next frame
	{
		frameStart = SDL_GetTicks();

		if (!uninterruptibleAnimation) // if NOT playing Shoot or Hit
		{
			if (xvel == 1) // if going right
			{
				facingRight = true;
				row = Run_R;
			}
			else if (xvel == -1) // if going left
			{
				facingRight = false;
				row = Run_L;
			} 
			else if (yvel != 0) // if NOT going right/left BUT going up/down
			{
				if (facingRight) // last direction the character was facing
				{
					row = Run_R;
				}
				else 
				{
					row = Run_L;
				}
			}
			else // if NOT moving at all
			{
				if (facingRight) // last direction the character was facing
				{
					row = Idle_R;
				}
				else 
				{
					row = Idle_L;
				}
			}
		}
		
		if (srcRect->y != row * PLAYERSPRITESIZE) { // if animation change happened
			frameCounter = 0;	// reset counter
			srcRect->y = row * PLAYERSPRITESIZE; // set new animation
		}
		else // if not
		{ 
			frameCounter++; // increment frames
			if (frameCounter >= sheetData[row][0]) // dont go past last frame (only need to check if incremented frames. everything has a first [0] frame)
			{
				frameCounter = 0; // return to first frame
				uninterruptibleAnimation = false; // the animation has finished
			}

		}
		srcRect->x = frameCounter * PLAYERSPRITESIZE; // finally, set the frame to display
	}

	SDL_RenderCopy(Game::renderer, objTexture, srcRect, destRect);
}

enum ProjectileDirection {
	up = 1,
	down = 2,
	right = 3,
	left = 4
};
int lookDirection = right;

void Player::SetVelX(int v) { 
	if (v == 1)
	{
		lookDirection = right;
	}
	else if (v == -1)
	{
		lookDirection = left;
	}
	xvel = v;
}

void Player::SetVelY(int v) {
	if (v == 1)
	{
		lookDirection = down;
	}
	else if (v == -1)
	{
		lookDirection = up;
	}
	yvel = v;
}

void Player::Shoot() { // no up or down shoot animation
	if (uninterruptibleAnimation) return;
	uninterruptibleAnimation = true;
	if (facingRight)
	{
		row = 6;
	}
	else 
	{
		row = 7;
	}
	GameObjectManager::CreateGameObject(GameObjectManager::projectile, destRect->x, destRect->y, lookDirection);
}

void Player::Hit() { // no up or down hit animation
	if (uninterruptibleAnimation) return;
	uninterruptibleAnimation = true;
	if (facingRight)
	{
		row = 4;
	}
	else
	{
		row = 5;
	}
}


void Player::Reset() {
	destRect->x = TileSize * PLAYERSPAWNX;
	destRect->y = TileSize * PLAYERSPAWNY;
}



