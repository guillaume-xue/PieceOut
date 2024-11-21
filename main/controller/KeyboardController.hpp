#ifndef KeyboardController_hpp
#define KeyboardController_hpp

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>

using namespace std;
using namespace sf;

class KeyboardController : public Keyboard
{
private:
  RenderWindow &window;
  Event event;

public:
  KeyboardController();
  KeyboardController(RenderWindow &window);
  ~KeyboardController();
  void handleKeyPress(vector<Drawable *> &scene_generale, vector<Drawable *> &scene_particuliere);
};

#endif