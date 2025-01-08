#include "PieceController.hpp"

PieceController* PieceController::instance = nullptr;

PieceController::PieceController() {}

PieceController::~PieceController() {
  cout << "PieceController deleted" << endl;
}

PieceController* PieceController::getInstance()
{
  if (instance == nullptr)
  {
    instance = new PieceController();
  }
  return instance;
}

void PieceController::destroyInstance()
{
  if (instance != nullptr)
  {
    delete instance;
    instance = nullptr;
  }
}

bool PieceController::update(MouseController *mouseController, Maps *map, MapVue &mapVue)
{
  if (mouseController->isButtonPressed(Mouse::Left))
  {
    pair<int, int> coord = make_pair(mouseController->getMouseWorldPos().x, mouseController->getMouseWorldPos().y);
    coord.first -= mapVue.getGlobalMarginX();
    coord.second -= mapVue.getGlobalMarginY();
    coord.first /= mapVue.getSizeCarre() + mapVue.getMarginCarre();
    coord.second /= mapVue.getSizeCarre() + mapVue.getMarginCarre();
    map->trigger(coord);
    if(map->isEnd()){
      cout << "End of the game" << endl;
      map->clean();
      return true;
    }
  }
  return false;
}