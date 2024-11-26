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
public:
  KeyboardController();
  void updateKeyboardEvent(RenderWindow &window);
  Event event;
};

#endif