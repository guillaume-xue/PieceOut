#ifndef __GAMECONTROLLER_HPP
#define __GAMECONTROLLER_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>

#include "MenuController.hpp"
#include "PieceController.hpp"
#include "KeyboardController.hpp"
#include "MouseController.hpp"
#include "HeaderController.hpp"

#include "../models/Maps.hpp"

#include "../views/MenuVue.hpp"
#include "../views/HeaderVue.hpp"
#include "../views/MapVue.hpp"

using namespace std;
using namespace sf;

class GameController
{
private:
  unsigned int nbPix_x = 858;
  unsigned int nbPix_y = 640;

  MenuController menuController;
  PieceController pieceController;
  KeyboardController keyboardController;
  MouseController mouseController;
  HeaderController headerController;

  HeaderVue headerVue;
  MapVue mapVue;
  MenuVue menuVue;

  Maps map;

public:
  GameController();
  ~GameController();
  void run();
  void update(RenderWindow &window);
  void draw(RenderWindow &window);
};

#endif