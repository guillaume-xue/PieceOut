#include "HeaderVue.hpp"

HeaderVue::HeaderVue()
{
  cout << "HeaderVue created" << endl;
}

HeaderVue::~HeaderVue()
{
  cout << "HeaderVue deleted" << endl;
}

void HeaderVue::init(int nbPix_x)
{
  if (!homeTexture.loadFromFile("resources/home.png"))
  {
    cout << "Error loading home.png" << endl;
  }
  homeButton.setTexture(homeTexture);
  homeButton.setScale(0.2, 0.2);
  homeButton.setPosition(5, 5);
  header.setSize(Vector2f(nbPix_x, 50));
  header.setFillColor(Color::White);
  header.setPosition(0, 0);

  if(!retourTexture.loadFromFile("resources/return.png"))
  {
    cout << "Error loading return.png" << endl;
  }
  retour.setTexture(retourTexture);
  retour.setScale(0.1, 0.1);
  retour.setPosition(50, 5);
}

void HeaderVue::draw(RenderWindow &window)
{
  window.draw(header);
  window.draw(homeButton);
  window.draw(retour);
}

Sprite HeaderVue::getHomeButton()
{
  return homeButton;
}

Sprite HeaderVue::getRetourButton()
{
  return retour;
}
