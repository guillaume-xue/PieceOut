#ifndef PIECE_HPP
#define PIECE_HPP

#include <utility>
#include <vector>
#include <iostream>
#include "Orientation.hpp"
using namespace std;

class PieceOperateur;
class Maps;

class Piece
{
public:
    virtual void trigger(const pair<int, int> &coord, Piece &origin) = 0;
    void trigger(const pair<int, int> &coord);
    virtual const vector<pair<int, int>> &getCoordinates() const = 0;
    virtual void accept(PieceOperateur &v, Piece &origin) = 0;
    virtual void reAccept(PieceOperateur &v, Piece &origin) = 0;
    virtual PieceOperateur *getSens(const pair<int, int> &coord, Piece &origin) const = 0;
    virtual ~Piece() { cout << "Piece deleted" << endl; }
};

class PieceConcrete : public Piece
{
public:
    vector<pair<int, int>> coordinates;
    Maps *maps;
    PieceConcrete(const vector<pair<int, int>> &coords, Maps *map);
    const vector<pair<int, int>> &getCoordinates() const override { return coordinates; }
    void trigger(const pair<int, int> &coord, Piece &origin) override;
    void accept(PieceOperateur &v, Piece &origin) override;
    void reAccept(PieceOperateur &v, Piece &origin) override;
    PieceOperateur *getSens(const pair<int, int> &coord, Piece &origin) const override;
    ~PieceConcrete() { cout << "PieceConcrete deleted" << endl; }
};

#endif