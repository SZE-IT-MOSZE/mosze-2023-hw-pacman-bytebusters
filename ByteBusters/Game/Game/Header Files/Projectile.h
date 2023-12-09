#pragma once
#include "Wall.h"
#include "GameObject.h"
#include <forward_list>

class Projectile : public GameObject
{
public:
	//projectile spawns centered on given position
	Projectile(int x, int y, int s, int d, SDL_Texture* t);  //!< Konstruktor, poz�ci�, ir�ny, text�ra
	~Projectile() {}; //!< Destruktor
	void Update() override; //!< Friss�t�s
	void Render() override; //!< Megjelen�t�s

private:
	int xvel, yvel; //!< Sebess�g ir�nya
	int speed; //!< Sebess�g szorz�
	const std::forward_list<std::unique_ptr<Wall>>* walls; //!< Falak list�ja

	int frame;
};
