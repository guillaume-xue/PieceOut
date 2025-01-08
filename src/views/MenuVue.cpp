#include "MenuVue.hpp"

MenuVue::MenuVue()
{
  cout << "MenuVue created" << endl;
}

MenuVue::~MenuVue()
{
  // cout << "MenuVue deleted" << endl;
}

void MenuVue::init(int nbPix_x, int nbPix_y, int size)
{
  int padding_x = (nbPix_x - 3 * size - 2 * MARGIN) / 2;
  int padding_y = (nbPix_y - 3 * size - 2 * MARGIN) / 2;

  if (!font.loadFromFile("resources/font/04B_30__.TTF"))
    cout << "Erreur de chargement de la police" << endl;
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      RectangleShape *carre = new RectangleShape(Vector2f(size, size));
      carre->setFillColor(Color::White);
      carre->setPosition(padding_x + j * (size + MARGIN), padding_y + i * (size + MARGIN));
      carres.push_back(carre);
      Text *texte = new Text(to_string(i * 3 + j + 1), font, 32);
      texte->setFillColor(Color::Black);
      texte->setPosition(padding_x + j * (size + MARGIN) + size / 2 - texte->getGlobalBounds().width / 2,
                         padding_y + i * (size + MARGIN) + size / 2 - texte->getGlobalBounds().height / 2);
      textes.push_back(texte);
    }
  }
}

void MenuVue::draw(RenderWindow &window)
{
  for (RectangleShape *x : carres)
    window.draw(*x);
  for (Text *x : textes)
    window.draw(*x);
}

void MenuVue::clear()
{
  for (RectangleShape *x : carres)
    delete x;
  carres.clear();
  for (Text *x : textes)
    delete x;
  textes.clear();
}