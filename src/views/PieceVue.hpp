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
  float size;

  Texture directionTexture;
  Texture rotateTexture;
  Texture symetricTexture;

  Color color;

  vector<Sprite> directionsSprite;
  Sprite rotateSprite;
  Sprite rotateSpriteInverse;
  Sprite symetricSprite;
  Sprite symetricSpriteInverse;

public:
  PieceVue();
  ~PieceVue();
  void init(float size);
  void initTexture();
  void initSprite();
  void draw(RenderWindow &window, Piece &piece, int pos_x, int pos_y);
  vector<Sprite> getDirectionsSprite() { return directionsSprite; }
  Sprite getRotateSprite() { return rotateSprite; }
  Sprite getSymetricSprite() { return symetricSprite; }
};

#endif