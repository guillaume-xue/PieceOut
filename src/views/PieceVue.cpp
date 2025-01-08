#include "PieceVue.hpp"

PieceVue::PieceVue()
{
  cout << "PieceVue created" << endl;
}

PieceVue::~PieceVue()
{
  // cout << "PieceVue deleted" << endl;
}

void PieceVue::init(float size)
{
  this->size = size;
  color = Color(rand() % 251, rand() % 251, rand() % 251);
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
  if (!croix.loadFromFile("resources/croix.png"))
  {
    cout << "Error loading croix.png" << endl;
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
  rotateSpriteInverse.setTexture(rotateTexture);
  rotateSpriteInverse.setOrigin({rotateSpriteInverse.getLocalBounds().width, 0});
  rotateSpriteInverse.setScale(-new_size, new_size);
  symetricSprite.setTexture(symetricTexture);
  symetricSprite.setScale(new_size, new_size);
  symetricSpriteHoriz.setTexture(symetricTexture);
  symetricSpriteHoriz.setScale(new_size, new_size);
  symetricSpriteHoriz.setRotation(90);
  
  croixSprite.setTexture(croix);
  croixSprite.setScale(new_size, new_size);
}

void PieceVue::draw(RenderWindow &window, Piece &piece, int pos_x, int pos_y)
{
  int margin = 20;
  for (pair<int, int> x : piece.getCoordinates())
  {
    RectangleShape carre(Vector2f(size + margin, size + margin));
    carre.setFillColor(color);                                                                    // Couleur du carré
    carre.setPosition(pos_x + (x.first * (size + margin)), pos_y + (x.second * (size + margin))); // Position du carré
    window.draw(carre);
  }
  for (pair<int, int> x : piece.getCoordinates())
  {
    if (OperateurDeplacement *op = dynamic_cast<OperateurDeplacement *>(piece.getSens(x, piece)))
    {
      switch (op->sens)
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
    else if (OperateurRotation *op = dynamic_cast<OperateurRotation *>(piece.getSens(x, piece)))
    {
      switch (op->sens)
      {
      case HORAIRE:
        rotateSprite.setPosition(pos_x + (x.first * (size + margin) + (margin / 2)), pos_y + (x.second * (size + margin) + (margin / 2)));
        window.draw(rotateSprite);
        break;
      case ANTI_HORAIRE:
        rotateSpriteInverse.setPosition(pos_x + (x.first * (size + margin) + (margin / 2)), pos_y + (x.second * (size + margin) + (margin / 2)));
        window.draw(rotateSpriteInverse);
        break;
      default:
        break;
      }
    }
    else if (OperateurSymetrie *op = dynamic_cast<OperateurSymetrie *>(piece.getSens(x, piece)))
    {
      switch (op->sens)
      {
      case HORIZONTALE:
        symetricSpriteHoriz.setPosition(pos_x + (x.first * (size + margin) + size + (margin / 2)), pos_y + (x.second * (size + margin) + (margin / 2)));
        window.draw(symetricSpriteHoriz);
        break;
      case VERTICALE:
        symetricSprite.setPosition(pos_x + (x.first * (size + margin) + (margin / 2)), pos_y + (x.second * (size + margin) + (margin / 2)));
        window.draw(symetricSprite);
        break;
      default:
        break;
      }
    }
  }
}

void PieceVue::draw2(RenderWindow &window, Piece &piece, int pos_x, int pos_y)
{
  int margin = 20;
  for (pair<int, int> x : piece.getEndPos())
  {
    RectangleShape carre(Vector2f(size + margin, size + margin));
    carre.setFillColor(color);                                                                    // Couleur du carré
    carre.setPosition(pos_x + (x.first * (size + margin)), pos_y + (x.second * (size + margin))); // Position du carré
    window.draw(carre);
  }
  for (pair<int, int> x : piece.getEndPos())
  {
    croixSprite.setPosition(pos_x + (x.first * (size + margin) + (margin / 2)), pos_y + (x.second * (size + margin) + (margin / 2)));
    window.draw(croixSprite);
  }
}

void PieceVue::clear()
{
  directionsSprite.clear();
}

