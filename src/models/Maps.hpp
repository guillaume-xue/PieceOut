#ifndef MAPS
#define MAPS

#include "PieceOperateur.hpp"
#include "Actions.hpp"
#include <climits>
#include <set>

using namespace std;

class Maps
{
private:
    vector<pair<int, int>> plateau;
    set <pair<int, int>> plateauSet;
    vector<Piece *> pieces;
    pair<int, int> sizePlateau;
    vector<Actions *> actions;
public:
    Maps();
    ~Maps() { cout << "Maps deleted" << endl; }
    void map1();
    void map2();
    void trigger(const pair<int, int> &relativePos);
    vector<pair<int, int>> getPlateau() { return plateau; }
    vector<Piece *> getPieces() { return pieces; }
    pair<int, int> getSizePlateau() { return sizePlateau; }
    vector<Actions *> &getActions() { return actions; }
    bool verify(Actions *origin);
};

#endif
