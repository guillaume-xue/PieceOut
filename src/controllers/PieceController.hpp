#ifndef PIECECONTROLLER_HPP
#define PIECECONTROLLER_HPP

#include "MouseController.hpp"
#include "../models/Maps.hpp"
#include "../views/MapVue.hpp"

using namespace std;
using namespace sf;

class PieceController
{
private:
  static PieceController* instance;
  PieceController();
  ~PieceController();

public:
  static PieceController* getInstance();
  PieceController(const PieceController&) = delete;
  void operator=(const PieceController&) = delete;
  static void destroyInstance();
  bool update(MouseController *mouseController, Maps &map, MapVue &mapVue);
};

#endif