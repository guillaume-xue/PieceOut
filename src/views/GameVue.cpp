#include "GameVue.hpp"

GameVue::GameVue()
{
  init();
}

GameVue::~GameVue()
{
  cout << "Destructeur GameVue" << endl;
}

void GameVue::init()
{
  RenderWindow window{VideoMode{nbPix_x, nbPix_y}, "Piece Out"};
  menuVue.init(nbPix_x, nbPix_y, 96);
  headerVue.init(nbPix_x, nbPix_y);

  while (window.isOpen())
  {
    Event event;

    while (window.pollEvent(event))
    {
      if (event.type == Event::Closed ||
          (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)) // fermeture de la fenêtre
        window.close();
    }

    draw(window);
  }
}

void GameVue::draw(RenderWindow &window)
{
  Color gray = Color(194, 197, 204, 255);
  window.clear(gray);
  window.setView(window.getDefaultView());
  menuVue.draw(window);
  headerVue.draw(window);
  window.display();
}
