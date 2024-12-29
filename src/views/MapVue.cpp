#include "MapVue.hpp"

MapVue::MapVue()
{
  cout << "MapVue created" << endl;
}

MapVue::~MapVue()
{
  cout << "MapVue deleted" << endl;
}

void MapVue::init(float size, Maps &map)
{
  this->size = size;
  for (size_t i = 0; i < map.getPieces().size(); i++)
  {
    PieceVue *piece = new PieceVue();
    piece->init(size);
    pieces.push_back(piece);
  }
}

pair<int, int> findMaxFirstAndSecond(const vector<pair<int, int>> &vec)
{
  int maxFirst = INT_MIN;
  int maxSecond = INT_MIN;

  for (const auto &p : vec)
  {
    if (p.first > maxFirst)
    {
      maxFirst = p.first;
    }
    if (p.second > maxSecond)
    {
      maxSecond = p.second;
    }
  }

  return {maxFirst + 1, maxSecond + 1};
}

void MapVue::draw(RenderWindow &window, Maps &map)
{
  int margin = 20;
  pair<int, int> maxFirstAndSecond = findMaxFirstAndSecond(map.getPlateau());
  int pos_x = window.getSize().x / 2 - (maxFirstAndSecond.first * (size + margin)) / 2;
  int pos_y = window.getSize().y / 2 - (maxFirstAndSecond.second * (size + margin)) / 2;

  for (pair<int, int> x : map.getPlateau())
  {
    RectangleShape carre(Vector2f(size + margin, size + margin));
    carre.setFillColor(Color::White);                                                             // Couleur du carré
    carre.setPosition(pos_x + (x.first * (size + margin)), pos_y + (x.second * (size + margin))); // Position du carré
    window.draw(carre);
  }
  for (size_t i = 0; i < map.getPieces().size(); i++)
  {
    pieces[i]->draw(window, *map.getPieces()[i], pos_x, pos_y);
  }
}
