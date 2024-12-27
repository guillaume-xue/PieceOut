#include "MenuController.hpp"

MenuController::MenuController()
{
  cout << "MenuController created" << endl;
}

MenuController::~MenuController()
{
  cout << "MenuController deleted" << endl;
}

int MenuController::getNbMapClicked(Vector2f mousePos, vector<RectangleShape *> carres)
{
  for (size_t i = 0; i < carres.size(); i++)
  {
    if (carres[i]->getGlobalBounds().contains(mousePos))
      return i + 1;
  }
  return -1;
}