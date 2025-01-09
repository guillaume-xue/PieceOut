#ifndef __HEADERVUE_HPP
#define __HEADERVUE_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>

using namespace std;
using namespace sf;

class HeaderVue
{
private:
  Texture homeTexture;
  Sprite homeButton;
  RectangleShape header;
  Sprite retour;
  Texture retourTexture;
public:
  HeaderVue();
  ~HeaderVue();
  void init(int nbPix_x);
  void draw(RenderWindow &window);
  Sprite getHomeButton();
  Sprite getRetourButton();
  void clear();
};

#endif