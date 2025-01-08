#include "Maps.hpp"
#include "OperateurDeplacementFactory.hpp"
#include "OperateurRotationFactory.hpp"
#include "OperateurSymetrieFactory.hpp"

Maps *Maps::instance = nullptr;

static OperateurDeplacementFactory deplacementFactoryNORD = OperateurDeplacementFactory(NORD);
static OperateurDeplacementFactory deplacementFactorySUD = OperateurDeplacementFactory(SUD);
static OperateurDeplacementFactory deplacementFactoryEST = OperateurDeplacementFactory(EST);
static OperateurDeplacementFactory deplacementFactoryOUEST = OperateurDeplacementFactory(OUEST);
static OperateurRotationFactory rotationFactoryHORAIRE = OperateurRotationFactory(HORAIRE);
static OperateurRotationFactory rotationFactoryANTI_HORAIRE = OperateurRotationFactory(ANTI_HORAIRE);
static OperateurSymetrieFactory symetrieFactoryHORIZONTALE = OperateurSymetrieFactory(HORIZONTALE);
static OperateurSymetrieFactory symetrieFactoryVERTICALE = OperateurSymetrieFactory(VERTICALE);


Maps::Maps()
{
    // cout << "Maps created" << endl;
}
Maps::~Maps()
{
    cout << "Maps deleted" << endl;
}

Maps *Maps::getInstance()
{
    if (instance == nullptr)
    {
        instance = new Maps();
    }
    return instance;
}

void Maps::destroyInstance()
{
    if (instance != nullptr)
    {
        instance->clean();
        delete instance;
        instance = nullptr;
    }
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
    Piece *p = deplacementFactoryEST.createPiece(*piece, {0, 0});
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
    Piece *p = deplacementFactoryOUEST.createPiece(*piece, {0, 0});
    Piece *p2 = deplacementFactoryNORD.createPiece(*p, {2, 0});
    Piece *p3 = deplacementFactorySUD.createPiece(*p2, {0, 2});
    Piece *p4 = deplacementFactoryEST.createPiece(*p3, {2, 2});
    pieces.push_back(p4);
    piecesEnd.push_back(p4);

    vector<pair<int, int>> coords2{{6, 7}, {7, 7}, {8, 7}};
    PieceConcrete *piece2 = new PieceConcrete(coords2, this);
    Piece *p5 = rotationFactoryHORAIRE.createPiece(*piece2, {6, 7});
    Piece *p6 = rotationFactoryANTI_HORAIRE.createPiece(*p5, {7, 7});
    Piece *p7 = deplacementFactoryOUEST.createPiece(*p6, {8, 7});
    pieces.push_back(p7);

    vector<pair<int, int>> coords3{{1, 7}, {2, 6}, {0, 5}, {0, 9}, {0, 7}};
    PieceConcrete *piece3 = new PieceConcrete(coords3, this);
    Piece *p8 = deplacementFactoryNORD.createPiece(*piece3, {0, 9});
    Piece *p9 = symetrieFactoryHORIZONTALE.createPiece(*p8, {1, 7});
    Piece *p10 = symetrieFactoryVERTICALE.createPiece(*p9, {2, 6});

    pieces.push_back(p10);

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


void Maps::map1()
{
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

    vector<pair<int, int>> coords{  {2, 5},
                                    {2 ,6}};
    PieceConcrete *piece = new PieceConcrete(coords, this);
    piece->endPos = {{2, 0}, {2, 1}};

    Piece *p = deplacementFactoryNORD.createPiece(*piece, {2, 5});
    Piece *p2 = deplacementFactorySUD.createPiece(*p, {2, 6});
    pieces.push_back(p2);
    piecesEnd.push_back(p2);

    vector<pair<int, int>> coords2{ {1, 2}, 
                                    {1, 3}, {2, 3}, 
                                    {1, 4}};
    PieceConcrete *piece2 = new PieceConcrete(coords2, this);
    Piece *p3 = rotationFactoryANTI_HORAIRE.createPiece(*piece2, {1, 3});
    pieces.push_back(p3);

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
    Piece *p = deplacementFactoryNORD.createPiece(*piece, {1, 0});
    Piece *p2 = deplacementFactorySUD.createPiece(*p, {1, 2});
    Piece *p3 = rotationFactoryANTI_HORAIRE.createPiece(*p2, {1, 1});
    pieces.push_back(p3);
    piecesEnd.push_back(p3);

    vector<pair<int, int>> coords2{{2, 0}, {2, 1}, {2, 2}, {3, 0}};
    PieceConcrete *piece2 = new PieceConcrete(coords2, this);
    piece2->endPos = {{3, 4}, {3, 5}, {3, 6}, {2, 6}};
    Piece *p4 = deplacementFactoryNORD.createPiece(*piece2, {2, 0});
    Piece *p5 = deplacementFactorySUD.createPiece(*p4, {2, 2});
    Piece *p6 = rotationFactoryANTI_HORAIRE.createPiece(*p5, {2, 1});
    pieces.push_back(p6);
    piecesEnd.push_back(p6);

    vector<pair<int, int>> coords3{{3, 1}, {4, 0}, {4, 1}, {4, 2}};
    PieceConcrete *piece3 = new PieceConcrete(coords3, this);
    piece3->endPos = {{1, 4}, {1, 5}, {1, 6}, {2, 5}};
    Piece *p7 = deplacementFactoryNORD.createPiece(*piece3, {4, 0});
    Piece *p8 = deplacementFactorySUD.createPiece(*p7, {4, 2});
    Piece *p9 = rotationFactoryANTI_HORAIRE.createPiece(*p8, {4, 1});
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
    Piece *p = deplacementFactoryNORD.createPiece(*piece, {1, 4});
    Piece *p2 = deplacementFactoryEST.createPiece(*p, {2, 4});
    Piece *p3 = deplacementFactoryOUEST.createPiece(*p2, {2, 5});
    Piece *p4 = deplacementFactorySUD.createPiece(*p3, {1, 5});
    pieces.push_back(p4);
    piecesEnd.push_back(p4);

    vector<pair<int, int>> coords2{{2, 0}, {2, 1}, {2, 2}, {3, 2}};
    PieceConcrete *piece2 = new PieceConcrete(coords2, this);
    Piece *p5 = deplacementFactoryNORD.createPiece(*piece2, {2, 0});
    Piece *p6 = deplacementFactorySUD.createPiece(*p5, {2, 2});
    Piece *p7 = symetrieFactoryHORIZONTALE.createPiece(*p6, {2, 1});
    pieces.push_back(p7);

    vector<pair<int, int>> coords3{{5, 2}, {5, 3}, {5, 4}};
    PieceConcrete *piece3 = new PieceConcrete(coords3, this);
    Piece *p8 = deplacementFactoryNORD.createPiece(*piece3, {5, 2});
    Piece *p9 = deplacementFactorySUD.createPiece(*p8, {5, 4});
    pieces.push_back(p9);

    vector<pair<int, int>> coords4{{4, 3}, {4, 4}, {4, 5}, {3, 5}};
    PieceConcrete *piece4 = new PieceConcrete(coords4, this);
    Piece *p10 = deplacementFactoryNORD.createPiece(*piece4, {4, 3});
    Piece *p11 = deplacementFactorySUD.createPiece(*p10, {4, 5});
    Piece *p12 = rotationFactoryANTI_HORAIRE.createPiece(*p11, {4, 4});
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

