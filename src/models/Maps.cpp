#include "Maps.hpp"

Maps::Maps()
{
    cout << "Maps created" << endl;
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
    actions.clear();
    plateauSet.clear();
    pieces.clear();
    plateau.clear();
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
    actions.clear();
    plateauSet.clear();
    pieces.clear();
    plateau.clear();
    vector<pair<int, int>> coords{{0, 0}, {1, 0}, {2, 0}, 
                                  {0, 1}, {1, 1}, {2, 1}, 
                                  {0, 2}, {1, 2}, {2, 2}};
    PieceConcrete *piece = new PieceConcrete(coords, this);
    Piece *p = new OperateurDeplacement(*piece, {0, 0}, OUEST);
    Piece *p2 = new OperateurDeplacement(*p, {2, 0}, NORD);
    Piece *p3 = new OperateurDeplacement(*p2, {0, 2}, SUD);
    Piece *p4 = new OperateurDeplacement(*p3, {2, 2}, EST);
    pieces.push_back(p4);

    plateau = {{0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0},
               {0, 1}, {1, 1}, {2, 1}, {3, 1}, {4, 1},
               {0, 2}, {1, 2}, {2, 2}, {3, 2}, {4, 2},
               {0, 3}, {1, 3}, {2, 3}, {3, 3}, {4, 3},
               {0, 4}, {1, 4}, {2, 4}, {3, 4}, {4, 4}}; 
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
            actions.back()->getOrigin()->reAccept(actions.back()->getPiece(), *actions.back()->getOrigin());
        }
    }
    
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
                    // if(OperateurRotation *op = dynamic_cast<OperateurRotation *>(tmp))
                    //     tmp = &op->source;
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