#include "MenuController.hpp"

MenuController::MenuController()
{
  cout << "MenuController created" << endl;
}

MenuController::~MenuController()
{
  cout << "MenuController deleted" << endl;
}

void MenuController::update(MouseController mouseController, vector<RectangleShape *> carres, Maps &map)
{
  if (mouseController.isButtonPressed(Mouse::Left) && !init_map)
  {
    for (size_t i = 0; i < carres.size(); i++)
    {
      if (carres[i]->getGlobalBounds().contains(mouseController.getMouseWorldPos()))
      {
        switch (i)
        {
        case 0:
          map.map1();
          init_map = true;
          break;

        default:
          init_map = false;
          break;
        }
      }
    }
  }
}