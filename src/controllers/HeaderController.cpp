#include "HeaderController.hpp"

HeaderController::HeaderController()
{
  cout << "HeaderController created" << endl;
}

HeaderController::~HeaderController()
{
  cout << "HeaderController deleted" << endl;
}

void HeaderController::update(MouseController &mouseController, HeaderVue &headerVue, MenuController &menuController, Maps &map)
{
  if (headerVue.getHomeButton().getGlobalBounds().contains(mouseController.getMouseWorldPos()))
  {
    if (mouseController.isButtonPressed(Mouse::Left))
    {
      menuController.setInitMap(false);
    }
  }
  if(headerVue.getRetourButton().getGlobalBounds().contains(mouseController.getMouseWorldPos()))
  {
    if(mouseController.isButtonPressed(Mouse::Left))
    {
      map.undo();
    }
  }
}