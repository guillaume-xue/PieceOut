#include "Maps.hpp"

Maps::Maps()
{
    init();
}

void Maps::init()
{
    cout << "init" << endl;
    plateau = {{0, 0}, {0, 1}, {0, 2}, {0, 3}};
    Piece *piece = new PieceConcrete({{0, 0}});
    piece = new OperateurDeplacement{*piece, {0, 0}, EST};
    piece = new OperateurDeplacement{*piece, {0, 0}, OUEST};
    pieces.push_back(piece);
}