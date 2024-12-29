#ifndef MAPS
#define MAPS

#include "PieceOperateur.hpp"

using namespace std;

class Maps
{
private:
    vector<pair<int, int>> plateau;
    vector<Piece *> pieces;

public:
    Maps();
    ~Maps() { cout << "Maps deleted" << endl; }
    void map1();
    vector<pair<int, int>> getPlateau() { return plateau; }
    vector<Piece *> getPieces() { return pieces; }
};

#endif
