#pragma once
#include "GameObject.h"
#include <forward_list>
#include "Wall.h"
#include "Item.h"
#include "Projectile.h"


class Player : public GameObject { //!< A j�t�kos karakter oszt�lya
public:
	Player(int x, int y, int s, SDL_Texture* t, std::forward_list<Wall*>& w, std::forward_list<Item*>& i, std::forward_list<Projectile*>& p); //!< Konstruktor ami azt mutatja, hogy a player tud a falakr�l �s az itemekr�l
	~Player();

	void Update() override;//!< Minden framen h�vjuk ez tartalmazza a �tk�z�s �rz�kel�st �s a j�t�kos poz�ci�j�na friss�t�s�t
	void Render() override;//!< Csak a j�t�kos renderel�se �s megjelen�t�se

	void SetVelX(int v); //!< A player sebess�ge az X tengelyen mozogva
	void SetVelY(int v); //!< A player sebess�ge az Y tengelyen mozogva

	void Shoot();
	void Hit();

	int GetHP() const { return hp; }
	void DamagePlayer();
	void Reset(); //!< A player alap helyzetbe �ll�t�sa egy �j p�lya bet�lt�sekor

	// player could have getters for posX and posY since it has to calculate it anyways

private:
	std::forward_list<Wall*>& walls; //!< P�lya falak list�ja
	std::forward_list<Item*>& items; //!< A gy�jthet� elemek list�ja
	std::forward_list<Projectile*>& projectiles; //!< A gy�jthet� elemek list�ja

	int xvel; //!< X sebess�g
	int yvel; //!< Y sebess�g
	int posX;
	int posY;
	int speed;
	int hp;
	
	bool uninterruptibleAnimation; // uninterruptible animations set this for themselves, Render() only unsets it

	Uint32 frameStart;	// start of render
	int frameDelay;		// length between two renders of this object in milliseconds
	int frameCounter;	// frame counter
	int row;			// animation to display

};