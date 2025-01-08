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
  static MouseController *instance;
  MouseController();
  ~MouseController();
public:
  static MouseController *getInstance();
  MouseController(const MouseController &) = delete;
  void operator=(const MouseController &) = delete;
  static void destroyInstance();
  void updateMousePosition(RenderWindow &window);
  Vector2f getMouseWorldPos();
};

#endif