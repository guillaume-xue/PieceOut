#ifndef __MENUVUE_HPP
#define __MENUVUE_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>

using namespace std;
using namespace sf;

class MenuVue
{
private:
  int MARGIN = 32;
  int nbPix_x, nbPix_y;
  int size;
  vector<RectangleShape *> carres;

public:
  MenuVue(int nbPix_x, int nbPix_y, int size);
  ~MenuVue();
  void init();
  int getNbMapClicked(Vector2f mousePos);
  void draw(RenderWindow &window);
};

#endif