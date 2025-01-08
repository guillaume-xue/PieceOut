#include "controllers/GameController.hpp"

int main()
{
  GameController* gameController = GameController::getInstance();
  gameController->run();
  GameController::destroyInstance();
  return EXIT_SUCCESS;
}