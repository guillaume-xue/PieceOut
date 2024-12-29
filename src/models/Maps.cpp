#include "Maps.hpp"

Maps::Maps()
{
    cout << "Maps created" << endl;
    map1();
}

void Maps::map1()
{
    vector<pair<int, int>> coords{{0, 0}};
    PieceConcrete *piece = new PieceConcrete(coords);
    Piece *p = new OperateurDeplacement(*piece, {0, 0}, EST);
    pieces.push_back(p);
    plateau = {{0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}};
}