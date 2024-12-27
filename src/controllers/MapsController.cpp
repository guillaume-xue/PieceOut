#include "MapsController.hpp"

MapsController::MapsController(int pos_x, int pos_y, float size) : vue(pos_x, pos_y, size) {}

MapsController::~MapsController() {}

void MapsController::handleEvent(Event &event)
{
  // Gérer les événements utilisateur, comme les clics de souris ou les touches du clavier
  // Exemple :
  if (event.type == Event::MouseButtonPressed)
  {
    // Ajouter ou supprimer un élément de la carte en fonction de la position de la souris
  }
}

void MapsController::update()
{
  // Mettre à jour le modèle si nécessaire
}

void MapsController::draw(RenderWindow &window)
{
  vue.draw(window, map);
}