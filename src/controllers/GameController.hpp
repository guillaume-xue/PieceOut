#ifndef __GAMECONTROLLER_HPP
#define __GAMECONTROLLER_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>

#include "../utils/Observer.hpp"
#include "../utils/CommandManager.hpp"

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
class PieceController;

class GameController
{
private:
  static GameController* instance;
  GameController();
  ~GameController();

  unsigned int nbPix_x = 858;
  unsigned int nbPix_y = 640;
  bool isMousePressed = false;
  MenuController *menuController;
  PieceController *pieceController;
  KeyboardController *keyboardController;
  MouseController *mouseController;
  HeaderController *headerController;
  CommandManager *commandManager;

  HeaderVue headerVue;
  MapVue mapVue;
  MenuVue menuVue;

  Maps *map;

public:
  static GameController* getInstance();
  GameController(const GameController&) = delete;
  void operator=(const GameController&) = delete;
  static void destroyInstance();
  
  void run();
  void update(RenderWindow &window);
  void draw(RenderWindow &window);
  void clear();
  void endMap();
  void drawEndText(Text &endText, RectangleShape &endOverlay);
};

#endif