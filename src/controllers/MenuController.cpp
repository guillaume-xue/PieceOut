#include "MenuController.hpp"

MenuController::MenuController()
{
  cout << "MenuController created" << endl;
}

MenuController::~MenuController()
{
  cout << "MenuController deleted" << endl;
}

void MenuController::update(MouseController mouseController, vector<RectangleShape *> carres)
{
  if (mouseController.isButtonPressed(Mouse::Left) && nbMapClicked == -1)
  {
    for (size_t i = 0; i < carres.size(); i++)
    {
      if (carres[i]->getGlobalBounds().contains(mouseController.getMouseWorldPos()))
        nbMapClicked = i;
    }
  }
}

int MenuController::getNbMapClicked()
{
  return nbMapClicked;
}