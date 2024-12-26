#ifndef __MAPVUE_HPP
#define __MAPVUE_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include "../models/Maps.hpp"

using namespace std;
using namespace sf;

class MapVue
{
private:
  int pos_x, pos_y;
  float size;

public:
  MapVue(int pos_x, int pos_y, float size);
  ~MapVue();
  void draw(RenderWindow &window, Maps &map);
};

#endif