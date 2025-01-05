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
    vector<Piece *> piecesEnd;
    pair<int, int> sizePlateau;
    vector<Actions *> actions;
public:
    Maps();
    ~Maps() { cout << "Maps deleted" << endl; }
    void map1();
    void map2();
    void map3();
    void map4();
    void map5();
    void map6();
    void map7();
    void map8();
    void map9();
    void trigger(const pair<int, int> &relativePos);
    vector<pair<int, int>> getPlateau() { return plateau; }
    vector<Piece *> getPieces() { return pieces; }
    vector<Piece *> getPiecesEnd() { return piecesEnd; }
    pair<int, int> getSizePlateau() { return sizePlateau; }
    vector<Actions *> &getActions() { return actions; }
    void undo();
    bool verify(Actions *origin);
    void clean();
    bool isEnd();
};

Piece *R_rota_oneDir(Maps *maps);
Piece *L_rota_sym_oneDir(Maps *maps);

#endif
