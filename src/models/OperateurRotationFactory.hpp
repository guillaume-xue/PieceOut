#ifndef OPERATEURROTATIONFACTORY_HPP
#define OPERATEURROTATIONFACTORY_HPP

#include "PieceFactory.hpp"
#include "PieceOperateur.hpp"

class OperateurRotationFactory : public PieceFactory
{
private:
    OrientationRotation sens;

public:
    OperateurRotationFactory(OrientationRotation sens) : sens(sens) {}
    Piece* createPiece(Piece &source, const pair<int, int> &position) override
    {
        return new OperateurRotation(source, position, sens);
    }
};

#endif