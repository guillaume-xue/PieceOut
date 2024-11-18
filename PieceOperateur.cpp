#include "PieceOperateur.hpp"

// PieceOperateur
PieceOperateur::PieceOperateur(Piece & source, const pair<int,int> & position) 
    : source{source},position{position} {}

void PieceOperateur::trigger(const pair<int,int> & relativePos, Piece &origin) {
    if (relativePos == position) origin.accept(*this);
    else source.trigger(relativePos, origin);
}

void PieceOperateur::visit(PieceConcrete &p) const {
    for (pair<int,int> &x : p.coordinates) mapPosition(x);
}

// OperateurDeplacement
OperateurDeplacement::OperateurDeplacement(Piece & source, const pair<int,int> & position, OrientationDeplacement sens) 
    : PieceOperateur(source,position) , sens{sens} {}


void OperateurDeplacement::accept(const PieceOperateur &v) {
    v.visit(*this);
}

void OperateurDeplacement::visit(OperateurDeplacement &x) const {
    mapPosition(x.position);
    x.source.accept(*this);
}

void OperateurDeplacement::mapPosition(pair<int, int> & pos) const {
    switch (sens) {
        case NORD : pos.second--; break;
        case SUD : pos.second++; break;
        case EST : pos.first++; break;
        case OUEST : pos.first--; break;
    }
}



