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
  Font font;
  vector<RectangleShape *> carres;
  vector<Text *> textes;

public:
  MenuVue();
  ~MenuVue();
  void init(int nbPix_x, int nbPix_y, int size);
  void draw(RenderWindow &window);
  vector<RectangleShape *> getCarres() { return carres; }
  void clear();
};

#endif