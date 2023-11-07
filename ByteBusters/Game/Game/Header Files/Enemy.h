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

	void CalculatePositions(); // !!!!!!!!! CALL BEFORE CalculateDistance() AND CheckLineOfSight()
	int CalculateDistance(); // easier calculation, check first instead of CheckLineOfSight()
	bool CheckLineOfSight(); // overwrites positions calculated in  CalculatePositions(), CALL LAST!!! //!< Azt ellenõrizzük, hogy az enemy látja-e a játékost és, hogy látó távolságon bellül van-e
	void Chase(); //!<A játékos üldözése az enemy részélõl
	void Wander(); //!< Az enemy barangolása az adott pályán 
	void Attack();

	int xvel, yvel;
	int speed;

	int playerPosX, playerPosY; //!< A játékos pozíciója a pályán belül
	int posX, posY;

	int distance;
	int visionDistance; //!< Az enemy látótávolsága
	int attackDistance;


	bool uninterruptibleAnimation = false; 

	Uint32 frameStart = SDL_GetTicks();	// start of render
	int frameDelay = 0;		// length between two renders of this object in milliseconds
	int frameCounter = 0;	// frame counter
	int row = 0;			// animation to display
	bool facingRight = true;

};