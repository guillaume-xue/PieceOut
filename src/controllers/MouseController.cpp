#include "MouseController.hpp"

MouseController::MouseController()
{
  mousePos = Vector2i(0, 0);
  mouseWorldPos = Vector2f(0, 0);
}

void MouseController::updateMousePosition(RenderWindow &window)
{
  mousePos = Mouse::getPosition(window);
  mouseWorldPos = window.mapPixelToCoords(mousePos);
}

Vector2f MouseController::getMouseWorldPos()
{
  return mouseWorldPos;
}