#pragma once
#include "GameObject.h"
#include "Player.h"
#include "Wall.h"
#include "Projectile.h"
#include <forward_list>


class Enemy : public GameObject {
public:
	Enemy(int x, int y, int s, SDL_Texture* t, std::forward_list<Wall*>& w, std::forward_list<Projectile*>& pr, Player* p); //!< Enemy konstruktor az enemy létrehozására
	~Enemy();

	virtual void Update(); //!< Enemy frissítése
	void Render(); //!< Enemy renderelése

protected: 
	Player* player; //player is still a pointer. only lists are references
	SDL_Rect* playerRect;
	std::forward_list<Wall*>& walls;
	std::forward_list<Projectile*>& projectiles;

	void CalculatePositions(); // !!!!!!!!! CALL BEFORE CalculateDistance() AND CheckLineOfSight()
	int CalculateDistance(); // easier calculation, check first instead of CheckLineOfSight()
	bool CheckLineOfSight(); // overwrites positions calculated in CalculatePositions(), CALL LAST!!! //!< Azt ellenõrizzük, hogy az enemy látja-e a játékost és, hogy látó távolságon bellül van-e
	void Wander(); //!< Az enemy barangolása az adott pályán 

	int xvel, yvel;
	int speed;

	int playerPosX, playerPosY; //!< A játékos pozíciója a pályán belül
	int posX, posY;

	int distance;
	int visionDistance; //!< Az enemy látótávolsága
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