#include "../../src/views/MenuVue.hpp"
using namespace std;
using namespace sf;

int main()
{
  // Parametres graphiques, à replacer au bon endroit

  unsigned int nbPix_x = 858;
  unsigned int nbPix_y = 640;
  RenderWindow window{VideoMode{nbPix_x, nbPix_y}, "Piece Out"};
  MenuVue menuVue;
  menuVue.init(nbPix_x, nbPix_y, 96);

  while (window.isOpen())
  {
    Event event;

    while (window.pollEvent(event))
    {
      if (event.type == Event::Closed ||
          (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)) // fermeture de la fenêtre
        window.close();
    }

    window.clear(Color::Black);
    window.setView(window.getDefaultView());

    menuVue.draw(window);

    window.display();
  }
  // Remarquez que la destruction des objets n'est pas faites
  // et que dans ce code il ne suffit pas de détruire scene_generale et scene_particuliere car on y a ajouté des objets créés par new et d'autre déclarés dans un bloc... ce qui n'est pas malin.
  return EXIT_SUCCESS;
}
