#ifndef PIECECONTROLLER_HPP
#define PIECECONTROLLER_HPP

#include "GameController.hpp"
#include "MouseController.hpp"
#include "../models/Maps.hpp"
#include "../views/MapVue.hpp"
#include "../utils/Observer.hpp"

class GameController;

using namespace std;
using namespace sf;

class PieceController: public Observer
{
private:
  static PieceController* instance;
  PieceController();
  ~PieceController();

  GameController *gameController;
  MouseController *mouseController;
  MenuController *menuController;
  Maps *map;
  MapVue *mapVue;

  Text endText;
  Font font;
  Clock endClock;
  RectangleShape endOverlay;
  bool showEndText = false;

public:
  static PieceController* getInstance();
  PieceController(const PieceController&) = delete;
  void operator=(const PieceController&) = delete;
  static void destroyInstance();
  void init(GameController *gameController, MouseController *mouseController, MenuController *menuController, Maps *map, MapVue *mapVue);
  void update() override;
};

#endif