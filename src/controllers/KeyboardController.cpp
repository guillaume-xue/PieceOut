#include "KeyboardController.hpp"

KeyboardController *KeyboardController::instance = nullptr;

KeyboardController::KeyboardController()
{
  // cout << "KeyboardController created" << endl;
}

KeyboardController::~KeyboardController()
{
  cout << "KeyboardController deleted" << endl;
}

KeyboardController *KeyboardController::getInstance()
{
  if (instance == nullptr)
  {
    instance = new KeyboardController();
  }
  return instance;
}

void KeyboardController::destroyInstance()
{
  if (instance != nullptr)
  {
    delete instance;
    instance = nullptr;
  }
}

void KeyboardController::updateKeyboardEvent(RenderWindow &window)
{
  while (window.pollEvent(event))
  {
    if (event.type == Event::Closed ||
        (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)) // fermeture de la fenêtre
      window.close();
  }
  notifyObservers();
}