#pragma once
#include "GameObject.h"

class Item : public GameObject
{
public:
	Item(int x, int y, SDL_Texture* t);
};
