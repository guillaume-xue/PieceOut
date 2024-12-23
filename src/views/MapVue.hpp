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
  Maps *map;

public:
  MapVue(Maps *map) : map(map) { cout << "MapVue created" << endl; }
  ~MapVue() { cout << "MapVue deleted" << endl; }
  void draw(RenderWindow &window);
  void update();
};

#endif