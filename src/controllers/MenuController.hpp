#ifndef MENUCONTROLLER_HPP
#define MENUCONTROLLER_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "MouseController.hpp"
#include "../models/Maps.hpp"
#include "../views/MapVue.hpp"
#include "../utils/Observer.hpp"

using namespace std;
using namespace sf;

class MenuController: public Observer
{
private:
  static MenuController* instance;
  MenuController();
  ~MenuController();
  bool init_map = false;

  MouseController *mouseController;
  Maps *map;
  MapVue *mapVue;
  vector<RectangleShape *> carres;

public:
  static MenuController* getInstance();
  MenuController(const MenuController&) = delete;
  void operator=(const MenuController&) = delete;
  static void destroyInstance();

  bool getInitMap() { return init_map; }
  void setInitMap(bool b) { init_map = b; }
  void init(MouseController *mouseController, Maps *map, MapVue *mapVue, vector<RectangleShape *> carres);
  void update() override;
};

#endif