#pragma once
#include "SDL.h"
#include <memory>

class GameObjectManager;

class GameObject {

public:

	GameObject(int x, int y); //!< Konstruktor, poz�ci�
	virtual ~GameObject() {}; //!< Destruktor

	virtual void Update() {}; //!< �res friss�t�s, alap GameObject nem csin�l semmit
	virtual void Render(); //!< Megjelen�t�s

	const SDL_Rect* GetDestRectPtr() { return &dstRect; } //!< Hitbox
	SDL_Point GetCenterPosition(); //!< Poz�ci� meg�llap�t�sa

protected:
	int tileRes; //!< Cellam�ret
	std::weak_ptr<GameObjectManager> gom; //!< GameObjectManager el�r�s

	SDL_Rect dstRect; //!< Hitbox �s megjelen�t�si c�lpont
	SDL_Rect srcRect; //!< Sprite sheet text�ra elem

	SDL_Texture* objTexture; //!< Text�ra

};