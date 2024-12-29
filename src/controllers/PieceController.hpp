#ifndef PIECECONTROLLER_HPP
#define PIECECONTROLLER_HPP

#include "../models/Piece.hpp"
#include "../models/PieceOperateur.hpp"
#include "../views/PieceVue.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

using namespace std;
using namespace sf;

class PieceController
{
private:
  vector<Piece *> pieces;
  PieceVue vue;

public:
  PieceController();
  ~PieceController();
  void addPiece(Piece *piece);
  void handleEvent(sf::Event &event);
  void update();
};

#endif