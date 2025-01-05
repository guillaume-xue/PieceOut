#ifndef PIECECONTROLLER_HPP
#define PIECECONTROLLER_HPP

#include "MouseController.hpp"
#include "../models/Maps.hpp"
#include "../views/MapVue.hpp"

using namespace std;
using namespace sf;

class PieceController
{
public:
  PieceController();
  ~PieceController();
  bool update(MouseController &mouseController, Maps &map, MapVue &mapVue);
};

#endif