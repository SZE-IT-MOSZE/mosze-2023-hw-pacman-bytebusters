#pragma once
#include "GameObject.h"
#include "Player.h"
#include "Wall.h"
#include <time.h>
#include <forward_list>


class Enemy : public GameObject {
public:
	Enemy(int x, int y, SDL_Texture* t, std::forward_list<Wall*>& w, Player* p); //!< Enemy konstruktor az enemy l�trehoz�s�ra
	~Enemy();

	void Update(); //!< Enemy friss�t�se
	void Render(); //!< Enemy renderel�se

private:
	Player* player; //player is still a pointer. only lists are references
	SDL_Rect* playerRect;
	std::forward_list<Wall*>& walls;

	bool CheckLineOfSight(); //!< Azt ellen�rizz�k, hogy az enemy l�tja-e a j�t�kost �s, hogy l�t� t�vols�gon bell�l van-e
	void Chase(); //!<A j�t�kos �ld�z�se az enemy r�sz�l�l
	void Wander(); //!< Az enemy barangol�sa az adot p�ly�n 

	int xvel, yvel;

	int playerPosX, playerPosY; //!< A j�t�kosunk poz�ci�ja a p�ly�n bell�l
	int posX, posY;

	int visionDistance; //!< Az enemy l�t� t�vols�ga

};