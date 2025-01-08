#ifndef PIECEFACTORY_HPP
#define PIECEFACTORY_HPP

#include "Piece.hpp"

class PieceFactory
{
public:
    virtual Piece* createPiece(Piece &source, const pair<int, int> &position) = 0;
    virtual ~PieceFactory() {}
};

#endif