#include "MenuVue.hpp"

MenuVue::MenuVue(int nbPix_x, int nbPix_y, int size) : nbPix_x(nbPix_x), nbPix_y(nbPix_y), size(size)
{
  init();
  cout << "MenuVue created" << endl;
}

MenuVue::~MenuVue()
{
  cout << "MenuVue deleted" << endl;
}

void MenuVue::init()
{
  int padding_x = (nbPix_x - 3 * size - 2 * MARGIN) / 2;
  int padding_y = (nbPix_y - 3 * size - 2 * MARGIN) / 2;
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      RectangleShape *carre = new RectangleShape(Vector2f(size, size));
      carre->setFillColor(Color::White);
      carre->setPosition(padding_x + i * (size + MARGIN), padding_y + j * (size + MARGIN));
      carres.push_back(carre);
    }
  }
}

int MenuVue::getNbMapClicked(Vector2f mousePos)
{
  for (int i = 0; i < carres.size(); i++)
  {
    if (carres[i]->getGlobalBounds().contains(mousePos))
      return i;
  }
  return -1;
}

void MenuVue::draw(RenderWindow &window)
{
  for (RectangleShape *x : carres)
    window.draw(*x);
}