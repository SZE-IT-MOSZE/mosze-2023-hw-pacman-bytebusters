#pragma once
#include "GameObject.h"
#include "Player.h"
#include "Wall.h"
#include "Projectile.h"
#include <time.h>
#include <forward_list>


class Enemy : public GameObject {
public:
	Enemy(int x, int y, int s, SDL_Texture* t, std::forward_list<Wall*>& w, std::forward_list<Projectile*>& pr, Player* p); //!< Enemy konstruktor az enemy létrehozására
	~Enemy();

	void Update(); //!< Enemy frissítése
	void Render(); //!< Enemy renderelése

private: 
	Player* player; //player is still a pointer. only lists are references
	SDL_Rect* playerRect;
	std::forward_list<Wall*>& walls;
	std::forward_list<Projectile*>& projectiles;

	bool CheckLineOfSight(); //!< Azt ellenõrizzük, hogy az enemy látja-e a játékost és, hogy látó távolságon bellül van-e
	void Chase(); //!<A játékos üldözése az enemy részélõl
	void Wander(); //!< Az enemy barangolása az adott pályán 

	int xvel, yvel;
	int speed;

	int playerPosX, playerPosY; //!< A játékosunk pozíciója a pályán belül
	int posX, posY;

	int visionDistance; //!< Az enemy látó távolsága

};