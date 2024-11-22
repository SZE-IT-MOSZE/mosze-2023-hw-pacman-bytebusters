#pragma once
#ifndef CHECK_REACHABILITY_H
#define CHECK_REACHABILITY_H

#include <vector>

/**
 * @file checkReachability.h
 * @brief A checkReachability függvény deklarációja.
 *
 * Deklarálja a checkReachability függvényt, amely ellenőrzi, hogy a grid minden nullával jelölt
 * cellája elérhető-e a rács széleiről.
 */

 /**
  * @brief Függvény prototípusa egy rács elérhetőségének ellenőrzésére.
  *
  * Ez a függvény ellenőrzi, hogy a grif minden nullával jelölt cellája elérhető-e a rács széleiről.
  * A függvény DEEP FIRST SEARCH (DFS) alkalmaz a grid bejárására, megállapítva, hogy minden
  * nullás értékű cella elérhető-e anélkül, hogy át kellene menni egy nem-nullás cellán.
  *
  * @param grid Egy konstans referencia egy 2D egész számokból álló vektorra, amely maga a grid.
  * @return Igaz, ha minden nullával jelölt cella elérhető a szélekről, egyébként meg hamis.
  */
bool checkReachability(const std::vector<std::vector<int>>& grid);

#endif // CHECK_REACHABILITY_H
