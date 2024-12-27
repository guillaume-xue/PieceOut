#ifndef MAPSCONTROLLER_HPP
#define MAPSCONTROLLER_HPP

#include "../models/Maps.hpp"
#include "../views/MapVue.hpp"
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class MapsController
{
private:
  Maps map;
  MapVue vue;

public:
  MapsController(int pos_x, int pos_y, float size);
  ~MapsController();
  void handleEvent(sf::Event &event);
  void update();
  void draw(sf::RenderWindow &window);
};

#endif