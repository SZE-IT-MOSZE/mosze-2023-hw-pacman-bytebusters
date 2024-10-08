#pragma once
//DEBUG
//#define DEBUGLEVEL
#define STARTERLEVEL 1

//game
#define WINDOWTITLE "DeerGame by ByteBusters"
#define _FPS 30
#define _UPS 30

//map
#define ROWS 15
#define COLS 20
#define MAPS 10

//speed
#define DIVIDE_BY_THIS 32

#define PLAYER_SPEED 4
#define SLOW_ENEMY_SPEED 2
#define FAST_ENEMY_SPEED 4
#define PROJECTILE_SPEED 10

//player
#define PLAYER_HP 10
#define PLAYER_SPRITE_SIZE 64
#define PLAYER_SPAWN_X 18
#define PLAYER_SPAWN_Y 13
#define PLAYER_HIT_DISTANCE 2

//projectile
#define PROJECTILE_SPRITE_SIZE 16
#define PROJECTILE_SIZE_REDUCTION 2

//enemy
#define ENEMY_SPAWN_X 1
#define ENEMY_SPAWN_Y 1
#define ENEMY_SPRITE_SIZE 64
#define VISIONDISTANCE 5
#define ATTACKDISTANCE 1

//events
#define EVENT_START 1 
#define EVENT_LOAD 2 
#define EVENT_SAVE 3 
#define EVENT_MENU 4
