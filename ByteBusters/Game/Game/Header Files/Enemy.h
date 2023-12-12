#pragma once
#include "Wall.h"
#include "Player.h"
#include "GameObject.h"
#include "Projectile.h"
#include <vector>
#include <forward_list>


class Enemy : public GameObject {
public:
	Enemy(int x, int y, int s, SDL_Texture* t); //!< Enemy konstruktor, poz�ci�, text�ra
	virtual ~Enemy() {}; //!< Virtu�lis enemy destruktor

	virtual void Update() override = 0; //!< Friss�t�s
	void Render() override; //!< Megjelen�t�s

	void SendToDeathRow();

protected: 
	Player* player; //!< Player mutat�
	const SDL_Rect* playerDestRect; //!< Player hitbox
	const std::forward_list<std::unique_ptr<Wall>>* walls; //!< Falak
	const std::forward_list<std::unique_ptr<Projectile>>* projectiles; //!< Player l�ved�kei

	int CalculateDistance(); //!< Enemy �s Player t�vols�ga
	bool CheckLineOfSight(); //!< Azt ellen�rizz�k, hogy az enemy l�tja-e a j�t�kost �s hogy l�t�t�vols�gon bel�l van-e
	void Wander(); //!< Enemy barangol�sa

	int xvel, yvel; //!< Enemy sebess�ge tengelyek ment�n
	int speed; //!< Enemy sebess�g szorz�ja

	SDL_Point playerPos; //!< Player poz�ci�ja
	SDL_Point thisPos; //!< Enemy poz�ci�ja

	int distance; //!< T�vols�g Enemy �s Player k�z�tt
	int visionDistance; //!< Enemy l�t�t�vols�ga
	int attackDistance; //!< Enemy t�mad�si t�vols�ga

	bool uninterruptibleAnimation = false; //!< Megszak�thatalan anim�ci�, pl.: l�v�s, �t�s

	Uint32 frameStart;	// start of render
	int frameDelay;		// length between two renders of this object in milliseconds
	int frameCounter;	// frame counter
	int row;			// animation to display
	int newRow;			// new animation to set if different from previous
	bool facingRight;

	std::vector<std::vector<int>> enemySheetData; //!< Enemy sprite sheet adatai

private:

	enum anim { //!< Anim�ci� k�dok
		Idle_R = 0,
		Idle_L = 1,
		Run_R = 2,
		Run_L = 3,
	};

};