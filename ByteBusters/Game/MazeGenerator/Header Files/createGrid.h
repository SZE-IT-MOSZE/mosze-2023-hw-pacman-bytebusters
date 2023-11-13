#pragma once
#ifndef CREATE_GRID_H
#define CREATE_GRID_H

#include <vector>

/**
 * @file createGrid.h
 * @brief A createGrid f�ggv�ny deklar�ci�ja.
 *
 * Deklar�lja a createGrid f�ggv�nyt, amely egy 2D r�cs l�trehoz�s�ra szolg�l.
 */

 /**
  * @brief F�ggv�ny protot�pusa egy 2D r�cs l�trehoz�s�hoz.
  *
  * Ez a f�ggv�ny egy k�t dimenzi�s vektort (grid) hoz l�tre a megadott
  * sorok (a) �s oszlopok (b) sz�m�val. A r�cs minden eleme kezdetben null�ra
  * van �ll�tva.
  *
  * @param a A r�cs sorainak sz�ma.
  * @param b A r�cs oszlopainak sz�ma.
  * @return 2D eg�sz sz�mokb�l �ll� vektor, amely a r�csot k�pviseli,
  * m�retei a x b, �s minden eleme null�ra van inicializ�lva.
  */
std::vector<std::vector<int>> createGrid(int a, int b);

#endif // CREATE_GRID_H
