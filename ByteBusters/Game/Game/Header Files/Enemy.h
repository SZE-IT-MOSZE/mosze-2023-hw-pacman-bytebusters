#pragma once
#include "GameObject.h"
#include "Player.h"
#include "Wall.h"
#include <time.h>
#include <forward_list>


class Enemy : public GameObject {
public:
	Enemy(int x, int y, SDL_Texture* t, std::forward_list<Wall*>& w, Player* p); //!< Enemy konstruktor az enemy létrehozására
	~Enemy();

	void Update(); //!< Enemy frissítése
	void Render(); //!< Enemy renderelése

private:
	Player* player; //player is still a pointer. only lists are references
	SDL_Rect* playerRect;
	std::forward_list<Wall*>& walls;

	bool CheckLineOfSight(); //!< Azt ellenõrizzük, hogy az enemy látja-e a játékost és, hogy látó távolságon bellül van-e
	void Chase(); //!<A játékos üldözése az enemy részélõl
	void Wander(); //!< Az enemy barangolása az adot pályán 

	int xvel, yvel;

	int playerPosX, playerPosY; //!< A játékosunk pozíciója a pályán bellül
	int posX, posY;

	int visionDistance; //!< Az enemy látó távolsága

};