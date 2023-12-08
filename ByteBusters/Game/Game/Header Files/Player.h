#pragma once
#include "GameObject.h"
#include <forward_list>
#include "Wall.h"
#include "Item.h"
#include "Projectile.h"
#include <vector>


class Player : public GameObject { //!< A j�t�kos karakter oszt�lya
public:
	Player(int x, int y, int s, SDL_Texture* t); //!< Konstruktor, poz�ci�, sebess�g
	~Player() {};

	void Update() override;//!< Friss�t�s
	void Render() override;//!< Megjelen�t�s

	void SetVelX(int v); //!< Sebess�g ir�nya X tengelyen
	void SetVelY(int v); //!< Sebess�g ir�nya Y tengelyen

	void Shoot(); //!< L�v�s
	void Hit(); //!< �t�s

	int GetHP() const { return hp; } //!< Player HP lek�rdez�se
	void DamagePlayer(); //!< Player sebz�se Enemy �ltal
	void Reset(); //!< A Player alaphelyzetbe �ll�t�sa

private:
	const std::forward_list<std::unique_ptr<Wall>>* walls; //!< Falak list�ja
	const std::forward_list<std::unique_ptr<Item>>* items; //!< Item-eek list�ja
	const std::forward_list<std::unique_ptr<Projectile>>* projectiles; //!< Enemy l�ved�kek list�ja

	int xvel; //!< Sebess�g X tengelyen
	int yvel; //!< Sebess�g Y tengelyen
	int speed; //!< Sebess�g szorz�
	int hp; //!< �letpontok

	// uninterruptible animations set this for themselves, Render() only unsets it
	bool uninterruptibleAnimation; //!< Megszak�thatalan anim�ci�, pl.: l�v�s, �t�s

	int lookDirection; //!< Merre n�z a j�t�kos

	Uint32 frameStart;	// start of render
	int frameDelay;		// length between two renders of this object in milliseconds
	int frameCounter;	// frame counter
	int row;			// animation to display
	int newRow;			// new animation to set if different from previous

	void ShootProjectile(int d); //!< L�v�s adott ir�nyba

	bool facingRight; //!< Jobbra n�z-e a j�t�kos

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