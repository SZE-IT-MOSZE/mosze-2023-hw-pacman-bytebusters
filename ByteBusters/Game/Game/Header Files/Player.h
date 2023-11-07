#pragma once
#include "GameObject.h"
#include <forward_list>
#include "Wall.h"
#include "Item.h"


class Player : public GameObject { //!< A j�t�kos karakter oszt�lya
public:
	Player(int x, int y, int s, SDL_Texture* t, std::forward_list<Wall*>& w, std::forward_list<Item*>& i); //!< Konstruktor ami azt mutatja, hogy a player tud a falakr�l �s az itemekr�l
	~Player();

	void Update();//!< Minden framen h�vjuk ez tartalmazza a �tk�z�s �rz�kel�st �s a j�t�kos poz�ci�j�na friss�t�s�t
	void Render();//!< Csak a j�t�kos renderel�se �s megjelen�t�se

	void SetVelX(int v); //!< A player sebess�ge az X tengelyen mozogva
	void SetVelY(int v); //!< A player sebess�ge az Y tengelyen mozogva

	/*void MoveUp(int vel);
	void MoveDown(int vel);
	void MoveRight(int vel);
	void MoveLeft(int vel);*/
	void Shoot();
	void Hit();

	void Reset(); //!< A player alap helyzetbe �ll�t�sa egy �j p�lya bet�lt�sekor

	SDL_Rect* getDestRect() { return destRect; } //!< player hitbox�nak a gettere

private:
	std::forward_list<Wall*>& walls; //!< P�lya falak list�ja
	std::forward_list<Item*>& items; //!< A gy�jthet� elemek list�ja

	int xvel; //!< X sebess�g
	int yvel; //!< Y sebess�g
	int speed;

	SDL_Rect* srcRect;
	
	bool uninterruptibleAnimation; // uninterruptible animations set this for themselves, Render() only unsets it


	Uint32 frameStart;	// start of render
	int frameDelay;		// length between two renders of this object in milliseconds
	int frameCounter;	// frame counter
	int row;			// animation to display

};