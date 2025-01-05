#include "Maps.hpp"

Maps::Maps()
{
    cout << "Maps created" << endl;
}

void Maps::clean(){
    for (Piece *p : pieces)
    {
        p->clean();
    }
    for (Actions *a : actions)
    {
        a->clean();
        delete a;
    }
    actions.clear();
    plateauSet.clear();
    pieces.clear();
    plateau.clear();
    piecesEnd.clear();
    sizePlateau = {};
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

void Maps::map8()
{
    vector<pair<int, int>> coords{{0, 0}};
    PieceConcrete *piece = new PieceConcrete(coords, this);
    piece->endPos = {{4, 0}};
    Piece *p = new OperateurDeplacement(*piece, {0, 0}, EST);
    pieces.push_back(p);
    piecesEnd.push_back(p);

    plateau = {{0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}};
    for (const auto &coord : plateau)
    {
        plateauSet.insert(coord);
    }
    sizePlateau = findMaxFirstAndSecond(plateau);
}

void Maps::map9()
{
    vector<pair<int, int>> coords{{0, 0}, {1, 0}, {2, 0}, 
                                  {0, 1}, {1, 1}, {2, 1}, 
                                  {0, 2}, {1, 2}, {2, 2}};
    PieceConcrete *piece = new PieceConcrete(coords, this);
    piece->endPos = {{-1, -1}};
    Piece *p = new OperateurDeplacement(*piece, {0, 0}, OUEST);
    Piece *p2 = new OperateurDeplacement(*p, {2, 0}, NORD);
    Piece *p3 = new OperateurDeplacement(*p2, {0, 2}, SUD);
    Piece *p4 = new OperateurDeplacement(*p3, {2, 2}, EST);
    pieces.push_back(p4);
    piecesEnd.push_back(p4);
    pieces.push_back(R_rota_oneDir(this));
    pieces.push_back(L_rota_sym_oneDir(this));

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

bool Maps::isEnd(){
    for (Piece *p : piecesEnd)
    {
        set <pair<int, int>> visited;
        for (const auto &coord : p->getEndPos())
        {
            visited.insert(coord);
        }
        for (const auto &coord : p->getCoordinates())
        {
            if(visited.count(coord) == 0){
                return false;
                break;
            }
        }
    }
    return true;
}

void Maps::undo()
{
    if(actions.empty()){
        return;
    }
    actions.back()->getOrigin()->accept(actions.back()->getPiece(), *actions.back()->getOrigin(), true);
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
                    if(OperateurSymetrie *op = dynamic_cast<OperateurSymetrie *>(tmp))
                        tmp = &op->source;
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

Piece *L_rota_sym_oneDir(Maps *map){
    vector<pair<int, int>> coords{{1, 7}, {2, 6}, {0, 5}, {0, 9}, {0, 7}};
    PieceConcrete *piece = new PieceConcrete(coords, map);
    Piece *p = new OperateurDeplacement(*piece, {0, 9}, NORD);
    Piece *p2 = new OperateurSymetrie(*p, {1, 7}, HORIZONTALE);
    Piece *p3 = new OperateurSymetrie(*p2, {2, 6}, VERTICALE);
    return p3;
}


void Maps::map1()
{
    vector<pair<int, int>> coords{  {2, 5},
                                    {2 ,6}};
    PieceConcrete *piece = new PieceConcrete(coords, this);
    piece->endPos = {{2, 0}, {2, 1}};
    Piece *p = new OperateurDeplacement(*piece, {2, 5}, NORD);
    Piece *p2 = new OperateurDeplacement(*p, {2, 6}, SUD);
    pieces.push_back(p2);
    piecesEnd.push_back(p2);
    vector<pair<int, int>> coords2{ {1, 2}, 
                                    {1, 3}, {2, 3}, 
                                    {1, 4}};
    PieceConcrete *piece2 = new PieceConcrete(coords2, this);
    Piece *p3 = new OperateurRotation(*piece2, {1, 3}, ANTI_HORAIRE);
    pieces.push_back(p3);

    plateau = {                 {2, 0},
                                {2, 1},
                        {1, 2}, {2, 2},
                {0, 3}, {1, 3}, {2, 3},
                        {1, 4}, {2, 4},
                                {2, 5},
                                {2, 6}};
    
    for (const auto &coord : plateau)
    {
        plateauSet.insert(coord);
    }
    sizePlateau = findMaxFirstAndSecond(plateau);
}

void Maps::map2()
{
    plateau = {         {1, 0}, {2, 0}, {3, 0}, {4, 0},
                        {1, 1}, {2, 1}, {3, 1}, {4, 1},
                        {1, 2}, {2, 2}, {3, 2}, {4, 2},
                {0, 3}, {1, 3}, {2, 3}, {3, 3}, {4, 3}, {5, 3},
                        {1, 4}, {2, 4}, {3, 4}, {4, 4},
                        {1, 5}, {2, 5}, {3, 5}, {4, 5},
                        {1, 6}, {2, 6}, {3, 6}, {4, 6}};
    
    for (const auto &coord : plateau)
    {
        plateauSet.insert(coord);
    }
    sizePlateau = findMaxFirstAndSecond(plateau);

    vector<pair<int, int>> coords{{1, 0}, {1, 1}, {1, 2}};
    PieceConcrete *piece = new PieceConcrete(coords, this);
    piece->endPos = {{4, 4}, {4, 5}, {4, 6}};
    Piece *p = new OperateurDeplacement(*piece, {1, 0}, NORD);
    Piece *p2 = new OperateurDeplacement(*p, {1, 2}, SUD);
    Piece *p3 = new OperateurRotation(*p2, {1, 1}, ANTI_HORAIRE);
    pieces.push_back(p3);
    piecesEnd.push_back(p3);

    vector<pair<int, int>> coords2{{2, 0}, {2, 1}, {2, 2}, {3, 0}};
    PieceConcrete *piece2 = new PieceConcrete(coords2, this);
    piece2->endPos = {{3, 4}, {3, 5}, {3, 6}, {2, 6}};
    Piece *p4 = new OperateurDeplacement(*piece2, {2, 0}, NORD);
    Piece *p5 = new OperateurDeplacement(*p4, {2, 2}, SUD);
    Piece *p6 = new OperateurRotation(*p5, {2, 1}, ANTI_HORAIRE);
    pieces.push_back(p6);
    piecesEnd.push_back(p6);

    vector<pair<int, int>> coords3{{3, 1}, {4, 0}, {4, 1}, {4, 2}};
    PieceConcrete *piece3 = new PieceConcrete(coords3, this);
    piece3->endPos = {{1, 4}, {1, 5}, {1, 6}, {2, 5}};
    Piece *p7 = new OperateurDeplacement(*piece3, {4, 0}, NORD);
    Piece *p8 = new OperateurDeplacement(*p7, {4, 2}, SUD);
    Piece *p9 = new OperateurRotation(*p8, {4, 1}, ANTI_HORAIRE);
    pieces.push_back(p9);
    piecesEnd.push_back(p9);
}

void Maps::map3()
{
    plateau = { {0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0},
                {0, 1}, {1, 1}, {2, 1}, {3, 1}, {4, 1}, {5, 1},
                        {1, 2}, {2, 2}, {3, 2}, {4, 2}, {5, 2},
                        {1, 3}, {2, 3}, {3, 3}, {4, 3}, {5, 3},
                        {1, 4}, {2, 4}, {3, 4}, {4, 4}, {5, 4},
                        {1, 5}, {2, 5}, {3, 5}, {4, 5}, {5, 5}};
    
    for (const auto &coord : plateau)
    {
        plateauSet.insert(coord);
    }
    sizePlateau = findMaxFirstAndSecond(plateau);

    vector<pair<int, int>> coords{{1, 4}, {1, 5}, {2, 4}, {2, 5}};
    PieceConcrete *piece = new PieceConcrete(coords, this);
    piece->endPos = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};
    Piece *p = new OperateurDeplacement(*piece, {1, 4}, NORD);
    Piece *p2 = new OperateurDeplacement(*p, {2, 4}, EST);
    Piece *p3 = new OperateurDeplacement(*p2, {2, 5}, SUD);
    Piece *p4 = new OperateurDeplacement(*p3, {1, 5}, OUEST);
    pieces.push_back(p4);
    piecesEnd.push_back(p4);

    vector<pair<int, int>> coords2{{2, 0}, {2, 1}, {2, 2}, {3, 2}};
    PieceConcrete *piece2 = new PieceConcrete(coords2, this);
    Piece *p5 = new OperateurDeplacement(*piece2, {2, 0}, NORD);
    Piece *p6 = new OperateurDeplacement(*p5, {2, 2}, SUD);
    Piece *p7 = new OperateurSymetrie(*p6, {2, 1}, HORIZONTALE);
    pieces.push_back(p7);

    vector<pair<int, int>> coords3{{5, 2}, {5, 3}, {5, 4}};
    PieceConcrete *piece3 = new PieceConcrete(coords3, this);
    Piece *p8 = new OperateurDeplacement(*piece3, {5, 2}, NORD);
    Piece *p9 = new OperateurDeplacement(*p8, {5, 4}, SUD);
    pieces.push_back(p9);

    vector<pair<int, int>> coords4{{4, 3}, {4, 4}, {4, 5}, {3, 5}};
    PieceConcrete *piece4 = new PieceConcrete(coords4, this);
    Piece *p10 = new OperateurDeplacement(*piece4, {4, 3}, NORD);
    Piece *p11 = new OperateurDeplacement(*p10, {4, 5}, SUD);
    Piece *p12 = new OperateurRotation(*p11, {4, 4}, ANTI_HORAIRE);
    pieces.push_back(p12);

}

void Maps::map4()
{

}

void Maps::map5()
{

}

void Maps::map6()
{

}

void Maps::map7()
{

}

