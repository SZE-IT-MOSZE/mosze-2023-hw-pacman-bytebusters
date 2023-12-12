#pragma once
#include "SDL.h"
#include <memory>

class GameObjectManager;

class GameObject {

public:

	GameObject(int x, int y); //!< Konstruktor, pozíció
	virtual ~GameObject() {}; //!< Destruktor

	virtual void Update() {}; //!< Üres frissítés, alap GameObject nem csinál semmit
	virtual void Render(); //!< Megjelenítés

	const SDL_Rect* GetDestRectPtr() { return &dstRect; } //!< Hitbox
	SDL_Point GetCenterPosition(); //!< Pozíció megállapítása

protected:
	int tileRes; //!< Cellaméret
	std::weak_ptr<GameObjectManager> gom; //!< GameObjectManager elérés

	SDL_Rect dstRect; //!< Hitbox és megjelenítési célpont
	SDL_Rect srcRect; //!< Sprite sheet textúra elem

	SDL_Texture* objTexture; //!< Textúra

};