#include "HeaderVue.hpp"

HeaderVue::HeaderVue()
{
  cout << "HeaderVue created" << endl;
}

HeaderVue::~HeaderVue()
{
  cout << "HeaderVue deleted" << endl;
}

void HeaderVue::init(int nbPix_x, int nbPix_y)
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
}

void HeaderVue::draw(RenderWindow &window)
{
  window.draw(header);
  window.draw(homeButton);
}