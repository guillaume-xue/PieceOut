#ifndef PIECE_HPP
#define PIECE_HPP

#include <utility>
#include <vector>

using namespace std;

class PieceOperateur;

class Piece {
    public:
        virtual void trigger(const pair<int,int> & coord , Piece &origin) = 0;
        void trigger(const pair<int,int> & coord);
        virtual const vector<pair<int, int>>& getCoordinates() const = 0;
        virtual void accept(const PieceOperateur &v) = 0;
};

class PieceConcrete : public Piece {
    public:
        vector<pair<int, int>> coordinates;
        PieceConcrete(const vector<pair<int, int>>& coords);
        const vector<pair<int, int>>& getCoordinates() const { return coordinates; }
        void trigger(const pair<int,int> & coord, Piece &origin);
        void accept(const PieceOperateur & v);
};

#endif