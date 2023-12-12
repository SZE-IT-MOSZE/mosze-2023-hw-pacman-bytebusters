#pragma once
#include "Item.h"

Item::Item(int x, int y, SDL_Texture* t) : GameObject(x, y) {
	objTexture = t;
}