#pragma once
#include "GameObject.h"
#include <forward_list>
#include "Wall.h"
#include "Item.h"


class Player : public GameObject { //!< A játékos karakter osztálya
public:
	Player(int x, int y, int s, SDL_Texture* t, std::forward_list<Wall*>& w, std::forward_list<Item*>& i); //!< Konstruktor ami azt mutatja, hogy a player tud a falakról és az itemekrõl
	~Player();

	void Update();//!< Minden framen hívjuk ez tartalmazza a ütközés érzékelést és a játékos pozíciójána frissítését
	void Render();//!< Csak a játékos renderelése és megjelenítése

	void SetVelX(int v); //!< A player sebessége az X tengelyen mozogva
	void SetVelY(int v); //!< A player sebessége az Y tengelyen mozogva

	/*void MoveUp(int vel);
	void MoveDown(int vel);
	void MoveRight(int vel);
	void MoveLeft(int vel);*/
	void Shoot();
	void Hit();

	void Reset(); //!< A player alap helyzetbe állítása egy új pálya betöltésekor

	SDL_Rect* getDestRect() { return destRect; } //!< player hitboxának a gettere

private:
	std::forward_list<Wall*>& walls; //!< Pálya falak listája
	std::forward_list<Item*>& items; //!< A gyújthetõ elemek listája

	int xvel; //!< X sebesség
	int yvel; //!< Y sebesség
	int speed;

	SDL_Rect* srcRect;
	
	bool uninterruptibleAnimation; // uninterruptible animations set this for themselves, Render() only unsets it


	Uint32 frameStart;	// start of render
	int frameDelay;		// length between two renders of this object in milliseconds
	int frameCounter;	// frame counter
	int row;			// animation to display

};