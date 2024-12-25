#include "PieceVue.hpp"

PieceVue::PieceVue(Piece &piece) : piece(piece)
{
  cout << "PieceVue created" << endl;
  init();
}

void PieceVue::init()
{
  initTexture();
  initSprite(32);
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

void PieceVue::initSprite(float size)
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

void PieceVue::draw(RenderWindow &window)
{
  int size = directionsSprite[0].getScale().x * directionTexture.getSize().x;
  int margin = 20;
  for (pair<int, int> x : piece.getCoordinates())
  {
    RectangleShape carre(Vector2f(size + margin, size + margin));
    carre.setFillColor(Color::Blue);                                          // Couleur du carré
    carre.setPosition(x.first * (size + margin), x.second * (size + margin)); // Position du carré
    window.draw(carre);
  }
  for (pair<int, int> x : piece.getCoordinates())
  {
    switch (piece.getSens(x, piece))
    {
    case NORD:
      directionsSprite[3].setPosition(x.first * 100 + (margin / 2), x.second * 100 + size + (margin / 2));
      window.draw(directionsSprite[3]);
      break;
    case SUD:
      directionsSprite[1].setPosition(x.first * 100 + size + (margin / 2), x.second * 100 + (margin / 2));
      window.draw(directionsSprite[1]);
      break;
    case EST: // On affiche la direction vers l'est
      directionsSprite[0].setPosition(x.first * 100 + (margin / 2), x.second * 100 + (margin / 2));
      window.draw(directionsSprite[0]);
      break;
    case OUEST: //
      directionsSprite[2].setPosition(x.first * 100 + size + (margin / 2), x.second * 100 + size + (margin / 2));
      window.draw(directionsSprite[2]);
      break;
    default:
      break;
    }
  }
}
