#include "PieceController.hpp"

PieceController::PieceController(int pos_x, int pos_y, float size) : vue(pos_x, pos_y, size) {}

PieceController::~PieceController()
{
  for (Piece *piece : pieces)
  {
    delete piece;
  }
}

void PieceController::addPiece(Piece *piece)
{
  pieces.push_back(piece);
}

void PieceController::handleEvent(Event &event)
{
  // Gérer les événements utilisateur, comme les clics de souris ou les touches du clavier
  // Exemple :
  if (event.type == Event::MouseButtonPressed)
  {
    // Déplacer une pièce en fonction de la position de la souris
  }
}

void PieceController::update()
{
  // Mettre à jour les modèles si nécessaire
}