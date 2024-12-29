#include "KeyboardController.hpp"

KeyboardController::KeyboardController()
{
}

void KeyboardController::updateKeyboardEvent(RenderWindow &window)
{
  while (window.pollEvent(event))
  {
    if (event.type == Event::Closed ||
        (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)) // fermeture de la fenêtre
      window.close();
  }
}