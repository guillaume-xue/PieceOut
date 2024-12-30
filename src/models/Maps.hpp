#ifndef MAPS
#define MAPS

#include "PieceOperateur.hpp"

using namespace std;

class Maps
{
private:
    vector<pair<int, int>> plateau;
    vector<Piece *> pieces;
    pair<int, int> sizePlateau;

public:
    Maps();
    ~Maps() { cout << "Maps deleted" << endl; }
    void map1();
    void trigger(const pair<int, int> &relativePos);
    vector<pair<int, int>> getPlateau() { return plateau; }
    vector<Piece *> getPieces() { return pieces; }
    pair<int, int> getSizePlateau() { return sizePlateau; }
};

#endif
