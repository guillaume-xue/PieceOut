#include "PieceController.hpp"

PieceController* PieceController::instance = nullptr;

PieceController::PieceController() 
{
  // cout << "PieceController created" << endl;
  if (!font.loadFromFile("resources/font/04B_30__.TTF"))
  {
    cout << "Error loading font" << endl;
  }
  endText.setFont(font);
  endText.setString("Finish");
  endText.setCharacterSize(50);
  endText.setFillColor(Color::Red);
  endText.setPosition(400, 300);

    endOverlay.setSize(sf::Vector2f(858, 640));
  endOverlay.setFillColor(sf::Color(0, 0, 0, 150));
}

PieceController::~PieceController() 
{
  cout << "PieceController deleted" << endl;
}

PieceController* PieceController::getInstance()
{
  if (instance == nullptr)
  {
    instance = new PieceController();
  }
  return instance;
}

void PieceController::destroyInstance()
{
  if (instance != nullptr)
  {
    delete instance;
    instance = nullptr;
  }
}

void PieceController::init(GameController *gameController, MouseController *mouseController,MenuController *menuController, Maps *map, MapVue *mapVue)
{
  this->gameController = gameController;
  this->mouseController = mouseController;
  this->menuController = menuController;
  this->map = map;
  this->mapVue = mapVue;
  mouseController->addObserver(this);
}

void PieceController::update()
{
  if (menuController->getInitMap())
  {
    if (mouseController->isButtonPressed(Mouse::Left))
    {
      pair<int, int> coord = make_pair(mouseController->getMouseWorldPos().x, mouseController->getMouseWorldPos().y);
      coord.first -= mapVue->getGlobalMarginX();
      coord.second -= mapVue->getGlobalMarginY();
      coord.first /= mapVue->getSizeCarre() + mapVue->getMarginCarre();
      coord.second /= mapVue->getSizeCarre() + mapVue->getMarginCarre();
      map->trigger(coord);
      if(map->isEnd()){
        map->clean();
        gameController->endMap();

        gameController->drawEndText(endText,endOverlay);
        
      }
    }
  }
  mouseController->observerFinished();
}