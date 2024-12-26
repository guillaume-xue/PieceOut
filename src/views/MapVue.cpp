#include "MapVue.hpp"

MapVue::MapVue(int pos_x, int pos_y, float size) : pos_x(pos_x), pos_y(pos_y), size(size)
{
  cout << "MapVue created" << endl;
}

MapVue::~MapVue()
{
  cout << "MapVue deleted" << endl;
}

void MapVue::draw(RenderWindow &window, Maps &map)
{
  int margin = 20;
  for (pair<int, int> x : map.plateau)
  {
    RectangleShape carre(Vector2f(size + margin, size + margin));
    carre.setFillColor(Color::White);                                                             // Couleur du carré
    carre.setPosition(pos_x + (x.first * (size + margin)), pos_y + (x.second * (size + margin))); // Position du carré
    window.draw(carre);
  }
}
