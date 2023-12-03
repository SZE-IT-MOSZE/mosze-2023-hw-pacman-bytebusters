#pragma once
#include "GameObject.h"
#include "Player.h"
#include "Wall.h"
#include "Projectile.h"
#include <forward_list>
#include <vector>


class Enemy : public GameObject {
public:
	Enemy(int x, int y, int s, SDL_Texture* t); //!< Enemy konstruktor az enemy létrehozására
	virtual ~Enemy();

	virtual void Update() override = 0; //!< Enemy frissítése
	void Render() override; //!< Enemy renderelése

protected: 
	Player* player; // this should be const too
	const SDL_Rect* playerRect;
	const std::forward_list<std::unique_ptr<Wall>>* walls;
	const std::forward_list<std::unique_ptr<Projectile>>* projectiles;

	int CalculateDistance(); // easier calculation, check first instead of CheckLineOfSight()
	bool CheckLineOfSight(); // overwrites positions calculated in CalculatePositions(), CALL LAST!!! //!< Azt ellenõrizzük, hogy az enemy látja-e a játékost és, hogy látó távolságon bellül van-e
	void Wander(); //!< Az enemy barangolása az adott pályán 

	int xvel, yvel;
	int speed;

	SDL_Point playerPos;
	SDL_Point thisPos;

	int distance;
	int visionDistance; //!< Az enemy látótávolsága
	int attackDistance;

	bool uninterruptibleAnimation = false; 

	Uint32 frameStart;	// start of render
	int frameDelay;		// length between two renders of this object in milliseconds
	int frameCounter;	// frame counter
	int row;			// animation to display
	bool facingRight;

	//int(*enemySheetData)[2];

	std::vector<std::vector<int>> enemySheetData;

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
		>runaway


*/
//