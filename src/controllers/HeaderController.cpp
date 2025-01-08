#include "HeaderController.hpp"

HeaderController *HeaderController::instance = nullptr;

HeaderController::HeaderController()
{
  // cout << "HeaderController created" << endl;
}

HeaderController::~HeaderController()
{
  cout << "HeaderController deleted" << endl;
}

HeaderController *HeaderController::getInstance()
{
  if (instance == nullptr)
  {
    instance = new HeaderController();
  }
  return instance;
}

void HeaderController::destroyInstance()
{
  if (instance != nullptr)
  {
    delete instance;
    instance = nullptr;
  }
}

void HeaderController::init(MouseController *mouseController, MenuController *menuController, Maps *map, MapVue *mapVue, HeaderVue *headerVue)
{
  this->mouseController = mouseController;
  this->menuController = menuController;
  this->map = map;
  this->mapVue = mapVue;
  this->headerVue = headerVue;
  mouseController->addObserver(this);
}

void HeaderController::update()
{
  if (headerVue->getHomeButton().getGlobalBounds().contains(mouseController->getMouseWorldPos()))
  {
    if (mouseController->isButtonPressed(Mouse::Left))
    {
      menuController->setInitMap(false);
      map->clean();
      mapVue->clear();
    }
  }
  if(headerVue->getRetourButton().getGlobalBounds().contains(mouseController->getMouseWorldPos()))
  {
    if(mouseController->isButtonPressed(Mouse::Left))
    {
      map->undo();
    }
  }
  // cout << "HeaderController update" << endl;
  mouseController->observerFinished();
  // cout << "HeaderController update finished" << endl;
}