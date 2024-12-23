#include "PieceVue.hpp"

PieceVue::PieceVue(Piece &piece) : piece(piece)
{
  cout << "PieceVue created" << endl;
  init();
}

void PieceVue::init()
{
  initTexture();
  initDirectionSprite();
  initRotateSprite();
  initSymetricSprite();
}

void PieceVue::initTexture()
{
  if (!directionTexture.loadFromFile("resources/direction.png"))
  {
    cout << "Error loading direction.png" << endl;
  }
  if (!rotateTexture.loadFromFile("resources/rotate.png"))
  {
    cout << "Error loading rotate.png" << endl;
  }
  if (!symetricTexture.loadFromFile("resources/symetric.png"))
  {
    cout << "Error loading symetric.png" << endl;
  }
}

void PieceVue::initDirectionSprite()
{
  for (int i = 0; i < 4; ++i)
  {
    Sprite sprite;
    sprite.setTexture(directionTexture);
    sprite.setScale(0.1, 0.1);
    sprite.setRotation(i * 90);
    sprite.setPosition(100 + i * 10, 100);
    directionsSprite.push_back(sprite);
  }
}

void PieceVue::initRotateSprite()
{
  rotateSprite.setTexture(rotateTexture);
  rotateSprite.setScale(0.1, 0.1);
  rotateSprite.setPosition(10, 200);
}

void PieceVue::initSymetricSprite()
{
  symetricSprite.setTexture(symetricTexture);
  symetricSprite.setScale(0.1, 0.1);
  symetricSprite.setPosition(100, 300);
}

void PieceVue::draw(RenderWindow &window)
{
  for (Sprite x : directionsSprite)
    window.draw(x);
  window.draw(rotateSprite);
  window.draw(symetricSprite);
}