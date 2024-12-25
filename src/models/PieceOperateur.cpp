#include "PieceOperateur.hpp"

// PieceOperateur
PieceOperateur::PieceOperateur(Piece &source, const pair<int, int> &position)
    : source{source}, position{position} {}

void PieceOperateur::trigger(const pair<int, int> &relativePos, Piece &origin)
{
    if (relativePos == position)
        origin.accept(*this);
    else
        source.trigger(relativePos, origin);
}

void PieceOperateur::visit(PieceConcrete &p) const
{
    for (pair<int, int> &x : p.coordinates)
        mapPosition(x);
}

// OperateurDeplacement
OperateurDeplacement::OperateurDeplacement(Piece &source, const pair<int, int> &position, OrientationDeplacement sens)
    : PieceOperateur(source, position), sens{sens} {}

void OperateurDeplacement::accept(const PieceOperateur &v)
{
    v.visit(*this);
}

void OperateurDeplacement::visit(OperateurDeplacement &x) const
{
    mapPosition(x.position);
    x.source.accept(*this);
}

void OperateurDeplacement::mapPosition(pair<int, int> &pos) const
{
    switch (sens)
    {
    case NORD:
        pos.second--;
        break;
    case SUD:
        pos.second++;
        break;
    case EST:
        pos.first++;
        break;
    case OUEST:
        pos.first--;
        break;
    default:
        break;
    }
}

OrientationDeplacement OperateurDeplacement::getSens(const pair<int, int> &coord, Piece &origin) const
{
    if (coord == position)
        return sens;
    else
        return source.getSens(coord, origin);
}

// OperateurRotation
// OperateurRotation::OperateurRotation(Piece & source, const pair<int,int> & position)
//     : PieceOperateur(source,position) {}

// void OperateurRotation::accept(const PieceOperateur &v) {
//     v.visit(*this);
// }

// void OperateurRotation::visit(OperateurRotation &x) const {
//     mapPosition(x.position);
//     x.source.accept(*this);
// }

// void OperateurRotation::mapPosition(pair<int, int> & pos) const {
//     int x = pos.first;
//     pos.first = -pos.second;
//     pos.second = x;
// }

// // OperateurSymetrie
// OperateurSymetrie::OperateurSymetrie(Piece & source, const pair<int,int> & position)
//     : PieceOperateur(source,position) {}

// void OperateurSymetrie::accept(const PieceOperateur &v) {
//     v.visit(*this);
// }

// void OperateurSymetrie::visit(OperateurSymetrie &x) const {
//     mapPosition(x.position);
//     x.source.accept(*this);
// }

// void OperateurSymetrie::mapPosition(pair<int, int> & pos) const {
//     pos.first = -pos.first;
// }
