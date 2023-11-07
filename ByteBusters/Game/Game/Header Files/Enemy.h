#pragma once
#include "GameObject.h"
#include "Player.h"
#include "Wall.h"
#include "Projectile.h"
#include <time.h>
#include <forward_list>


class Enemy : public GameObject {
public:
	Enemy(int x, int y, int s, SDL_Texture* t, std::forward_list<Wall*>& w, std::forward_list<Projectile*>& pr, Player* p); //!< Enemy konstruktor az enemy l�trehoz�s�ra
	~Enemy();

	void Update(); //!< Enemy friss�t�se
	void Render(); //!< Enemy renderel�se

private: 
	Player* player; //player is still a pointer. only lists are references
	SDL_Rect* playerRect;
	std::forward_list<Wall*>& walls;
	std::forward_list<Projectile*>& projectiles;

	void CalculatePositions(); // !!!!!!!!! CALL BEFORE CalculateDistance() AND CheckLineOfSight()
	int CalculateDistance(); // easier calculation, check first instead of CheckLineOfSight()
	bool CheckLineOfSight(); // overwrites positions calculated in  CalculatePositions(), CALL LAST!!! //!< Azt ellen�rizz�k, hogy az enemy l�tja-e a j�t�kost �s, hogy l�t� t�vols�gon bell�l van-e
	void Chase(); //!<A j�t�kos �ld�z�se az enemy r�sz�l�l
	void Wander(); //!< Az enemy barangol�sa az adott p�ly�n 
	void Attack();

	int xvel, yvel;
	int speed;

	int playerPosX, playerPosY; //!< A j�t�kos poz�ci�ja a p�ly�n bel�l
	int posX, posY;

	int distance;
	int visionDistance; //!< Az enemy l�t�t�vols�ga
	int attackDistance;


	bool uninterruptibleAnimation = false; 

	Uint32 frameStart = SDL_GetTicks();	// start of render
	int frameDelay = 0;		// length between two renders of this object in milliseconds
	int frameCounter = 0;	// frame counter
	int row = 0;			// animation to display
	bool facingRight = true;

};