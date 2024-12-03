#ifndef MAPS
#define MAPS

#include "PieceOperateur.hpp"


class Maps
{
    private:
        
    public:
        const int TILE_SIZE = 50;
        int **map = nullptr;
        int nbCol = 0;
        int nbLigne = 0;
        Piece *piece;
        
        Maps();
        ~Maps() {cout << "Maps deleted" << endl;}

        void map1();

};


#endif 
 