#include "Wall.h"

Wall::Wall(int x, int y, int h, int w, SDL_Texture* t) {
	objTexture = t;
	destRect = new SDL_Rect;

	destRect->x = x;
	destRect->y = y;
	destRect->w = w;
	destRect->h = h;
}

Wall::~Wall() {
	delete destRect;
}