#include <SFML/Graphics.hpp>
#include <iostream>
#include "../../src/views/PieceVue.hpp"
using namespace std;
using namespace sf;

int main()
{
  // Parametres graphiques, à replacer au bon endroit
  int MARGIN_LEFT = 100, MARGIN_RIGHT = 100, MARGIN_TOP = 100, MARGIN_BOTTOM = 100;
  int TILE_SIZE = 64;
  int NB_COL = 8, NB_LIGNE = 10;
  unsigned int nbPix_x = MARGIN_LEFT + MARGIN_RIGHT + NB_COL * TILE_SIZE;
  unsigned int nbPix_y = MARGIN_TOP + MARGIN_BOTTOM + NB_LIGNE * TILE_SIZE;
  // définition d'un panneau "central"
  RectangleShape centralPane(Vector2f(NB_COL * TILE_SIZE, NB_LIGNE * TILE_SIZE));
  centralPane.setPosition(MARGIN_LEFT, MARGIN_TOP);
  centralPane.setFillColor(Color::White);
  vector<Drawable *> scene_generale;
  scene_generale.push_back(&centralPane);
  RenderWindow window{VideoMode{nbPix_x, nbPix_y}, "Piece Out"};

  vector<pair<int, int>> coords{{0, 0}, {0, 1}, {0, 2}, {1, 2}};
  PieceConcrete tetris_L(coords);
  Piece *p = new OperateurDeplacement{tetris_L, {0, 0}, EST};
  p = new OperateurDeplacement{*p, {0, 1}, SUD};
  PieceVue pieceVue(*p);

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

    // les affichages
    for (Drawable *x : scene_generale)
      window.draw(*x);

    pieceVue.draw(window);

    window.display();
  }
  // Remarquez que la destruction des objets n'est pas faites
  // et que dans ce code il ne suffit pas de détruire scene_generale et scene_particuliere car on y a ajouté des objets créés par new et d'autre déclarés dans un bloc... ce qui n'est pas malin.
  return EXIT_SUCCESS;
}
