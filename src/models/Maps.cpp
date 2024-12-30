#include "Maps.hpp"

Maps::Maps()
{
    cout << "Maps created" << endl;
    map1();
}

pair<int, int> findMaxFirstAndSecond(const vector<pair<int, int>> &vec)
{
    int maxFirst = INT_MIN;
    int maxSecond = INT_MIN;

    for (const auto &p : vec)
    {
        if (p.first > maxFirst)
        {
            maxFirst = p.first;
        }
        if (p.second > maxSecond)
        {
            maxSecond = p.second;
        }
    }

    return {maxFirst + 1, maxSecond + 1};
}

void Maps::map1()
{
    pieces.clear();
    plateau.clear();
    vector<pair<int, int>> coords{{0, 0}};
    PieceConcrete *piece = new PieceConcrete(coords);
    Piece *p = new OperateurDeplacement(*piece, {0, 0}, EST);
    pieces.push_back(p);
    plateau = {{0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}};

    sizePlateau = findMaxFirstAndSecond(plateau);
}

void Maps::trigger(const pair<int, int> &relativePos)
{
    for (Piece *p : pieces)
    {
        p->trigger(relativePos);
    }
}