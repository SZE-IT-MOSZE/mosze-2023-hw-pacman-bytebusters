#pragma once

#include "Player.h"
#include "TextureManager.h"
#include "Map.h"
#include "Game.h"
#include <iostream>
#include "GameObjectManager.h"

#define SPRITESIZE 64

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
	objTexture = t;

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


bool uninterruptibleAnimation = false; // uninterruptible animations set this for themselfves, Render() only unsets it
void Player::Update() {

	//place enemy collision/hit check above here

	if (uninterruptibleAnimation) return; // if an uninterruptible animation is playing the character does not move
		
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

Uint32 frameStart = SDL_GetTicks();	// start of render
int frameDelay = 0;					// length between two renders of this object in milliseconds
int i = 0;							// frame counter
int row = 0;						// animation to display

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
		
		if (srcRect->y != row * SPRITESIZE) { // if animation change happened
			i = 0;	// reset counter
			srcRect->y = row * SPRITESIZE; // set new animation
		}
		else // if not
		{ 
			i++; // increment frames
			if (i >= sheetData[row][0]) // dont go past last frame (only need to check if incremented frames. everything has a first [0] frame)
			{
				i = 0; // return to first frame
				uninterruptibleAnimation = false; // the animation has finished
			}

		}
		srcRect->x = i * SPRITESIZE; // finally, set the frame to display
	}

	SDL_RenderCopy(Game::renderer, objTexture, srcRect, destRect);
}

void Player::SetVelX(int v) { 
	xvel = v;
}

void Player::SetVelY(int v) {
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
	GameObjectManager::CreateGameObject(GameObjectManager::projectile, destRect->x, destRect->y, 1);
}

void Player::Hit() { // no up or down hit animation
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



