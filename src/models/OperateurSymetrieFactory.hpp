#ifndef OPERATEURSYMETRIEFACTORY_HPP
#define OPERATEURSYMETRIEFACTORY_HPP

#include "PieceFactory.hpp"
#include "PieceOperateur.hpp"

class OperateurSymetrieFactory : public PieceFactory
{
private:
    OrientationSymetrie sens;

public:
    OperateurSymetrieFactory(OrientationSymetrie sens) : sens(sens) {}
    Piece* createPiece(Piece &source, const pair<int, int> &position) override
    {
        return new OperateurSymetrie(source, position, sens);
    }
};

#endif