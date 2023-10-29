#pragma once
#include "GameObject.h"
#include <forward_list>
#include "Wall.h"
#include "Item.h"


class Player : public GameObject {
public:
	Player(int x, int y, SDL_Texture* t, std::forward_list<Wall*>& w, std::forward_list<Item*>& i);
	~Player();

	void Update();
	void Render();

	void SetVelX(int v);
	void SetVelY(int v);

	void Reset();

	SDL_Rect* getDestRect() { return destRect; }

private:
	std::forward_list<Wall*>& walls;
	std::forward_list<Item*>& items;

	int xvel;
	int yvel;

};