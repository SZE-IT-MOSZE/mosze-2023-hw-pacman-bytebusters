#pragma once
#include "Map.h"
#include "Game.h"
#include "Player.h"
#include "Defines.h"
#include "TextureManager.h"
#include "GameObjectManager.h"
#include <iostream>

Player::Player(int x, int y, int s, SDL_Texture* t) : GameObject(x, y) {

	objTexture = t;

	//hitbox.x = x + (tileRes / 100 * (HITBOX_SIZE_REDUCTION_PERCENT / 2));
	//hitbox.w = tileRes - (tileRes / 100 * HITBOX_SIZE_REDUCTION_PERCENT);
	//hitbox.y = y + (tileRes / 100 * (HITBOX_SIZE_REDUCTION_PERCENT / 2));
	//hitbox.h = tileRes - (tileRes / 100 * HITBOX_SIZE_REDUCTION_PERCENT);

	lookDirection = GameObjectManager::left;
	facingRight = false;

	walls = nullptr;
	projectiles = nullptr;
	items = nullptr;

	if (auto lockedPtr = gom.lock())
	{
		walls = lockedPtr->GetWalls();
		projectiles = lockedPtr->GetEnemyProjectiles();
		items = lockedPtr->GetItems();
	}

	xvel = 0;
	yvel = 0;
	hp = 10;

	srcRect.w = srcRect.h = PLAYER_SPRITE_SIZE;

	uninterruptibleAnimation = false;

	frameStart = SDL_GetTicks();	
	frameDelay = 0;					
	frameCounter = 0;				
	row = 0;						
	newRow = 0;						

	speed = s * tileRes/DIVIDE_BY_THIS;

	sheetData = {
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
}

void Player::Update() {

	for (auto& projectile : *projectiles)
	{
		if (SDL_HasIntersection(&dstRect, projectile->GetDestRectPtr())) {
			if (auto lockedPtr = gom.lock())
			{
				lockedPtr->FlagForDelete(projectile.get());
			}
			DamagePlayer();
			break;
		}
	}

	if (uninterruptibleAnimation) return; // if an uninterruptible animation is playing the character does not move
		
	dstRect.x += xvel * speed;
	for (auto& wall : *walls)
	{
		if (SDL_HasIntersection(&dstRect, wall->GetDestRectPtr())) {
			dstRect.x -= xvel * speed;
			break;
		}
	}

	dstRect.y += yvel * speed;
	for (auto& wall : *walls)
	{
		if (SDL_HasIntersection(&dstRect, wall->GetDestRectPtr())) {
			dstRect.y -= yvel * speed;
			break;
		}
	}

	for (auto& item : *items)
	{
		if (SDL_HasIntersection(&dstRect, item->GetDestRectPtr())) {
			if (auto lockedPtr = gom.lock())
			{
				lockedPtr->FlagForDelete(item.get());
			}
			break;
		}
	}
}

void Player::Render() {
	frameDelay = SDL_GetTicks() - frameStart;

	//facingRight set in SetVelX();
	if (!uninterruptibleAnimation) { // if there is no uninterruptible animation
		if (xvel == 0 && yvel == 0) // if standing still
		{
			if (facingRight) // faced right last time
			{
				newRow = Idle_R;
			}
			else // faced left last time
			{
				newRow = Idle_L;
			}
		}
		else // if moving
		{
			if (facingRight) // faced right last time
			{
				newRow = Run_R;
			}
			else // faced left last time
			{
				newRow = Run_L;
			}
		}
	}

	//if (!uninterruptibleAnimation) // if NOT playing Shoot or Hit
	//{
	//	//if (xvel == 1) // if going right
	//	//{
	//	//	facingRight = true;
	//	//	newRow = Run_R;
	//	//}
	//	//else if (xvel == -1) // if going left
	//	//{
	//	//	facingRight = false;
	//	//	newRow = Run_L;
	//	//}
	//	//else if (yvel != 0) // if NOT going right/left BUT going up/down
	//	//{
	//	//	if (facingRight) // last direction the character was facing
	//	//	{
	//	//		newRow = Run_R;
	//	//	}
	//	//	else
	//	//	{
	//	//		newRow = Run_L;
	//	//	}
	//	//}
	//	//else // if NOT moving at all
	//	//{
	//	//	if (facingRight) // last direction the character was facing
	//	//	{
	//	//		newRow = Idle_R;
	//	//	}
	//	//	else
	//	//	{
	//	//		newRow = Idle_L;
	//	//	}
	//	//}
	//}

	if (frameDelay > sheetData[row][1] || newRow != row) // if time to display next frame OR a change has happened
	{
		frameStart = SDL_GetTicks();

		if (newRow != row) { // if animation change happened
			row = newRow; // set new row
			frameCounter = 0;	// reset counter
			srcRect.y = row * PLAYER_SPRITE_SIZE; // set new animation
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
		srcRect.x = frameCounter * PLAYER_SPRITE_SIZE; // finally, set the frame to display
	}

	SDL_RenderDrawRect(Game::renderer, &dstRect);
	SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &dstRect);
}

void Player::SetVelX(int v) { 
	if (v == 1)
	{
		facingRight = true;
		lookDirection = GameObjectManager::right;
	}
	else if (v == -1)
	{
		facingRight = false;
		lookDirection = GameObjectManager::left;
	}
	xvel = v;
}

void Player::SetVelY(int v) {
	if (v == 1)
	{
		lookDirection = GameObjectManager::down;
	}
	else if (v == -1)
	{
		lookDirection = GameObjectManager::up;
	}
	yvel = v;
}

void Player::Shoot() {
	if (uninterruptibleAnimation) return;
	uninterruptibleAnimation = true;

	switch (lookDirection)
	{
	case GameObjectManager::up:
		//std::cout << "shoot up" << std::endl;
		newRow = Shoot_U;
		ShootProjectile(GameObjectManager::up);
		break;
	case GameObjectManager::down:
		//std::cout << "shoot down" << std::endl;
		newRow = Shoot_D;
		ShootProjectile(GameObjectManager::down);
		break;
	case GameObjectManager::left:
		//std::cout << "shoot left" << std::endl;
		newRow = Shoot_L;
		ShootProjectile(GameObjectManager::left);
		break;
	case GameObjectManager::right:
		//std::cout << "shoot right" << std::endl;
		newRow = Shoot_R;
		ShootProjectile(GameObjectManager::right);
		break;
	default:
		break;
	}
	
}

void Player::ShootProjectile(int d) {
	if (auto lockedPtr = gom.lock())
	{
		SDL_Point pos = GetCenterPosition();

		std::cout << "player X: " << pos.x << "\n";
		std::cout << "player Y: " << pos.y << "\n";

		lockedPtr->CreateGameObject(GameObjectManager::playerProjectile, pos.x, pos.y, d);

	}
}

void Player::Hit() { // no up or down hit animation
	if (uninterruptibleAnimation) return;
	uninterruptibleAnimation = true;

	if (facingRight)
	{
		newRow = Hit_R;
	}
	else
	{
		newRow = Hit_L;
	}
	if (auto lockedPtr = gom.lock())
	{
		lockedPtr->CheckEnemyHit(PLAYER_HIT_DISTANCE * tileRes, facingRight);
	}
}


void Player::DamagePlayer() {
	--hp;
}

void Player::Reset() {
	dstRect.x = tileRes * PLAYER_SPAWN_X;
	dstRect.y = tileRes * PLAYER_SPAWN_Y;
	//hitbox.x = (tileRes * PLAYER_SPAWN_X) + (tileRes / 100 * (HITBOX_SIZE_REDUCTION_PERCENT / 2));
	//hitbox.y = (tileRes * PLAYER_SPAWN_Y) + (tileRes / 100 * (HITBOX_SIZE_REDUCTION_PERCENT / 2));
	hp = 10;
}



