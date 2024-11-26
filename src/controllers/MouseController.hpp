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
  Vector2i mousePos;
  Vector2f mouseWorldPos;

public:
  MouseController();
  void updateMousePosition(RenderWindow &window);
  Vector2f getMouseWorldPos();
};

#endif