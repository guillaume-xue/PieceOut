#ifndef ACTIONS_HPP
#define ACTIONS_HPP

#include "Piece.hpp"

class Actions
{
private:
    PieceConcrete &pc;
    const PieceOperateur &piece;
    Piece *origin = nullptr;
public:
    Actions(const PieceOperateur &p, Piece *origin, PieceConcrete &pc) : pc{pc}, piece{p}, origin{origin}  {}
    ~Actions() {}

    PieceConcrete &getPieceConcrete() { return pc; }
    Piece *getOrigin() { return origin; }
    const PieceOperateur &getPiece() { return piece; }
};

#endif