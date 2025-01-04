#include "Piece.hpp"
#include "PieceOperateur.hpp"

// Piece
void Piece::trigger(const pair<int, int> &coord)
{
    trigger(coord, *this);
}

// PieceConcrete
PieceConcrete::PieceConcrete(const vector<pair<int, int>> &coords, Maps *map)
    : coordinates(coords), maps(map) {}

void PieceConcrete::accept(PieceOperateur &v, Piece &origin, bool reverse)
{
    cout << "PieceConcrete::accept" << endl;
    v.visit(*this, origin, reverse);
}
// void PieceConcrete::reAccept(PieceOperateur &v, Piece &origin)
// {
//     cout << "PieceConcrete::reAccept" << endl;
//     v.reVisit(*this, origin);
// }
// void PieceConcrete::trigger(const pair<int, int> &coord, Piece &origin) {}

PieceOperateur *PieceConcrete::getSens(const pair<int, int> &coord, Piece &origin) const
{
    (void)coord;
    (void)origin;
    return nullptr;
}


