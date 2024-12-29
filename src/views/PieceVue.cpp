#include "PieceVue.hpp"

PieceVue::PieceVue()
{
  cout << "PieceVue created" << endl;
}

PieceVue::~PieceVue()
{
  cout << "PieceVue deleted" << endl;
}

void PieceVue::init(float size)
{
  this->size = size;
  initTexture();
  initSprite();
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

void PieceVue::initSprite()
{
  float new_size = size / directionTexture.getSize().x;
  for (int i = 0; i < 4; ++i)
  {
    Sprite sprite;
    sprite.setTexture(directionTexture);
    sprite.setScale(new_size, new_size);
    sprite.setRotation(i * 90);
    directionsSprite.push_back(sprite);
  }
  rotateSprite.setTexture(rotateTexture);
  rotateSprite.setScale(new_size, new_size);
  symetricSprite.setTexture(symetricTexture);
  symetricSprite.setScale(new_size, new_size);
}

void PieceVue::draw(RenderWindow &window, Piece &piece, int pos_x, int pos_y)
{
  int margin = 20;
  for (pair<int, int> x : piece.getCoordinates())
  {
    RectangleShape carre(Vector2f(size + margin, size + margin));
    carre.setFillColor(Color::Blue);                                                              // Couleur du carré
    carre.setPosition(pos_x + (x.first * (size + margin)), pos_y + (x.second * (size + margin))); // Position du carré
    window.draw(carre);
  }
  for (pair<int, int> x : piece.getCoordinates())
  {
    switch (piece.getSens(x, piece))
    {
    case NORD:
      directionsSprite[3].setPosition(pos_x + (x.first * (size + margin) + (margin / 2)), pos_y + (x.second * (size + margin) + size + (margin / 2)));
      window.draw(directionsSprite[3]);
      break;
    case SUD:
      directionsSprite[1].setPosition(pos_x + (x.first * (size + margin) + size + (margin / 2)), pos_y + (x.second * (size + margin) + (margin / 2)));
      window.draw(directionsSprite[1]);
      break;
    case EST: // On affiche la direction vers l'est
      directionsSprite[0].setPosition(pos_x + (x.first * (size + margin) + (margin / 2)), pos_y + (x.second * (size + margin) + (margin / 2)));
      window.draw(directionsSprite[0]);
      break;
    case OUEST: //
      directionsSprite[2].setPosition(pos_x + (x.first * (size + margin) + size + (margin / 2)), pos_y + (x.second * (size + margin) + size + (margin / 2)));
      window.draw(directionsSprite[2]);
      break;
    default:
      break;
    }
  }
}
