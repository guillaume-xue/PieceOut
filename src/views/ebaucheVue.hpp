#ifndef ebaucheVue_hpp
#define ebaucheVue_hpp

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include "../controllers/MouseController.hpp"
#include "../controllers/KeyboardController.hpp"
#include "../models/Maps.hpp"

using namespace std;
using namespace sf;

class EbaucheVue
{
private:
  const int MARGIN_LEFT = 0, MARGIN_RIGHT = 0, MARGIN_TOP = 50, MARGIN_BOTTOM = 50;
  const int TILE_SIZE = 200;
  const int NB_COL = 3, NB_LIGNE = 3;
  unsigned int nbPix_x = MARGIN_LEFT + MARGIN_RIGHT + NB_COL * TILE_SIZE;
  unsigned int nbPix_y = MARGIN_TOP + MARGIN_BOTTOM + NB_LIGNE * TILE_SIZE;

  int trig_x = -1, trig_y = -1;
  string message = "Piece Out";

  vector<Drawable *> scene_generale;
  vector<Drawable *> scene_particuliere;
  vector<RectangleShape *> pieces;
  MouseController mouseController;
  KeyboardController keyboardController;

  bool isDragging = false;
  RectangleShape *selectedPiece = nullptr;
  Vector2f offset;

  RectangleShape centralPane;

  Texture homeTexture;

  Sprite homeButton;
  Text buttonText;

  Maps *map;

public:
  EbaucheVue();

  ~EbaucheVue() { cout << "EbaucheVue deleted" << endl; }

  void init();
  void initButton();
  void draw(RenderWindow &window);
  void addSprite();
  void initTexture();
  void initCentralPane();
  void initWindow(RenderWindow &window);
  void initSelectPlateau();
  void initNewTerrain();
};

#endif