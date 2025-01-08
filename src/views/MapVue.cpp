#include "MapVue.hpp"

MapVue::MapVue()
{
  cout << "MapVue created" << endl;
}

MapVue::~MapVue()
{
  // cout << "MapVue deleted" << endl;
}

void MapVue::init(float size, Maps *map)
{
  this->SIZE_CARRE = size;
  // Init pieces
  for (size_t i = 0; i < map->getPieces().size(); i++)
  { 
    PieceVue *piece = new PieceVue();
    piece->init(size);
    pieces.push_back(piece);
  }
}

void MapVue::draw(RenderWindow &window, Maps *map)
{
  // Global margin
  GLOBAL_MARGIN_X = window.getSize().x / 2 - (map->getSizePlateau().first * (SIZE_CARRE + MARGIN_CARRE)) / 2;
  GLOBAL_MARGIN_Y = window.getSize().y / 2 - (map->getSizePlateau().second * (SIZE_CARRE + MARGIN_CARRE)) / 2;
  // Draw plateau
  for (pair<int, int> x : map->getPlateau())
  {
    RectangleShape carre(Vector2f(SIZE_CARRE + MARGIN_CARRE, SIZE_CARRE + MARGIN_CARRE));
    carre.setFillColor(Color::White);                                                                                                         // Couleur du carré
    carre.setPosition(GLOBAL_MARGIN_X + (x.first * (SIZE_CARRE + MARGIN_CARRE)), GLOBAL_MARGIN_Y + (x.second * (SIZE_CARRE + MARGIN_CARRE))); // Position du carré
    window.draw(carre);
  }
  // Draw pieces
  for (size_t i = 0; i < map->getPiecesEnd().size(); i++)
  {
    pieces[i]->draw2(window, *map->getPiecesEnd()[i], GLOBAL_MARGIN_X, GLOBAL_MARGIN_Y);
  }
  for (size_t i = 0; i < map->getPieces().size(); i++)
  {
    pieces[i]->draw(window, *map->getPieces()[i], GLOBAL_MARGIN_X, GLOBAL_MARGIN_Y);
  }
}

void MapVue::clear()
{
  for (PieceVue *p : pieces)
  {
    p->clear();
    delete p;
  }
  pieces.clear();

}
