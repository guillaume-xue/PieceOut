#ifndef MENUCONTROLLER_HPP
#define MENUCONTROLLER_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "MouseController.hpp"
#include "../models/Maps.hpp"
#include "../views/MapVue.hpp"

using namespace std;
using namespace sf;

class MenuController
{
private:
  bool init_map = false;

public:
  MenuController();
  ~MenuController();
  void update(MouseController mouseController, vector<RectangleShape *> carres, Maps &map, MapVue &mapVue);
  bool getInitMap() { return init_map; }
  void setInitMap(bool b) { init_map = b; }
};

#endif