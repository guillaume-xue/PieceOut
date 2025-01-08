#ifndef __HEADERCONTROLLER_HPP__
#define __HEADERCONTROLLER_HPP__

#include "../views/HeaderVue.hpp"
#include "../controllers/MenuController.hpp"
#include "../utils/Observer.hpp"

class HeaderController: public Observer
{
private:
  static HeaderController *instance;
  HeaderController();
  ~HeaderController();

  MouseController *mouseController;
  MenuController *menuController;
  Maps *map;
  MapVue *mapVue;
  HeaderVue *headerVue;

public:
  static HeaderController *getInstance();
  HeaderController(const HeaderController &) = delete;
  void operator=(const HeaderController &) = delete;
  static void destroyInstance();
  void init(MouseController *mouseController, MenuController *menuController, Maps *map, MapVue *mapVue, HeaderVue *headerVue);
  void update() override;
};

#endif 