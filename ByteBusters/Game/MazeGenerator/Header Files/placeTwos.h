#pragma once
#include <cstdlib>
#include <ctime>
#include <vector>


/**
 * @file placeTwos.cpp
 * @brief A placeTwos f�ggv�ny deklaracioja.
 *
 * Ez a fajl tartalmazza a placeTwos f�ggv�ny deklaraciojat, amely
 * "2"-ket helyez el veletlenszeruen egy racsban.
 */

 /**
  * @brief "2" helyez el a racsban.
  *
  * Ez a fuggveny veletlenszeruen valaszt cellakat a racsban, es elhelyezi
  * bennuk a "2" erteket, am�g el nem eri a meghatarozott szamu cellat.
  * A fuggveny celja, hogy szorasszeruen elhelyezzen ertekeket a racsban.
  *
  * @param grid Egy referencia egy 2D egesz szamokbol allo vektorra, amely a racsot kepviseli.
  */
void placeTwos(std::vector<std::vector<int>>& grid);