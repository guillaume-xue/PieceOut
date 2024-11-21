#ifndef MouseController_hpp
#define MouseController_hpp

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>

using namespace std;
using namespace sf;

class MouseController : public Mouse
{
private:
  RenderWindow &window;
  Vector2i mousePos;
  Vector2f mouseWorldPos;

public:
  MouseController();
  MouseController(RenderWindow &window);
  ~MouseController();
  void handleMousePress();
  Vector2i const getMousePos();
  Vector2f const getMouseWorldPos();
};

#endif