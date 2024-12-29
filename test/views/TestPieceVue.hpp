#ifndef TEST_PIECE_VUE_HPP
#define TEST_PIECE_VUE_HPP

#include "../../src/views/PieceVue.hpp"
using namespace std;
using namespace sf;

void testPieceVue()
{
  unsigned int nbPix_x = 858;
  unsigned int nbPix_y = 640;

  RenderWindow window{VideoMode{nbPix_x, nbPix_y}, "Piece Out"};

  vector<pair<int, int>> coords{{0, 0}, {0, 1}, {0, 2}, {1, 2}};
  PieceConcrete tetris_L(coords);
  Piece *p = new OperateurDeplacement{tetris_L, {0, 0}, EST};
  p = new OperateurDeplacement{*p, {0, 1}, SUD};
  p = new OperateurDeplacement{*p, {1, 2}, NORD};
  PieceVue pieceVue;
  pieceVue.init(100, 100, 32);

  while (window.isOpen())
  {
    Event event;

    while (window.pollEvent(event))
    {
      if (event.type == Event::Closed ||
          (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)) // fermeture de la fenêtre
        window.close();
    }

    window.clear(Color::White);
    window.setView(window.getDefaultView());

    pieceVue.draw(window, *p);

    window.display();
  }
  // Remarquez que la destruction des objets n'est pas faites
  // et que dans ce code il ne suffit pas de détruire scene_generale et scene_particuliere car on y a ajouté des objets créés par new et d'autre déclarés dans un bloc... ce qui n'est pas malin.
}

#endif