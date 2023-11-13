#pragma once
#include "GameObject.h"

class Wall : public GameObject 
{
public:
	Wall(int x, int y, SDL_Texture* t); 
};