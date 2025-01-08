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
  Event event;
  static KeyboardController *instance;
  KeyboardController();
  ~KeyboardController();

public:
  static KeyboardController *getInstance();
  KeyboardController(const KeyboardController &) = delete;
  void operator=(const KeyboardController &) = delete;
  static void destroyInstance();

  void updateKeyboardEvent(RenderWindow &window);

};

#endif