#ifndef __HEADERCONTROLLER_HPP__
#define __HEADERCONTROLLER_HPP__

#include "../views/HeaderVue.hpp"
#include "../controllers/MenuController.hpp"

class HeaderController
{
private:
public:
  HeaderController();
  ~HeaderController();
  void update(MouseController &mouseController, HeaderVue &headerVue, MenuController &menuController, Maps &map);
};

#endif // __HEADERCONTROLLER_HPP__