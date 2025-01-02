#include "Maps.hpp"

Maps::Maps()
{
    cout << "Maps created" << endl;
}

void Maps::clean(){
    for (Piece *p : pieces)
    {
        delete p;
    }
    for (Actions *a : actions)
    {
        delete a;
    }
    actions.clear();
    plateauSet.clear();
    pieces.clear();
    plateau.clear();
    sizePlateau = {0, 0};
}

pair<int, int> findMaxFirstAndSecond(const vector<pair<int, int>> &vec)
{
    int maxFirst = INT_MIN;
    int maxSecond = INT_MIN;

    for (const auto &p : vec)
    {
        if (p.first > maxFirst)
        {
            maxFirst = p.first;
        }
        if (p.second > maxSecond)
        {
            maxSecond = p.second;
        }
    }

    return {maxFirst + 1, maxSecond + 1};
}

void Maps::map1()
{
    clean();

    vector<pair<int, int>> coords{{0, 0}};
    PieceConcrete *piece = new PieceConcrete(coords, this);
    Piece *p = new OperateurDeplacement(*piece, {0, 0}, EST);
    pieces.push_back(p);

    vector<pair<int, int>> coords2{{3, 0}};
    PieceConcrete *piece2 = new PieceConcrete(coords2, this);
    Piece *p2 = new OperateurDeplacement(*piece2, {3, 0}, OUEST);
    pieces.push_back(p2);

    plateau = {{0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}};
    for (const auto &coord : plateau)
    {
        plateauSet.insert(coord);
    }
    sizePlateau = findMaxFirstAndSecond(plateau);

}

void Maps::map2()
{
    clean();
    
    vector<pair<int, int>> coords{{0, 0}, {1, 0}, {2, 0}, 
                                  {0, 1}, {1, 1}, {2, 1}, 
                                  {0, 2}, {1, 2}, {2, 2}};
    PieceConcrete *piece = new PieceConcrete(coords, this);
    Piece *p = new OperateurDeplacement(*piece, {0, 0}, OUEST);
    Piece *p2 = new OperateurDeplacement(*p, {2, 0}, NORD);
    Piece *p3 = new OperateurDeplacement(*p2, {0, 2}, SUD);
    Piece *p4 = new OperateurDeplacement(*p3, {2, 2}, EST);
    pieces.push_back(p4);

    pieces.push_back(R_rota_oneDir(this));

    plateau = {{0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 0}, {7, 0}, {8, 0}, {9, 0},
               {0, 1}, {1, 1}, {2, 1}, {3, 1}, {4, 1}, {5, 1}, {6, 1}, {7, 1}, {8, 1}, {9, 1},
               {0, 2}, {1, 2}, {2, 2}, {3, 2}, {4, 2}, {5, 2}, {6, 2}, {7, 2}, {8, 2}, {9, 2},
               {0, 3}, {1, 3}, {2, 3}, {3, 3}, {4, 3}, {5, 3}, {6, 3}, {7, 3}, {8, 3}, {9, 3},
               {0, 4}, {1, 4}, {2, 4}, {3, 4}, {4, 4}, {5, 4}, {6, 4}, {7, 4}, {8, 4}, {9, 4},
               {0, 5}, {1, 5}, {2, 5}, {3, 5}, {4, 5}, {5, 5}, {6, 5}, {7, 5}, {8, 5}, {9, 5},
               {0, 6}, {1, 6}, {2, 6}, {3, 6}, {4, 6}, {5, 6}, {6, 6}, {7, 6}, {8, 6}, {9, 6},
               {0, 7}, {1, 7}, {2, 7}, {3, 7}, {4, 7}, {5, 7}, {6, 7}, {7, 7}, {8, 7}, {9, 7},
               {0, 8}, {1, 8}, {2, 8}, {3, 8}, {4, 8}, {5, 8}, {6, 8}, {7, 8}, {8, 8}, {9, 8},
               {0, 9}, {1, 9}, {2, 9}, {3, 9}, {4, 9}, {5, 9}, {6, 9}, {7, 9}, {8, 9}, {9, 9}};
    for (const auto &coord : plateau)
    {
        plateauSet.insert(coord);
    }
    sizePlateau = findMaxFirstAndSecond(plateau);
}

void Maps::trigger(const pair<int, int> &relativePos)
{
    for (Piece *p : pieces)
    {
        // cout << "Maps::trigger" << endl;
        p->trigger(relativePos);
    }
    if(!actions.empty()){
        if(!verify(actions.back())){
            cout << "Maps::trigger: invalid move" << endl;
            undo();
        }
    }
    
}

void Maps::undo()
{
    if(actions.empty()){
        return;
    }
    actions.back()->getOrigin()->reAccept(actions.back()->getPiece(), *actions.back()->getOrigin());
}

bool Maps::verify(Actions *origin)
{
    set<pair<int, int>> visited;
    for (Piece *p : pieces)
    {
        if (p != origin->getOrigin())
        {
            Piece *tmp = p;
            while(true){
                if(PieceConcrete *piece = dynamic_cast<PieceConcrete *>(tmp)){
                    for (const auto &coord : piece->getCoordinates())
                    {
                        visited.insert(coord);
                    }
                    break;
                }else{
                    if(OperateurDeplacement *op = dynamic_cast<OperateurDeplacement *>(tmp))
                        tmp = &op->source;
                    if(OperateurRotation *op = dynamic_cast<OperateurRotation *>(tmp))
                        tmp = &op->source;
                    // if(OperateurSymetrie *op = dynamic_cast<OperateurSymetrie *>(tmp))
                    //     tmp = &op->source;
                }
            }
        }
    }
    for (const auto &coord : origin->getPieceConcrete().getCoordinates())
    {
        if(visited.count(coord) > 0){
            return false;
        }
        if(plateauSet.count(coord) == 0){
            return false;
        }
    }
    return true;
}

Piece *R_rota_oneDir(Maps *map){
    vector<pair<int, int>> coords{{6, 7}, {7, 7}, {8, 7}};
    PieceConcrete *piece = new PieceConcrete(coords, map);
    Piece *p = new OperateurRotation(*piece, {6, 7}, HORAIRE);
    Piece *p2 = new OperateurRotation(*p, {7, 7}, ANTI_HORAIRE);
    Piece *p3 = new OperateurDeplacement(*p2, {8, 7}, OUEST);
    return p3;
}