#ifndef COMMAND_HPP
#define COMMAND_HPP

class Piece;
class PieceConcrete;
class PieceOperateur;
class Command
{
public:
    virtual ~Command() {}
    virtual void execute() = 0;
    virtual void undoMove() = 0;
    virtual Piece *getPiece() = 0;
    virtual PieceConcrete &getPieceConcrete() = 0;
    virtual PieceOperateur &getPieceOperateur() = 0;
};

#endif