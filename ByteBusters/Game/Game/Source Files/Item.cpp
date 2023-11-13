#pragma once
#include "Item.h"
#include <iostream>
#include "Game.h"
#include "Defines.h"


Item::Item(int x, int y, SDL_Texture* t) : GameObject(x, y) {
	objTexture = t;
}