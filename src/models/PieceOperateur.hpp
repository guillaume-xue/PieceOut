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

    // void mapPosition(PieceOperateur *x);
    // void mapPositionReverse(PieceOperateur *x);
    // void mapPosition(pair<int, int> &pos);
    // void mapPositionReverse(pair<int, int> &pos);
    virtual void mapPosition(PieceConcrete &op, bool reverse) = 0;
    virtual void mapPosition(OperateurDeplacement &op, bool reverse) = 0;
    virtual void mapPosition(OperateurRotation &op, bool reverse) = 0;
    virtual void mapPosition(OperateurSymetrie &op, bool reverse) = 0;
    virtual void mapPosition(pair<int, int> &p, bool reverse) = 0;
    virtual void visit(PieceConcrete &p, Piece &origin, bool reverse) = 0;
    // void reVisit(PieceConcrete &p, Piece &origin);
    // void visit(PieceOperateur *x, Piece &origin);
    // void reVisit(PieceOperateur *x, Piece &origin);  
    // void accept(PieceOperateur &v, Piece &origin) override;
    // void reAccept(PieceOperateur &v, Piece &origin) override;  
    virtual void accept(PieceOperateur &v, Piece &origin, bool reverse) = 0;
    virtual void visit(OperateurDeplacement &x, Piece &origin, bool reverse) = 0;
    // virtual void reVisit(OperateurDeplacement &x, Piece &origin) const = 0;
    virtual void visit(OperateurRotation &x, Piece &origin, bool reverse) = 0;
    // virtual void reVisit(OperateurRotation &x, Piece &origin) const = 0;
    virtual void visit(OperateurSymetrie &x, Piece &origin, bool reverse) = 0;
    virtual PieceOperateur *getSens(const pair<int, int> &coord, Piece &origin) const = 0;
    // virtual void accept(const PieceOperateur &v, Piece &origin) = 0;
    // void changeSensRot(PieceOperateur *x, OrientationRotation sens);

    virtual void changeSens(OperateurDeplacement &x, bool reverse) = 0;
    virtual void changeSens(OperateurRotation &x, bool reverse) = 0;
    virtual void changeSens(OperateurSymetrie &x, bool reverse) = 0;
};

class OperateurDeplacement : public PieceOperateur
{
public:
    OrientationDeplacement sens;
    OperateurDeplacement(Piece &source, const pair<int, int> &position, OrientationDeplacement sens);
    // void accept(const PieceOperateur &v, Piece &origin) override;
    // void mapPosition(pair<int, int> &pos) const override;
    // void mapPositionReverse(pair<int, int> &pos) const override;
    // void reVisit(OperateurDeplacement &x, Piece &origin) override;
    // virtual void visit(OperateurRotation &x, Piece &origin) const override {};
    // virtual void reVisit(OperateurRotation &x, Piece &origin) const override {};
    // void reAccept(const PieceOperateur &v, Piece &origin) override;
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
    ~OperateurDeplacement() { cout << "OperateurDeplacement deleted" << endl; }
    OrientationDeplacement getReverseSens();

    void changeSens(OperateurDeplacement &x, bool reverse) override {};
    void changeSens(OperateurRotation &x, bool reverse) override {};
    void changeSens(OperateurSymetrie &x, bool reverse) override {};
};

class OperateurRotation : public PieceOperateur 
{
public:
    OrientationRotation sens;
    OperateurRotation(Piece & source, const pair<int,int> & position, OrientationRotation sens);
    // void accept(const PieceOperateur &v, Piece &origin) override;
    // void mapPosition(pair<int, int> &pos) const override;
    // void mapPositionReverse(pair<int, int> &pos) const override;
    // void visit(OperateurDeplacement &x, Piece &origin) override {};
    // void reVisit(OperateurDeplacement &x, Piece &origin) override {};
    // // void visit(OperateurSymetrie &x) const override;
    // // void visit(OperateurDeplacement &x) const override;
    // void visit(OperateurRotation &x, Piece &origin) const override;
    // void reVisit(OperateurRotation &x, Piece &origin) const override;
    // void reAccept(const PieceOperateur &v, Piece &origin) override;
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
    ~OperateurRotation() { cout << "OperateurRotation deleted" << endl; }
    OrientationRotation getReverseSens();

    void changeSens(OperateurDeplacement &x, bool reverse) override;
    void changeSens(OperateurRotation &x, bool reverse) override {};
    void changeSens(OperateurSymetrie &x, bool reverse) override;
};

class OperateurSymetrie : public PieceOperateur 
{
public:
    OrientationSymetrie sens;
    OperateurSymetrie(Piece & source, const pair<int,int> & position, OrientationSymetrie sens);
    // virtual void accept(const PieceOperateur &v);
    // void visit(OperateurSymetrie &x) const override;
    // void visit(OperateurDeplacement &x) const override;
    // void visit(OperateurRotation &x) const override;
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
    ~OperateurSymetrie() { cout << "OperateurSymetrie deleted" << endl; }
    OrientationSymetrie getReverseSens();

    void changeSens(OperateurDeplacement &x, bool reverse) override;
    void changeSens(OperateurRotation &x, bool reverse) override;
    void changeSens(OperateurSymetrie &x, bool reverse) override {};
};

#endif