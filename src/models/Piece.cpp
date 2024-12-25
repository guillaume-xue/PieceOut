#include "Piece.hpp"
#include "PieceOperateur.hpp"

// Piece
void Piece::trigger(const pair<int, int> &coord)
{
    trigger(coord, *this);
}

// PieceConcrete
PieceConcrete::PieceConcrete(const vector<pair<int, int>> &coords)
    : coordinates(coords) {}

void PieceConcrete::accept(const PieceOperateur &v)
{
    v.visit(*this);
}

void PieceConcrete::trigger(const pair<int, int> &coord, Piece &origin) {}

OrientationDeplacement PieceConcrete::getSens(const pair<int, int> &coord, Piece &origin) const
{
    return VIDE;
}