#include "MovePieceCommand.hpp"

void MovePieceCommand::execute()
{
    // piece->trigger(newPosition);
    // cout << "MovePieceCommand executed" << endl;
}

void MovePieceCommand::undoMove()
{
    piece->accept(pieceOperateur, *piece, true);
}

