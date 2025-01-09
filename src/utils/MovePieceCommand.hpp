#ifndef MOVEPIECECOMMAND_HPP
#define MOVEPIECECOMMAND_HPP

#include "Command.hpp"
#include "../models/Piece.hpp"


class MovePieceCommand : public Command
{
private:
    Piece *piece;
    PieceConcrete &pieceConcrete;
    PieceOperateur &pieceOperateur;

public:
    MovePieceCommand(Piece *piece, PieceConcrete &pieceConcrete, PieceOperateur &pieceOperateur)
        : piece{piece}, pieceConcrete{pieceConcrete}, pieceOperateur{pieceOperateur} {}

    ~MovePieceCommand() {}

    void execute() override;

    void undoMove() override;

    Piece *getPiece() { return piece; }
    PieceConcrete &getPieceConcrete() { return pieceConcrete; }
    PieceOperateur &getPieceOperateur() { return pieceOperateur; }

};

#endif