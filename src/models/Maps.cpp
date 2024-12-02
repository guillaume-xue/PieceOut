#include "Maps.hpp"
#include "iostream"
using namespace std;

Maps::Maps(){
    init();
}

void Maps::init(){
    vector<pair<int, int>> coords = { {0, 0} };
    PieceConcrete carre_1x1(coords);
    piece = new OperateurDeplacement(carre_1x1, {0, 0}, OUEST);
    
}

void Maps::map1(){
    nbCol = 6;
    nbLigne = 1;
    map = new int*[nbLigne];
    for (int i = 0; i < nbLigne; i++)
        map[i] = new int[nbCol];
    for (int i = 0; i < nbLigne; i++)
        for (int j = 0; j < nbCol; j++)
            map[i][j] = 0;
    map[nbLigne - 1][nbCol - 1] = 2;

    if(piece == nullptr)
        cout << "piece est null" << endl;
    
    // Ajouter la pièce sur la première case de la carte
    const vector<pair<int, int>>& coords = piece->getCoordinates();
    for (const auto& coord : coords) {
        cout << "(" << coord.first << ", " << coord.second << ")" << endl;
    }
    // for (const auto& coord : coords) {
    //     int x = coord.first;
    //     int y = coord.second;
    //     if (x >= 0 && x < nbCol && y >= 0 && y < nbLigne) {
    //         map[y][x] = 1;
    //     }
    // }
}