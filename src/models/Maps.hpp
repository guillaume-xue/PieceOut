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
    void init();
    ~Maps() { cout << "Maps deleted" << endl; }
    friend class MapVue;
};

#endif
