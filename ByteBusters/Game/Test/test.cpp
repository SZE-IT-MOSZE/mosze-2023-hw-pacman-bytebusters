#include <gtest/gtest.h>
#include "Player.h"
#include "Map.h"
#include "GameObjectManager.h"

TEST(PlayerTest1, PlayerPosition) { // A player elhelyezésének ellenõrzése

	Player* player1 = GameObjectManager::CreateGameObject(GameObjectManager::player, 0, 0);
	EXPECT_EQ(player1->GetDestRect()->x, 0 );
	EXPECT_EQ(player1->GetDestRect()->y, 0 );
	delete player1;
}

TEST(PlayerTest2, PlayerHP) { // A player HP ellenõrzése

	Player* player1 = GameObjectManager::CreateGameObject(GameObjectManager::player, 0, 0);
	EXPECT_EQ(player1->GetHP(), 10);
	delete player1;
	
}

TEST(PlayerTest3, PlayerDamageTest) {
	Player* player1 = GameObjectManager::CreateGameObject(GameObjectManager::player, 0, 0);
	player1->DamagePlayer();
	EXPECT_EQ(player1->GetHP(), 9);
	delete player1;
}

TEST(GameObjectTest, GameObjectDestroyTest) { // Objektum állapot ellenõrzés
	GameObjectManager::CreateGameObject(GameObjectManager::homeless, 0, 0);
	GameObjectManager::CreateGameObject(GameObjectManager::soldier, 0, 0);
	GameObjectManager::CreateGameObject(GameObjectManager::joseph, 0, 0);
	GameObjectManager::CreateGameObject(GameObjectManager::item, 0, 0);
	GameObjectManager::CreateGameObject(GameObjectManager::concrete02, 0, 0);
	GameObjectManager::CreateGameObject(GameObjectManager::playerProjectile, 0, 0, 0);
	GameObjectManager::CreateGameObject(GameObjectManager::enemyProjectile, 0, 0, 0);
	GameObjectManager::DestroyAllExceptPlayer();
	
	EXPECT_TRUE(GameObjectManager::AreAllListsEmpty());
}

TEST(MapTest, MapTileTest) { // Map osztály ellenõrzése, hogy jó e a Tile
	Map::Innit(32);
	EXPECT_EQ(Map::GetTileSize(), 32);
	Map::Clean();

}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
