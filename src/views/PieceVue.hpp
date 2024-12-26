#ifndef __PIECEVUE_HPP
#define __PIECEVUE_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include "../models/Piece.hpp"
#include "../models/PieceOperateur.hpp"

using namespace std;
using namespace sf;

class PieceVue
{
private:
  int pos_x, pos_y;
  float size;

  Texture directionTexture;
  Texture rotateTexture;
  Texture symetricTexture;

  vector<Sprite> directionsSprite;
  Sprite rotateSprite;
  Sprite symetricSprite;

public:
  PieceVue(int pos_x, int pos_y, float size);
  ~PieceVue();
  void init();
  void initTexture();
  void initSprite();
  void draw(RenderWindow &window, Piece &piece);
};

#endif