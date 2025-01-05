#ifndef __MAPVUE_HPP
#define __MAPVUE_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include "../models/Maps.hpp"
#include "PieceVue.hpp"

using namespace std;
using namespace sf;

class MapVue
{
private:
  int GLOBAL_MARGIN_X, GLOBAL_MARGIN_Y, MARGIN_CARRE = 20;
  float SIZE_CARRE;

  vector<PieceVue *> pieces;

public:
  MapVue();
  ~MapVue();
  void init(float size, Maps &map);
  void draw(RenderWindow &window, Maps &map);
  vector<PieceVue *> getPieces() { return pieces; }
  int getGlobalMarginX() { return GLOBAL_MARGIN_X; }
  int getGlobalMarginY() { return GLOBAL_MARGIN_Y; }
  int getSizeCarre() { return SIZE_CARRE; }
  int getMarginCarre() { return MARGIN_CARRE; }
  void clear();
};

#endif