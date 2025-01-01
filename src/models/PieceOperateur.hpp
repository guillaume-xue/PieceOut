#ifndef PIECEOPERATEUR_HPP
#define PIECEOPERATEUR_HPP

#include "Piece.hpp"
#include "Maps.hpp"

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
    void trigger(const pair<int, int> &relativePos, Piece &origin);

    ~PieceOperateur() { cout << "PieceOperateur deleted" << endl; }

    virtual void mapPosition(pair<int, int> &) const = 0;
    virtual void mapPositionReverse(pair<int, int> &) const = 0;
    virtual void visit(PieceConcrete &p, Piece &origin) const;
    virtual void reVisit(PieceConcrete &p, Piece &origin) const;
    virtual void visit(OperateurDeplacement &x, Piece &origin) const = 0;
    virtual void reVisit(OperateurDeplacement &x, Piece &origin) const = 0;
    // virtual void visit(OperateurRotation &x) const =0;
    // virtual void visit(OperateurSymetrie &x) const =0;
    virtual void accept(const PieceOperateur &v, Piece &origin) = 0;
};

class OperateurDeplacement : public PieceOperateur
{
public:
    OrientationDeplacement sens;
    OperateurDeplacement(Piece &source, const pair<int, int> &position, OrientationDeplacement sens);
    virtual void accept(const PieceOperateur &v, Piece &origin) override;
    virtual void mapPosition(pair<int, int> &pos) const override;
    virtual void mapPositionReverse(pair<int, int> &pos) const override;
    // void visit(OperateurSymetrie &x) const override;
    void visit(OperateurDeplacement &x, Piece &origin) const override;
    void reVisit(OperateurDeplacement &x, Piece &origin) const override;
    void reAccept(const PieceOperateur &v, Piece &origin) override;
    // void visit(OperateurRotation &x) const override;
    OrientationDeplacement getSens(const pair<int, int> &coord, Piece &origin) const override;
    ~OperateurDeplacement() { cout << "OperateurDeplacement deleted" << endl; }
};

// class OperateurRotation : public PieceOperateur {
//     public:

//         OperateurRotation(Piece & source, const pair<int,int> & position);
//         virtual void accept(const PieceOperateur &v);
//         // void visit(OperateurSymetrie &x) const override;
//         // void visit(OperateurDeplacement &x) const override;
//         void visit(OperateurRotation &x) const override;
//         virtual void mapPosition(pair<int, int> & pos) const;
// };

// class OperateurSymetrie : public PieceOperateur {
//     public:
//         OperateurSymetrie(Piece & source, const pair<int,int> & position);
//         virtual void accept(const PieceOperateur &v);
//         void visit(OperateurSymetrie &x) const override;
//         // void visit(OperateurDeplacement &x) const override;
//         // void visit(OperateurRotation &x) const override;
//         virtual void mapPosition(pair<int, int> & pos) const;
// };

#endif