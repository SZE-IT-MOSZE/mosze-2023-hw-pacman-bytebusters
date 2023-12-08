#pragma once
#include "Player.h"

#include "Enemy_Melee.h"
#include "Enemy_Ranged.h"
#include "Enemy_NoAttack.h"

#include "Wall.h"
#include "Item.h"
#include "Projectile.h"

#include <forward_list>
#include <set>

#include <mutex>


class GameObjectManager {
public:

	static std::shared_ptr<GameObjectManager> GetInstance(const int tR); //!< Singleton GetInstance, cellam�ret
	GameObjectManager(GameObjectManager& other) = delete; //!< T�r�lt copy konstruktor
	void operator=(const GameObjectManager&) = delete; //!< T�r�lt = oper�tor
	~GameObjectManager() {}; //!< Destruktor

	enum PlayerTypes //!< J�t�kos
	{
		player //only one texture
	};
	enum EnemyTypes //!< Ellens�g t�pusok
	{
		ape,
		deer,
		homeless,
		joseph,
		rat,
		soldier,
		yusri,
	};
	enum WallTypes //!< Fal t�pusok
	{
		concrete02,
		water,
		lava
	};
	enum ItemTypes //!< Item
	{
		item
	};
	enum ProjectileTypes //!< J�t�kos vagy Ellens�g l�ved�k
	{
		playerProjectile,
		enemyProjectile
	};
	enum Direction { //!< Ir�nyok sz�mokra k�dolva
		up = 0,
		down = 1,
		right = 2,
		left = 3
	};

	Player* CreateGameObject(PlayerTypes t, int x, int y); //!< Player l�trehoz�sa, pointer vissza ad�sa
	void CreateGameObject(EnemyTypes t, int x, int y); //!< Ellens�g l�terhoz�sa adott poz�ci�ban
	void CreateGameObject(WallTypes t, int x, int y); //!< Fal l�trehoz�sa adott poz�ci�ban
	void CreateGameObject(ItemTypes t, int x, int y); //!< Item l�trehoz�sa adott poz�ci�ban
	void CreateGameObject(ProjectileTypes t, int x, int y, int d); //!< Item l�trehoz�sa adott poz�ci�ban

	void RenderAllGameObjects(); //!< Game objektumok megjelen�t�se
	void UpdateAllGameObjects(); //!< Az objektumok friss�t�se
	void DestroyAllExceptPlayer(); //!< Az �ssze objektum t�rl�se, kiv�tel a j�t�kos

	void ResetPlayer(); //!< J�t�kos vissza�ll�t�sa alap�llapotba

	void CheckEnemyHit(int range, bool r); //!< A j�t�kos meg�t�tte-e az ellens�get, �t�s t�vols�g, ir�ny

	void FlagForDelete(Enemy* f); //!< Ellens�g megjel�l�sre t�rl�sre
	void FlagForDelete(Wall* f); //!< Fal megjel�l�sre t�rl�sre
	void FlagForDelete(Item* f); //!< Item megjel�l�sre t�rl�sre
	void FlagForDelete(Projectile* f); //!< L�ved�k megjel�l�sre t�rl�sre

	bool AreAllItemsPickedUp(); //!< Az �ssze item-et fel vette-e a j�t�kos
	
	bool AreJosephAndYusriDead(); //!< A f� ellens�gek halottak-e 

	std::forward_list<std::unique_ptr<Enemy>>*		GetEnemies() { return &enemies; } //!< Ellens�gek list�j�nak lek�r�se
	std::forward_list<std::unique_ptr<Wall>>*		GetWalls() { return &walls; } //!< Falak list�j�nak lek�r�se
	std::forward_list<std::unique_ptr<Item>>*		GetItems() { return &items; } //!< Item-ek list�j�nak lek�r�se
	std::forward_list<std::unique_ptr<Projectile>>*	GetPlayerProjectiles() { return &playerProjectiles; } //!< J�t�kos l�ved�kek list�j�nak lek�r�se
	std::forward_list<std::unique_ptr<Projectile>>*	GetEnemyProjectiles() { return &enemyProjectiles; } //!< J�t�kos l�ved�kek list�j�nak lek�r�se
	Player* GetPlayer() { return _player.get(); }  //!< J�t�kos lek�r�se

private:

	GameObjectManager(int tR); //!< Priv�t konstruktor
	static std::weak_ptr<GameObjectManager> instance_; //!< Singleton instance
	static std::mutex mutex_; //!< Thread guard

	std::unique_ptr<Player> _player; //!< J�t�kos objektum
	const SDL_Rect* playerRect; //!< J�t�kos hitbox

	Enemy* _joseph; //!< Joseph (fontos ellens�g)
	Enemy* _yusri; //!< yusri (fontos ellens�g)

	std::forward_list<std::unique_ptr<Enemy>>		enemies; //!< Ellens�gek-k list�ja 
	std::forward_list<std::unique_ptr<Wall>>		walls; //!< Falak list�ja
	std::forward_list<std::unique_ptr<Item>>		items; //!< Itemek list�ja
	std::forward_list<std::unique_ptr<Projectile>>	playerProjectiles; //!< J�t�kos l�ved�keinek list�ja
	std::forward_list<std::unique_ptr<Projectile>>	enemyProjectiles; //!< Ellens�gek l�ved�keinek list�ja

	std::set<Enemy*>				flaggedForDeleteEnemies; //!< T�rl�sre jel�lt ellens�gek
	std::set<Wall*>					flaggedForDeleteWalls; //!< T�rl�sre jel�lt falak
	std::set<Item*>					flaggedForDeleteItems; //!< T�rl�sre jel�lt item-ek
	std::set<Projectile*>			flaggedForDeleteProjectiles; //!< T�rl�sre jel�lt l�ved�kek

	void DeleteFlagged(); //!< T�rl�sre jel�lt objektumok t�rl�se

};