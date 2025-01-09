#ifndef PIECEOPERATEUR_HPP
#define PIECEOPERATEUR_HPP

#include "Piece.hpp"
#include "Maps.hpp"
#include "../utils/MovePieceCommand.hpp"
#include "../utils/Command.hpp"

class OperateurDeplacement;
class OperateurRotation;
class OperateurSymetrie;

using namespace std;

class PieceOperateur : public Piece
{
public:
    Piece &source;
    pair<int, int> position;
    PieceOperateur(Piece &source, const pair<int, int> &position);
    const vector<pair<int, int>> &getCoordinates() const { return source.getCoordinates(); }
    const vector<pair<int, int>> &getEndPos() const { return source.getEndPos(); }
    void trigger(const pair<int, int> &relativePos, Piece &origin);

    ~PieceOperateur();

    virtual void mapPosition(PieceConcrete &op, bool reverse) = 0;
    virtual void mapPosition(OperateurDeplacement &op, bool reverse) = 0;
    virtual void mapPosition(OperateurRotation &op, bool reverse) = 0;
    virtual void mapPosition(OperateurSymetrie &op, bool reverse) = 0;
    virtual void mapPosition(pair<int, int> &p, bool reverse) = 0;
    virtual void visit(PieceConcrete &p, Piece &origin, bool reverse) = 0;
    virtual void accept(PieceOperateur &v, Piece &origin, bool reverse) = 0;
    virtual void visit(OperateurDeplacement &x, Piece &origin, bool reverse) = 0;
    virtual void visit(OperateurRotation &x, Piece &origin, bool reverse) = 0;    
    virtual void visit(OperateurSymetrie &x, Piece &origin, bool reverse) = 0;
    virtual PieceOperateur *getSens(const pair<int, int> &coord, Piece &origin) const = 0;
    virtual void changeSens(OperateurDeplacement &x, bool reverse) = 0;
    virtual void changeSens(OperateurRotation &x, bool reverse) = 0;
    virtual void changeSens(OperateurSymetrie &x, bool reverse) = 0;

    virtual void clean() = 0;
};

class OperateurDeplacement : public PieceOperateur
{
public:
    OrientationDeplacement sens;
    OperateurDeplacement(Piece &source, const pair<int, int> &position, OrientationDeplacement sens);
    void accept(PieceOperateur &v, Piece &origin, bool reverse) override;
    void visit(OperateurDeplacement &x, Piece &origin, bool reverse) override;
    void visit(OperateurRotation &x, Piece &origin, bool reverse) override;
    void visit(OperateurSymetrie &x, Piece &origin, bool reverse) override;
    void visit(PieceConcrete &p, Piece &origin, bool reverse) override; 
    void mapPosition(PieceConcrete &op, bool reverse) override;
    void mapPosition(OperateurDeplacement &op, bool reverse) override;
    void mapPosition(OperateurRotation &op, bool reverse) override;
    void mapPosition(OperateurSymetrie &op, bool reverse) override;
    void mapPosition(pair<int, int> &p, bool reverse) override;
    PieceOperateur *getSens(const pair<int, int> &coord, Piece &origin) const override;
    ~OperateurDeplacement();
    OrientationDeplacement getReverseSens();

    void changeSens(OperateurDeplacement &x, bool reverse) override { (void)x; (void)reverse; };
    void changeSens(OperateurRotation &x, bool reverse) override { (void)x; (void)reverse; };
    void changeSens(OperateurSymetrie &x, bool reverse) override { (void)x; (void)reverse; };

    void clean() override;
};

class OperateurRotation : public PieceOperateur 
{
public:
    OrientationRotation sens;
    OperateurRotation(Piece & source, const pair<int,int> & position, OrientationRotation sens);
    void visit(OperateurDeplacement &x, Piece &origin, bool reverse) override;
    void visit(OperateurRotation &x, Piece &origin, bool reverse) override;
    void visit(OperateurSymetrie &x, Piece &origin, bool reverse) override;
    void visit(PieceConcrete &p, Piece &origin, bool reverse) override;
    void accept(PieceOperateur &v, Piece &origin, bool reverse) override;
    void mapPosition(PieceConcrete &op, bool reverse) override;
    void mapPosition(OperateurDeplacement &op, bool reverse) override;
    void mapPosition(OperateurRotation &op, bool reverse) override;
    void mapPosition(OperateurSymetrie &op, bool reverse) override;
    void mapPosition(pair<int, int> &p, bool reverse) override;
    PieceOperateur *getSens(const pair<int, int> &coord, Piece &origin) const override;
    ~OperateurRotation();
    OrientationRotation getReverseSens();

    void changeSens(OperateurDeplacement &x, bool reverse) override;
    void changeSens(OperateurRotation &x, bool reverse) override { (void)x; (void)reverse; };
    void changeSens(OperateurSymetrie &x, bool reverse) override;

    void clean() override;
};

class OperateurSymetrie : public PieceOperateur 
{
public:
    OrientationSymetrie sens;
    OperateurSymetrie(Piece & source, const pair<int,int> & position, OrientationSymetrie sens);
    void visit(OperateurDeplacement &x, Piece &origin, bool reverse) override;
    void visit(OperateurRotation &x, Piece &origin, bool reverse) override;
    void visit(OperateurSymetrie &x, Piece &origin, bool reverse) override;
    void visit(PieceConcrete &p, Piece &origin, bool reverse) override;
    void accept(PieceOperateur &v, Piece &origin, bool reverse) override;
    void mapPosition(PieceConcrete &op, bool reverse) override;
    void mapPosition(OperateurDeplacement &op, bool reverse) override;
    void mapPosition(OperateurRotation &op, bool reverse) override;
    void mapPosition(OperateurSymetrie &op, bool reverse) override;
    void mapPosition(pair<int, int> &p, bool reverse) override;

    PieceOperateur *getSens(const pair<int, int> &coord, Piece &origin) const override;
    ~OperateurSymetrie();
    OrientationSymetrie getReverseSens();

    void changeSens(OperateurDeplacement &x, bool reverse) override;
    void changeSens(OperateurRotation &x, bool reverse) override;
    void changeSens(OperateurSymetrie &x, bool reverse) override { (void)x; (void)reverse; };

    void clean() override;
};

#endif