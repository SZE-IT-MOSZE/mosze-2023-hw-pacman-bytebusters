#include "Wall.h"
#include <iostream>

Wall::Wall(int x, int y, SDL_Texture* t) : GameObject::GameObject(x, y){
	objTexture = t;
}
