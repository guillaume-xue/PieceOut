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
    v.visit(*this, origin, reverse);
}

PieceOperateur *PieceConcrete::getSens(const pair<int, int> &coord, Piece &origin) const
{
    (void)coord;
    (void)origin;
    return nullptr;
}

void PieceConcrete::clean()
{
    coordinates.clear();
    endPos.clear();
    maps = nullptr;
    delete this;
}


