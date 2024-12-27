#ifndef MENUCONTROLLER_HPP
#define MENUCONTROLLER_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

using namespace std;
using namespace sf;

class MenuController
{
public:
  MenuController();
  ~MenuController();
  int getNbMapClicked(Vector2f mousePos, vector<RectangleShape *> carres);
};

#endif