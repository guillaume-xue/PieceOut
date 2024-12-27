#include "Maps.hpp"

Maps::Maps()
{
    init();
}

void Maps::init()
{
    cout << "init" << endl;
    plateau = {{0, 0}, {0, 1}, {0, 2}, {0, 3}};
}