#pragma once
#include "GameObject.h"
#include "Player.h"

class Item : public GameObject
{
public:
	Item(int x, int y, SDL_Texture* t, Player* p);
	~Item();
	void Update();

private:
	Player* player;
	SDL_Rect* playerRect;
};
