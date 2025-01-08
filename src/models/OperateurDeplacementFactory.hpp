#ifndef OPERATEURDEPLACEMENTFACTORY_HPP
#define OPERATEURDEPLACEMENTFACTORY_HPP

#include "PieceFactory.hpp"
#include "PieceOperateur.hpp"

class OperateurDeplacementFactory : public PieceFactory
{
private:
    OrientationDeplacement sens;

public:
    OperateurDeplacementFactory(OrientationDeplacement sens) : sens(sens) {}
    Piece* createPiece(Piece &source, const pair<int, int> &position) override
    {
        return new OperateurDeplacement(source, position, sens);
    }
};

#endif