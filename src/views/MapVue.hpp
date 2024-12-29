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
  float size;
  vector<PieceVue *> pieces;

public:
  MapVue();
  ~MapVue();
  void init(float size, Maps &map);
  void draw(RenderWindow &window, Maps &map);
};

#endif