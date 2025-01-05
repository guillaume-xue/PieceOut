#ifndef ACTIONS_HPP
#define ACTIONS_HPP

#include "Piece.hpp"

class Actions
{
private:
    PieceConcrete &pc;
    PieceOperateur &piece;
    Piece *origin = nullptr;
public:
    Actions(PieceOperateur &p, Piece *origin, PieceConcrete &pc) : pc{pc}, piece{p}, origin{origin}  {}
    ~Actions() {}

    PieceConcrete &getPieceConcrete() { return pc; }
    Piece *getOrigin() { return origin; }
    PieceOperateur &getPiece() { return piece; }
    void clean() { origin = nullptr; }
};

#endif