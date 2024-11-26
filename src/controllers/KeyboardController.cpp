#include "KeyboardController.hpp"

KeyboardController::KeyboardController()
{
}

void KeyboardController::updateKeyboardEvent(RenderWindow &window)
{
  if (event.type == Event::Closed ||
      (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)) // fermeture de la fenêtre
    window.close();
}