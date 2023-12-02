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

Player::Player(int x, int y, int s, SDL_Texture* t, std::forward_list<Wall*>& w, std::forward_list<Item*>& i, std::forward_list<Projectile*>& p) : walls(w), items(i), projectiles(p), GameObject(x, y) {
	objTexture = t;

	std::cout << "player tile size: " << tileRes << "\n";

	xvel = 0;
	yvel = 0;

	posX = posY = 0;

	hp = 10;

	srcRect->w = srcRect->h = PLAYER_SPRITE_SIZE;

	uninterruptibleAnimation = false;

	frameStart = SDL_GetTicks();	// start of render
	frameDelay = 0;					// length between two renders of this object in milliseconds
	frameCounter = 0;				// frame counter
	row = 0;						// animation to display

	speed = s * tileRes/DIVIDE_BY_THIS;
}

Player::~Player() {
	std::cout << "player destructor called" << std::endl;
}


void Player::Update() {

	//place enemy collision/hit check above here

	for (Projectile* projectile : projectiles)
	{
		if (SDL_HasIntersection(destRect, projectile->GetDestRect())) {
			if (auto lockedPtr = gom.lock())
			{
				lockedPtr->FlagForDelete(projectile);
			}
			else
			{
				std::cout << "ATTENTION!!! GAMEOBJECT EXISTS WITHOUT MANAGER!!! \n";
			}
			DamagePlayer();
			break;
		}
	}

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
			//std::cout << "Item Pickup" << std::endl;
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

int sheetData[10][2] = {
	{5, 200},
	{5, 200},
	{3, 200},
	{3, 200},
	{7, 50},
	{7, 50},
	{5, 100},
	{5, 100}, // 5 * 100 = 500
	{3, 166}, // ? * 3 = 500 
	{3, 166}, // ? = 166.666...
};

enum anim {
	Idle_R	= 0,
	Idle_L	= 1,
	Run_R	= 2,
	Run_L	= 3,
	Hit_R	= 4,
	Hit_L	= 5,
	Shoot_R = 6,
	Shoot_L = 7,
	Shoot_D = 8,
	Shoot_U = 9
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
		
		if (srcRect->y != row * PLAYER_SPRITE_SIZE) { // if animation change happened
			frameCounter = 0;	// reset counter
			srcRect->y = row * PLAYER_SPRITE_SIZE; // set new animation
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
		srcRect->x = frameCounter * PLAYER_SPRITE_SIZE; // finally, set the frame to display
	}

	SDL_RenderCopy(Game::renderer, objTexture, srcRect, destRect);
}

enum Direction { // note: this is not the direction specified in projectile
	up = 0,
	down = 1,
	right = 2,
	left = 3
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

void Player::Shoot() {
	posX = destRect->x + destRect->w / 2;
	posY = destRect->y + destRect->h / 2;

	if (uninterruptibleAnimation) return;
	uninterruptibleAnimation = true;
	switch (lookDirection)
	{
	case up:
		//std::cout << "shoot up" << std::endl;
		row = Shoot_U;
		ShootProjectile(Projectile::up);
		break;
	case down:
		//std::cout << "shoot down" << std::endl;
		row = Shoot_D;
		ShootProjectile(Projectile::down);
		break;
	case left:
		//std::cout << "shoot left" << std::endl;
		row = Shoot_L;
		ShootProjectile(Projectile::left);
		break;
	case right:
		//std::cout << "shoot right" << std::endl;
		row = Shoot_R;
		ShootProjectile(Projectile::right);
		break;
	default:
		break;
	}
	
}

void Player::ShootProjectile(int d) {
	if (auto lockedPtr = gom.lock())
	{
		lockedPtr->CreateGameObject(GameObjectManager::enemyProjectile, posX, posY, d);
	}
	else
	{
		std::cout << "ATTENTION!!! GAMEOBJECT EXISTS WITHOUT MANAGER!!! \n";
	}
}

void Player::Hit() { // no up or down hit animation
	if (uninterruptibleAnimation) return;
	uninterruptibleAnimation = true;
	if (facingRight)
	{
		row = Hit_R;
	}
	else
	{
		row = Hit_L;
	}
	if (auto lockedPtr = gom.lock())
	{
		lockedPtr->CheckEnemyHit(destRect->x + destRect->w / 2, destRect->y + destRect->y / 2, 2 * tileRes, facingRight);
	}
	else
	{
		std::cout << "ATTENTION!!! GAMEOBJECT EXISTS WITHOUT MANAGER!!! \n";
	}
}


void Player::DamagePlayer() {
	--hp;
	std::cout << "Health Points: " << hp << std::endl;
}

void Player::Reset() {
	destRect->x = tileRes * PLAYER_SPAWN_X;
	destRect->y = tileRes * PLAYER_SPAWN_Y;
	hp = 10;
}



