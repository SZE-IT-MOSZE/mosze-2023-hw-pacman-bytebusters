#pragma once
#include "GameObject.h"
#include <forward_list>
#include "Wall.h"
#include "Item.h"
#include "Projectile.h"
#include <vector>


class Player : public GameObject { //!< A játékos karakter osztálya
public:
	Player(int x, int y, int s, SDL_Texture* t); //!< Konstruktor, pozíció, sebesség
	~Player() {};

	void Update() override;//!< Frissítés
	void Render() override;//!< Megjelenítés

	void SetVelX(int v); //!< Sebesség iránya X tengelyen
	void SetVelY(int v); //!< Sebesség iránya Y tengelyen

	void Shoot(); //!< Lövés
	void Hit(); //!< Ütés

	int GetHP() const { return hp; } //!< Player HP lekérdezése
	void DamagePlayer(); //!< Player sebzése Enemy által
	void Reset(); //!< A Player alaphelyzetbe állítása

private:
	const std::forward_list<std::unique_ptr<Wall>>* walls; //!< Falak listája
	const std::forward_list<std::unique_ptr<Item>>* items; //!< Item-eek listája
	const std::forward_list<std::unique_ptr<Projectile>>* projectiles; //!< Enemy lövedékek listája

	int xvel; //!< Sebesség X tengelyen
	int yvel; //!< Sebesség Y tengelyen
	int speed; //!< Sebesség szorzó
	int hp; //!< Életpontok

	// uninterruptible animations set this for themselves, Render() only unsets it
	bool uninterruptibleAnimation; //!< Megszakíthatalan animáció, pl.: lövés, ütés

	int lookDirection; //!< Merre néz a játékos

	Uint32 frameStart;	// start of render
	int frameDelay;		// length between two renders of this object in milliseconds
	int frameCounter;	// frame counter
	int row;			// animation to display
	int newRow;			// new animation to set if different from previous

	void ShootProjectile(int d); //!< Lövés adott irányba

	bool facingRight; //!< Jobbra néz-e a játékos

	std::vector<std::vector<int>> sheetData; 

	enum anim {
		Idle_R = 0,
		Idle_L = 1,
		Run_R = 2,
		Run_L = 3,
		Hit_R = 4,
		Hit_L = 5,
		Shoot_R = 6,
		Shoot_L = 7,
		Shoot_D = 8,
		Shoot_U = 9
	};

};