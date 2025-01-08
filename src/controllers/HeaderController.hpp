#ifndef __HEADERCONTROLLER_HPP__
#define __HEADERCONTROLLER_HPP__

#include "../views/HeaderVue.hpp"
#include "../controllers/MenuController.hpp"

class HeaderController
{
private:
  static HeaderController *instance;
  HeaderController();
  ~HeaderController();

public:
  static HeaderController *getInstance();
  HeaderController(const HeaderController &) = delete;
  void operator=(const HeaderController &) = delete;
  static void destroyInstance();
  void update(MouseController *mouseController, HeaderVue &headerVue, MenuController *menuController, Maps &map, MapVue &mapVue);
};

#endif 