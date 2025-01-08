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
  static MenuController* instance;
  MenuController() {
    cout << "MenuController created" << endl;
  };
  ~MenuController() {
    cout << "MenuController deleted" << endl;
  };
  bool init_map = false;

  

public:
  static MenuController* getInstance();
  MenuController(const MenuController&) = delete;
  void operator=(const MenuController&) = delete;
  static void destroyInstance();

  void update(MouseController *mouseController, vector<RectangleShape *> carres, Maps &map, MapVue &mapVue);
  bool getInitMap() { return init_map; }
  void setInitMap(bool b) { init_map = b; }
};

#endif