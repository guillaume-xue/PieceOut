#include "GameController.hpp"

GameController::GameController()
{
  headerVue.init(nbPix_x);
  menuVue.init(nbPix_x, nbPix_y, 96);
  mapVue.init(32, map);
}

GameController::~GameController() {}

void GameController::run()
{
  RenderWindow window{VideoMode{nbPix_x, nbPix_y}, "Piece Out"};

  while (window.isOpen())
  {
    update(window);
    draw(window);
  }
}

void GameController::update(RenderWindow &window)
{
  keyboardController.updateKeyboardEvent(window);
  mouseController.updateMousePosition(window);
  headerController.update(mouseController, headerVue, menuController);
  menuController.update(mouseController, menuVue.getCarres(), map);
  pieceController.update(mouseController, map, mapVue);
}

void GameController::draw(RenderWindow &window)
{
  Color gray(194, 197, 204);
  window.clear(gray);
  window.setView(window.getDefaultView());

  headerVue.draw(window);

  if (menuController.getInitMap())
  {
    mapVue.draw(window, map);
  }
  else
  {
    menuVue.draw(window);
  }

  window.display();
}