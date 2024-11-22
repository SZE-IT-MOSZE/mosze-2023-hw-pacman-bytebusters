
//#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN // To run tests uncomment this

#ifdef DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#pragma once
#include "doctest.h"
#include "GameObjectManager.h"
#include "Defines.h"
#include "Player.h"
#include "SDL.h"

TEST_CASE("PlayerPosition") {
	std::shared_ptr<GameObjectManager> gom = GameObjectManager::GetInstance(32);
	Player* player1 = gom->CreateGameObject(GameObjectManager::player, 0, 0);
	REQUIRE(player1->GetDestRectPtr()->x == 0);
	REQUIRE(player1->GetDestRectPtr()->y == 0);
}

TEST_CASE("GameobjectCenter") {
	int tileRes = 64;
	std::shared_ptr<GameObjectManager> gom = GameObjectManager::GetInstance(tileRes);
	Player* player1 = gom->CreateGameObject(GameObjectManager::player, 0, 0);
	SDL_Point pos = player1->GetCenterPosition();
	REQUIRE(pos.x == tileRes / 2);
	REQUIRE(pos.y == tileRes / 2);
}

TEST_CASE("PlayerHP") {
	std::shared_ptr<GameObjectManager> gom = GameObjectManager::GetInstance(32);
	Player* player1 = gom->CreateGameObject(GameObjectManager::player, 0, 0);
	REQUIRE(player1->GetHP() == PLAYER_HP);
	player1->Reset();
	REQUIRE(player1->GetHP() == PLAYER_HP);
}

TEST_CASE("PlayerGetsDamaged") {
	std::shared_ptr<GameObjectManager> gom = GameObjectManager::GetInstance(32);
	Player* player1 = gom->CreateGameObject(GameObjectManager::player, 0, 0);
	REQUIRE(player1->GetHP() == PLAYER_HP);
	player1->DamagePlayer();
	REQUIRE(player1->GetHP() == PLAYER_HP-1);
}

TEST_CASE("ProgressionConditions") {
	std::shared_ptr<GameObjectManager> gom = GameObjectManager::GetInstance(32);
	REQUIRE(gom->AreAllItemsPickedUp() == true);
	REQUIRE(gom->AreJosephAndYusriDead() == true);
	gom->CreateGameObject(GameObjectManager::yusri, 0, 0);
	gom->CreateGameObject(GameObjectManager::joseph, 0, 0);
	gom->CreateGameObject(GameObjectManager::item, 0, 0);
	REQUIRE(gom->AreAllItemsPickedUp() == false);
	REQUIRE(gom->AreJosephAndYusriDead() == false);
}

#endif // DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN