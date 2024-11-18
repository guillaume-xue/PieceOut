#ifndef PIECEOPERATEUR_HPP
#define PIECEOPERATEUR_HPP

#include "Piece.hpp"

class OperateurDeplacement;

class PieceOperateur : public Piece {
    public:
        Piece & source;
        pair<int, int> position;
        PieceOperateur(Piece & source, const pair<int,int> & position);
        const vector<pair<int, int>>& getCoordinates() const {return source.getCoordinates();}
        void trigger(const pair<int,int> & relativePos, Piece &origin);
        
        virtual void mapPosition(pair<int, int> &) const = 0; 
        virtual void visit(PieceConcrete &p) const;
        virtual void visit(OperateurDeplacement &) const = 0;
        //virtual void visit(OperateurRotation &) const =0;
	    //virtual void visit(OperateurSymetrie &) const =0;
        virtual void accept(const PieceOperateur &v) = 0;
};

enum OrientationDeplacement {NORD, SUD, EST, OUEST};

class OperateurDeplacement : public PieceOperateur {
    public:
        OrientationDeplacement sens;
        OperateurDeplacement(Piece & source, const pair<int,int> & position, OrientationDeplacement sens);
        virtual void accept(const PieceOperateur &v);
        //virtual void visit(OperateurRotation &x) const;
	    //virtual void visit(OperateurSymetrie &x) const;
        virtual void mapPosition(pair<int, int> & pos) const;
        void visit(OperateurDeplacement &x) const override;
        
};

#endif