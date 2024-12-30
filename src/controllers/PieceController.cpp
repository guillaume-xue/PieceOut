#include "PieceController.hpp"

PieceController::PieceController() {}

PieceController::~PieceController()
{
}

void PieceController::update(MouseController &mouseController, Maps &map, MapVue &mapVue)
{
  if (mouseController.isButtonPressed(Mouse::Left))
  {
    pair<int, int> coord = make_pair(mouseController.getMouseWorldPos().x, mouseController.getMouseWorldPos().y);
    coord.first -= mapVue.getGlobalMarginX();
    coord.second -= mapVue.getGlobalMarginY();
    coord.first /= mapVue.getSizeCarre() + mapVue.getMarginCarre();
    coord.second /= mapVue.getSizeCarre() + mapVue.getMarginCarre();
    map.trigger(coord);
  }
}