#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;

// ce code a juste été écrit pour une étude de faisabilité. Il vous faudra structurer les choses à votre façon.
class PieceOperateur;
class Piece
{
public:
  virtual void trigger(const pair<int, int> &coord, Piece &origin) = 0;
  void trigger(const pair<int, int> &coord) { trigger(coord, *this); }
  virtual const vector<pair<int, int>> &getCoordinates() const = 0;
  virtual void accept(const PieceOperateur &v) = 0;
};

class PieceConcrete : public Piece
{
public:
  vector<pair<int, int>> coordinates;
  PieceConcrete(const vector<pair<int, int>> &coords) : coordinates(coords) {}
  const vector<pair<int, int>> &getCoordinates() const { return coordinates; }
  void trigger(const pair<int, int> &coord, Piece &origin) {}
  void accept(const PieceOperateur &v);
};

class OperateurDeplacement;
class PieceOperateur : public Piece
{
public:
  Piece &source;
  pair<int, int> position;
  PieceOperateur(Piece &source, const pair<int, int> &position)
      : source{source}, position{position} {}
  const vector<pair<int, int>> &getCoordinates() const { return source.getCoordinates(); }
  void trigger(const pair<int, int> &relativePos, Piece &origin)
  {
    if (relativePos == position)
      origin.accept(*this);
    else
      source.trigger(relativePos, origin);
  }

  virtual void mapPosition(pair<int, int> &) const = 0;
  virtual void visit(PieceConcrete &p) const
  {
    for (pair<int, int> &x : p.coordinates)
      mapPosition(x);
  }

  virtual void visit(OperateurDeplacement &) const = 0;
  // virtual void visit(OperateurRotation &) const =0;
  // virtual void visit(OperateurSymetrie &) const =0;

  virtual void accept(const PieceOperateur &v) = 0;
};
enum OrientationDeplacement
{
  NORD,
  SUD,
  EST,
  OUEST
};
class OperateurDeplacement : public PieceOperateur
{
public:
  OrientationDeplacement sens;
  OperateurDeplacement(Piece &source, const pair<int, int> &position, OrientationDeplacement sens) : PieceOperateur(source, position), sens{sens} {};
  virtual void accept(const PieceOperateur &v) { v.visit(*this); }
  virtual void visit(OperateurDeplacement &x) const
  {
    // le deplacement ne modifie pas le sens
    mapPosition(x.position);
    x.source.accept(*this);
  }

  OrientationDeplacement getSens() const { return sens; }
  // virtual void visit(OperateurRotation &x) const;
  // virtual void visit(OperateurSymetrie &x) const;

  virtual void mapPosition(pair<int, int> &pos) const
  {
    switch (sens)
    {
    case NORD:
      pos.second--;
      break;
    case SUD:
      pos.second++;
      break;
    case EST:
      pos.first++;
      break;
    case OUEST:
      pos.first--;
      break;
    }
  }
};

void PieceConcrete::accept(const PieceOperateur &v) { v.visit(*this); }

class PieceVue
{
private:
  Piece &piece;

  int pieceSize;
  int positionX;
  int positionY;

  Texture directionTexture;
  Texture rotateTexture;
  Texture symetricTexture;

  vector<Sprite> directionsSprite;
  Sprite rotateSprite;
  Sprite symetricSprite;

public:
  PieceVue(Piece &piece);
  ~PieceVue() { cout << "PieceVue deleted" << endl; }
  void init();
  void initTexture();
  void initSprite(float size);
  void draw(RenderWindow &window);
  void update();
};

PieceVue::PieceVue(Piece &piece) : piece(piece)
{
  cout << "PieceVue created" << endl;
  init();
}

void PieceVue::init()
{
  initTexture();
  initSprite(32);
}

void PieceVue::initTexture()
{
  if (!directionTexture.loadFromFile("resources/direction.png"))
  {
    cout << "Error loading direction.png" << endl;
  }
  if (!rotateTexture.loadFromFile("resources/rotate.png"))
  {
    cout << "Error loading rotate.png" << endl;
  }
  if (!symetricTexture.loadFromFile("resources/symetric.png"))
  {
    cout << "Error loading symetric.png" << endl;
  }
}

void PieceVue::initSprite(float size)
{
  float new_size = size / directionTexture.getSize().x;
  for (int i = 0; i < 4; ++i)
  {
    Sprite sprite;
    sprite.setTexture(directionTexture);
    sprite.setScale(new_size, new_size);
    sprite.setRotation(i * 90);
    directionsSprite.push_back(sprite);
  }
  rotateSprite.setTexture(rotateTexture);
  rotateSprite.setScale(new_size, new_size);
  symetricSprite.setTexture(symetricTexture);
  symetricSprite.setScale(new_size, new_size);
}

void PieceVue::draw(RenderWindow &window)
{
  int size = directionsSprite[0].getScale().x * directionTexture.getSize().x;
  int margin = 20;
  for (pair<int, int> x : piece.getCoordinates())
  {
    RectangleShape carre(Vector2f(size + margin, size + margin));
    carre.setFillColor(Color::Blue);                                          // Couleur du carré
    carre.setPosition(x.first * (size + margin), x.second * (size + margin)); // Position du carré
    window.draw(carre);
  }
  if (auto *op = dynamic_cast<OperateurDeplacement *>(&piece))
  {
    switch (op->getSens())
    {
    case NORD:
      directionsSprite[3].setPosition(op->position.first * 100 + (margin / 2), op->position.second * 100 + size + (margin / 2));
      window.draw(directionsSprite[3]);
      break;
    case SUD:
      directionsSprite[1].setPosition(op->position.first * 100 + size + (margin / 2), op->position.second * 100 + (margin / 2));
      window.draw(directionsSprite[1]);
      break;
    case EST: // On affiche la direction vers l'est
      directionsSprite[0].setPosition(op->position.first * 100 + (margin / 2), op->position.second * 100 + (margin / 2));
      window.draw(directionsSprite[0]);
      break;
    case OUEST: //
      directionsSprite[2].setPosition(op->position.first * 100 + size + (margin / 2), op->position.second * 100 + size + (margin / 2));
      window.draw(directionsSprite[2]);
      break;
    }
  }
}

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
