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
  Piece &piece;

  int pieceSize;
  int positionX;
  int positionY;

  Texture directionTexture;
  Texture rotateTexture;
  Texture symetricTexture;

  vector<Sprite> directionsSprite;
  Sprite rotateSprite;
  Sprite symetricSprite;

public:
  PieceVue(Piece &piece);
  ~PieceVue() { cout << "PieceVue deleted" << endl; }
  void init();
  void initTexture();
  void initDirectionSprite();
  void initRotateSprite();
  void initSymetricSprite();
  void draw(RenderWindow &window);
  void update();
};

#endif