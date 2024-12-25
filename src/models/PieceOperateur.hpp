#ifndef PIECEOPERATEUR_HPP
#define PIECEOPERATEUR_HPP

#include "Piece.hpp"

class OperateurDeplacement;
// class OperateurRotation;
// class OperateurSymetrie;

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
    virtual void visit(PieceConcrete &p) const;
    virtual void visit(OperateurDeplacement &) const = 0;
    // virtual void visit(OperateurRotation &) const =0;
    // virtual void visit(OperateurSymetrie &) const =0;
    virtual void accept(const PieceOperateur &v) = 0;
};

class OperateurDeplacement : public PieceOperateur
{
public:
    OrientationDeplacement sens;
    OperateurDeplacement(Piece &source, const pair<int, int> &position, OrientationDeplacement sens);
    virtual void accept(const PieceOperateur &v);
    virtual void mapPosition(pair<int, int> &pos) const;
    // void visit(OperateurSymetrie &x) const override;
    void visit(OperateurDeplacement &x) const override;
    // void visit(OperateurRotation &x) const override;
    OrientationDeplacement getSens(const pair<int, int> &coord, Piece &origin) const;

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