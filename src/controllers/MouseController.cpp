#include "MouseController.hpp"

MouseController *MouseController::instance = nullptr;

MouseController::MouseController()
{
  // cout << "MouseController created" << endl;
  mousePos = Vector2i(0, 0);
  mouseWorldPos = Vector2f(0, 0);
}

MouseController::~MouseController()
{
  cout << "MouseController deleted" << endl;
}

MouseController *MouseController::getInstance()
{
  if (instance == nullptr)
  {
    instance = new MouseController();
  }
  return instance;
}

void MouseController::destroyInstance()
{
  if (instance != nullptr)
  {
    delete instance;
    instance = nullptr;
  }
}

void MouseController::updateMousePosition(RenderWindow &window)
{
  mousePos = Mouse::getPosition(window);
  mouseWorldPos = window.mapPixelToCoords(mousePos);

  if (Mouse::isButtonPressed(Mouse::Left))
  {
    if (!isMousePressed)
    {
      isMousePressed = true;
      notifyObservers();
    }
  }
  else
  {
    isMousePressed = false;
  }
}

Vector2f MouseController::getMouseWorldPos()
{
  return mouseWorldPos;
}