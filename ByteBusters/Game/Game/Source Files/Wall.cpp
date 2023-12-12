#pragma once
#include "Wall.h"

Wall::Wall(int x, int y, SDL_Texture* t) : GameObject(x, y){
	objTexture = t;
}
