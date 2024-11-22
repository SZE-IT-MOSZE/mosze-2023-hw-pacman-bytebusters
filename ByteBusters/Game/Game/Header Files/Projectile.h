#pragma once
#include "Wall.h"
#include "GameObject.h"
#include <forward_list>

class Projectile : public GameObject
{
public:
	//projectile spawns centered on given position
	Projectile(int x, int y, int s, int d, SDL_Texture* t);  //!< Konstruktor, pozíció, irány, textúra
	~Projectile() {}; //!< Destruktor
	void Update() override; //!< Frissítés
	void Render() override; //!< Megjelenítés

private:
	int xvel, yvel; //!< Sebesség iránya
	int speed; //!< Sebesség szorzó
	const std::forward_list<std::unique_ptr<Wall>>* walls; //!< Falak listája

	int frame;
};
