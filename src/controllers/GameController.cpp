#include "GameController.hpp"

GameController* GameController::instance = nullptr; // Initialisation du pointeur statique

GameController::GameController()
{
  // cout << "GameController created" << endl;
  headerVue.init(nbPix_x);
  menuVue.init(nbPix_x, nbPix_y, 96);
  menuController = MenuController::getInstance();
  pieceController = PieceController::getInstance();
  keyboardController = KeyboardController::getInstance();
  mouseController = MouseController::getInstance();
  headerController = HeaderController::getInstance();
  map = Maps::getInstance();
  
  // keyboardController->addObserver(this);
  headerController->init(mouseController, menuController, map, &mapVue, &headerVue);
  menuController->init(mouseController, map, &mapVue, menuVue.getCarres());
  pieceController->init(this, mouseController, menuController, map, &mapVue);

  // mouseController->addObserver(this);
}

GameController::~GameController()
{
  cout << "GameController deleted" << endl;
}

GameController* GameController::getInstance()
{
  if (instance == nullptr)
  {
    instance = new GameController();
  }
  return instance;
}

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
  keyboardController->updateKeyboardEvent(window);
  mouseController->updateMousePosition(window);
}

void GameController::draw(RenderWindow &window)
{
  Color gray(194, 197, 204);
  window.clear(gray);
  window.setView(window.getDefaultView());

  headerVue.draw(window);

  if (menuController->getInitMap())
  {
    mapVue.draw(window, map);
  }
  else
  {
    menuVue.draw(window);
  }

  window.display();
}

void GameController::destroyInstance()
{
  if (instance != nullptr)
  {
    delete instance;
    instance = nullptr;
  }
}


void GameController::clear()
{
  menuVue.clear();
  mapVue.clear();
  MenuController::destroyInstance();
  PieceController::destroyInstance();
  KeyboardController::destroyInstance();
  MouseController::destroyInstance();
  HeaderController::destroyInstance();
  Maps::destroyInstance();
}

// void GameController::update()
// {
  // Réagir aux événements de la souris et du clavier
  // if (mouseController->isButtonPressed(Mouse::Left))
  // {
  //   if (!isMousePressed)
  //   {
  //     isMousePressed = true;
  //     headerController->update(mouseController, headerVue, menuController, map, mapVue);
  //     menuController->update(mouseController, menuVue.getCarres(), map, mapVue);
  //     if (menuController->getInitMap())
  //       if (pieceController->update(mouseController, map, mapVue))
  //       {
          
  //       }
  //   }
  // }
  // else
  // {
  //   isMousePressed = false;
  // }
  // cout << "GameController update" << endl;
  // mouseController->observerFinished();
  // cout << "GameController update finished" << endl;
  // keyboardController->observerFinished();
// }

void GameController::endMap(){
  menuController->setInitMap(false);
  mapVue.clear();
  map->clean();
}