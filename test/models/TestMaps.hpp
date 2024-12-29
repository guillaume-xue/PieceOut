#ifndef __TESTMAPS_HPP
#define __TESTMAPS_HPP

#include "../../src/models/Maps.hpp"

void testMap()
{
  Maps map;
  map.map1();
  for (auto x : map.getPlateau())
    cout << x.first << " " << x.second << endl;
  cout << "---------------" << endl;
  for (auto x : map.getPieces()[0]->getCoordinates())
    cout << x.first << " " << x.second << endl;
}

#endif