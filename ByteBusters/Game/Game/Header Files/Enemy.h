#pragma once
#include "Wall.h"
#include "Player.h"
#include "GameObject.h"
#include "Projectile.h"
#include <vector>
#include <forward_list>


class Enemy : public GameObject {
public:
	Enemy(int x, int y, int s, SDL_Texture* t); //!< Enemy konstruktor, pozíció, textúra
	virtual ~Enemy() {}; //!< Virtuális enemy destruktor

	virtual void Update() override = 0; //!< Frissítés
	void Render() override; //!< Megjelenítés

	void SendToDeathRow();

protected: 
	Player* player; //!< Player mutató
	const SDL_Rect* playerDestRect; //!< Player hitbox
	const std::forward_list<std::unique_ptr<Wall>>* walls; //!< Falak
	const std::forward_list<std::unique_ptr<Projectile>>* projectiles; //!< Player lövedékei

	int CalculateDistance(); //!< Enemy és Player távolsága
	bool CheckLineOfSight(); //!< Azt ellenõrizzük, hogy az enemy látja-e a játékost és hogy látótávolságon belül van-e
	void Wander(); //!< Enemy barangolása

	int xvel, yvel; //!< Enemy sebessége tengelyek mentén
	int speed; //!< Enemy sebesség szorzója

	SDL_Point playerPos; //!< Player pozíciója
	SDL_Point thisPos; //!< Enemy pozíciója

	int distance; //!< Távolség Enemy és Player között
	int visionDistance; //!< Enemy látótávolsága
	int attackDistance; //!< Enemy támadási távolsága

	bool uninterruptibleAnimation = false; //!< Megszakíthatalan animáció, pl.: lövés, ütés

	Uint32 frameStart;	// start of render
	int frameDelay;		// length between two renders of this object in milliseconds
	int frameCounter;	// frame counter
	int row;			// animation to display
	int newRow;			// new animation to set if different from previous
	bool facingRight;

	std::vector<std::vector<int>> enemySheetData; //!< Enemy sprite sheet adatai

private:

	enum anim { //!< Animáció kódok
		Idle_R = 0,
		Idle_L = 1,
		Run_R = 2,
		Run_L = 3,
	};

};