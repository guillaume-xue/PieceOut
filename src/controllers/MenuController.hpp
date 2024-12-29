#ifndef MENUCONTROLLER_HPP
#define MENUCONTROLLER_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "MouseController.hpp"

using namespace std;
using namespace sf;

class MenuController
{
private:
  int nbMapClicked = -1;

public:
  MenuController();
  ~MenuController();
  void update(MouseController mouseController, vector<RectangleShape *> carres);
  int getNbMapClicked();
  void setNbMapClicked(int nb) { nbMapClicked = nb; }
};

#endif