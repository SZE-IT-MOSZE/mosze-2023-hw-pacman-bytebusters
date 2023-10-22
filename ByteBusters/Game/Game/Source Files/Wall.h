#pragma once
#include "GameObject.h"

class Wall : public GameObject {
public:
	Wall(int x, int y, int h, int w, SDL_Texture* t);
	~Wall();

};