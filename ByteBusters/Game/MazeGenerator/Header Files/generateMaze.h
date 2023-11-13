#pragma once

#include "createGrid.h"
#include "printGrid.h"
#include "modifyGridEdges.h"
#include "placeTetrisBlocks.h"
#include "removeEdgeAdjacentBlocks.h"
#include "writeGridToFile.h"
#include "checkReachability.h"
#include "placeTwos.h"
#include <iostream>
#include <sstream>

/**
 * @file generateMaze.h
 * @brief A generateMaze fuggveny deklaracioja.
 *
 * Deklaralja a generateMaze fuggvenyt, amely felelos palyak generalasert es
 * mentesert fajlokba.
 */

 /**
  * @brief Fuggveny prototipusa a palya generalashoz.
  *
  * Ez a fuggveny labirintusokat general különböző Tetris alakzatokbol, majd
  * ellenorzi az elerhetoseget es modositja a racs szeleit. Ha a labirintus
  * megfelelo, elmenti azt egy fajlba.
  *
  * @return Igaz, ha a labirintus generalas sikeres volt.
  */
bool generateMaze();
