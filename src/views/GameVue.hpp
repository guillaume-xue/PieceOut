#ifndef __GAMEVUE_HPP
#define __GAMEVUE_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>

#include "MenuVue.hpp"
#include "HeaderVue.hpp"

using namespace std;
using namespace sf;

class GameVue
{
private:
  const unsigned int nbPix_x = 858;
  const unsigned int nbPix_y = 640;
  vector<Drawable *> scene_generale;
  MenuVue menuVue;
  HeaderVue headerVue;

public:
  GameVue();
  ~GameVue();
  void init();
  void draw(RenderWindow &window);
};

#endif
