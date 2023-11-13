#pragma once
#include "GameObject.h"
#include "Player.h"
#include "Wall.h"
#include "Projectile.h"
#include <forward_list>


class Enemy : public GameObject {
public:
	Enemy(int x, int y, int s, SDL_Texture* t, std::forward_list<Wall*>& w, std::forward_list<Projectile*>& pr, Player* p); //!< Enemy konstruktor az enemy l�trehoz�s�ra
	~Enemy();

	virtual void Update(); //!< Enemy friss�t�se
	void Render(); //!< Enemy renderel�se

protected: 
	Player* player; //player is still a pointer. only lists are references
	SDL_Rect* playerRect;
	std::forward_list<Wall*>& walls;
	std::forward_list<Projectile*>& projectiles;

	void CalculatePositions(); // !!!!!!!!! CALL BEFORE CalculateDistance() AND CheckLineOfSight()
	int CalculateDistance(); // easier calculation, check first instead of CheckLineOfSight()
	bool CheckLineOfSight(); // overwrites positions calculated in CalculatePositions(), CALL LAST!!! //!< Azt ellen�rizz�k, hogy az enemy l�tja-e a j�t�kost �s, hogy l�t� t�vols�gon bell�l van-e
	void Wander(); //!< Az enemy barangol�sa az adott p�ly�n 

	int xvel, yvel;
	int speed;

	int playerPosX, playerPosY; //!< A j�t�kos poz�ci�ja a p�ly�n bel�l
	int posX, posY;

	int distance;
	int visionDistance; //!< Az enemy l�t�t�vols�ga
	int attackDistance;

	bool uninterruptibleAnimation = false; 

	Uint32 frameStart;	// start of render
	int frameDelay;		// length between two renders of this object in milliseconds
	int frameCounter;	// frame counter
	int row;			// animation to display
	bool facingRight;

	int(*enemySheetData)[2];

private:

	enum anim {
		Idle_R = 0,
		Idle_L = 1,
		Run_R = 2,
		Run_L = 3,
	};

};

/*
base enemy - should include wander
	>Enemy_MeleeAttack
		>wander
		>chase
		>attack
	>Enemy_RangedAttack 
		>wander
		>shoot (attack but different)
	>Enemy_NoAttack
		>wander
		>runaway (chase but different)


*/
//