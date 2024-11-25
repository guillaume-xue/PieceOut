#ifndef ebaucheVue_hpp
#define ebaucheVue_hpp

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>

using namespace std;
using namespace sf;

class EbaucheVue
{
private:
  const int MARGIN_LEFT = 100, MARGIN_RIGHT = 100, MARGIN_TOP = 100, MARGIN_BOTTOM = 100;
  const int TILE_SIZE = 64;
  const int NB_COL = 8, NB_LIGNE = 10;
  unsigned int nbPix_x = MARGIN_LEFT + MARGIN_RIGHT + NB_COL * TILE_SIZE;
  unsigned int nbPix_y = MARGIN_TOP + MARGIN_BOTTOM + NB_LIGNE * TILE_SIZE;

  int trig_x = -1, trig_y = -1;
  string message = "Piece Out";

  vector<Drawable *> scene_generale;
  vector<Drawable *> scene_particuliere;

  Event event;

  Vector2i mousePos;
  Vector2f mouseWorldPos;

  RectangleShape centralPane;
  VertexArray trame;

  Texture texture_rouge;

public:
  EbaucheVue();
  void init();
  void draw(RenderWindow &window);
  void handleKeyboardEvent(RenderWindow &window);
  void handleMouseEvent(RenderWindow &window);
  void updateTitle(RenderWindow &window);
  void addSprite();
  void initTexture();
  void initCentralPane();
  void initTrame();
  void initWindow(RenderWindow &window);
};

#endif