#include "GameController.hpp"

GameController::GameController()
{
  headerVue.init(nbPix_x);
  menuVue.init(nbPix_x, nbPix_y, 96);
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
  clear();
}

void GameController::update(RenderWindow &window)
{
  keyboardController.updateKeyboardEvent(window);
  mouseController.updateMousePosition(window);
  if (mouseController.isButtonPressed(Mouse::Left))
    {
        if (!isMousePressed)
        {
            isMousePressed = true;
            headerController.update(mouseController, headerVue, menuController, map, mapVue);
            menuController.update(mouseController, menuVue.getCarres(), map, mapVue);
            if(menuController.getInitMap())
              if(pieceController.update(mouseController, map, mapVue)){
                menuController.setInitMap(false);
                mapVue.clear();
                map.clean();
              }
        }
    }
    else
    {
        isMousePressed = false;
    }
  
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

void GameController::clear()
{
  menuVue.clear();
  mapVue.clear();
}