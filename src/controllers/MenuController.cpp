#include "MenuController.hpp"

MenuController *MenuController::instance = nullptr;

MenuController *MenuController::getInstance()
{
  if (instance == nullptr)
  {
    instance = new MenuController();
  }
  return instance;
}

void MenuController::destroyInstance()
{
  if (instance != nullptr)
  {
    delete instance;
    instance = nullptr;
  }
}

void MenuController::update(MouseController *mouseController, vector<RectangleShape *> carres, Maps &map, MapVue &mapVue)
{
  if (mouseController->isButtonPressed(Mouse::Left) && !init_map)
  {
    for (size_t i = 0; i < carres.size(); i++)
    {
      if (carres[i]->getGlobalBounds().contains(mouseController->getMouseWorldPos()))
      {
        switch (i)
        {
        case 0:
          map.map1();
          mapVue.init(32, map);
          init_map = true;
          break;
        case 1:
          map.map2();
          mapVue.init(32, map);
          init_map = true;
          break;
        case 2:
          map.map3();
          mapVue.init(32, map);
          init_map = true;
          break;
        case 3:
          map.map4();
          mapVue.init(32, map);
          init_map = true;
          break;
        case 4:
          map.map5();
          mapVue.init(32, map);
          init_map = true;
          break;
        case 5:
          map.map6();
          mapVue.init(32, map);
          init_map = true;
          break;
        case 6:
          map.map7();
          mapVue.init(32, map);
          init_map = true;
          break;
        case 7:
          map.map8();
          mapVue.init(32, map);
          init_map = true;
          break;
        case 8:
          map.map9();
          mapVue.init(32, map);
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

