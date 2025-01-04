#include "PieceOperateur.hpp"

// PieceOperateur
PieceOperateur::PieceOperateur(Piece &source, const pair<int, int> &position)
    : source{source}, position{position} {}

void PieceOperateur::trigger(const pair<int, int> &relativePos, Piece &origin)
{
    if (relativePos == position) {
        origin.accept(*this, origin, false);
    } else {
        source.trigger(relativePos, origin);
    }
}

PieceOperateur* OperateurDeplacement::getSens(const pair<int, int> &coord, Piece &origin) const
{
    if(coord == position)
        return const_cast<OperateurDeplacement*>(this);
    else{
        return source.getSens(coord, origin);
    }
}
PieceOperateur* OperateurRotation::getSens(const pair<int, int> &coord, Piece &origin) const
{
    if(coord == position)
        return const_cast<OperateurRotation*>(this);
    else{
        return source.getSens(coord, origin);
    }
}
PieceOperateur* OperateurSymetrie::getSens(const pair<int, int> &coord, Piece &origin) const
{
    if(coord == position)
        return const_cast<OperateurSymetrie*>(this);
    else{
        return source.getSens(coord, origin);
    }
}

// OperateurDeplacement
OperateurDeplacement::OperateurDeplacement(Piece &source, const pair<int, int> &position, OrientationDeplacement sens)
    : PieceOperateur(source, position), sens{sens} {}

void OperateurDeplacement::visit(OperateurDeplacement &x, Piece &origin, bool reverse)
{
    mapPosition(x, reverse);    
    x.source.accept(*this, origin, reverse);
}

void OperateurDeplacement::visit(OperateurRotation &x, Piece &origin, bool reverse)
{
    mapPosition(x, reverse);    
    x.source.accept(*this, origin, reverse);
}

void OperateurDeplacement::visit(OperateurSymetrie &x, Piece &origin, bool reverse)
{
    mapPosition(x, reverse);    
    x.source.accept(*this, origin, reverse);
}

void OperateurDeplacement::visit(PieceConcrete &p, Piece &origin, bool reverse)
{
    mapPosition(p, reverse);
    if(reverse) {
        p.maps->getActions().pop_back();
    } else {
        Actions *action = new Actions(*this, &origin, p);
        p.maps->getActions().push_back(action);
    }
}

void OperateurDeplacement::accept(PieceOperateur &v, Piece &origin, bool reverse)
{
    v.visit(*this, origin, reverse);
}
void OperateurDeplacement::mapPosition(OperateurDeplacement &op, bool reverse)
{
    mapPosition(op.position, reverse);
}
void OperateurDeplacement::mapPosition(OperateurRotation &op, bool reverse)
{
    mapPosition(op.position, reverse);
}
void OperateurDeplacement::mapPosition(OperateurSymetrie &op, bool reverse)
{
    mapPosition(op.position, reverse);
}
void OperateurDeplacement::mapPosition(PieceConcrete &op, bool reverse)
{
    for (pair<int, int> &x : op.coordinates)
        mapPosition(x, reverse);
}
void OperateurDeplacement::mapPosition(pair<int, int> &p, bool reverse){
    OrientationDeplacement tmp = this->sens;
    if(reverse) tmp = getReverseSens();
    switch (tmp)
    {
    case NORD:
        p.second--;
        break;
    case SUD:
        p.second++;
        break;
    case EST:
        p.first++;
        break;
    case OUEST:
        p.first--;
        break;
    default:
        break;
    }
}

OrientationDeplacement OperateurDeplacement::getReverseSens(){
    switch(this->sens){
        case NORD:
            return SUD;
        case SUD:
            return NORD;
        case EST:
            return OUEST;
        default:
            return EST;
    }
}

// OperateurRotation
OperateurRotation::OperateurRotation(Piece &source, const pair<int, int> &position, OrientationRotation sens)
    : PieceOperateur(source, position), sens{sens} {}

void OperateurRotation::visit(OperateurDeplacement &x, Piece &origin, bool reverse)
{
    mapPosition(x, reverse);
    changeSens(x, reverse);    
    x.source.accept(*this, origin, reverse);
}

void OperateurRotation::visit(OperateurRotation &x, Piece &origin, bool reverse)
{
    mapPosition(x, reverse);    
    x.source.accept(*this, origin, reverse);
}

void OperateurRotation::visit(OperateurSymetrie &x, Piece &origin, bool reverse)
{
    mapPosition(x, reverse); 
    changeSens(x, reverse);   
    x.source.accept(*this, origin, reverse);
}

void OperateurRotation::visit(PieceConcrete &p, Piece &origin, bool reverse)
{
    mapPosition(p, reverse);
    if(reverse) {
        p.maps->getActions().pop_back();
    } else {
        Actions *action = new Actions(*this, &origin, p);
        p.maps->getActions().push_back(action);
    }
}

void OperateurRotation::accept(PieceOperateur &v, Piece &origin, bool reverse)
{
    v.visit(*this, origin, reverse);
}
void OperateurRotation::mapPosition(OperateurDeplacement &op, bool reverse)
{
    mapPosition(op.position, reverse);
}
void OperateurRotation::mapPosition(OperateurRotation &op, bool reverse)
{
    mapPosition(op.position, reverse);
}
void OperateurRotation::mapPosition(OperateurSymetrie &op, bool reverse)
{
    mapPosition(op.position, reverse);
}
void OperateurRotation::mapPosition(PieceConcrete &op, bool reverse)
{
    for (pair<int, int> &x : op.coordinates)
        mapPosition(x, reverse);
}
void OperateurRotation::mapPosition(pair<int, int> &p, bool reverse){
    int x = p.first;
    int y = p.second;
    int x_c = this->position.first;
    int y_c = this->position.second;
    x -= x_c;
    y -= y_c;
    int xtemp = x;
    int ytemp = y;
    OrientationRotation tmp = this->sens;
    if(reverse) tmp = getReverseSens();
    switch (tmp)
    {
    case HORAIRE:
        x = -ytemp;
        y = xtemp;
        break;
    case ANTI_HORAIRE:
        x = ytemp;
        y = -xtemp;
        break;
    default:
        break;
    }
    x += x_c;
    y += y_c;
    p = {x, y};
}

OrientationRotation OperateurRotation::getReverseSens(){
    switch (this->sens)
    {
    case HORAIRE:
        return ANTI_HORAIRE;
    default:
        return HORAIRE;
    }
}

void OperateurRotation::changeSens(OperateurDeplacement &x, bool reverse)
{
    OrientationRotation tmp = this->sens;
    if(reverse) tmp = getReverseSens();
    if(tmp == ANTI_HORAIRE){
        switch (x.sens)
        {
        case NORD:
            x.sens = OUEST;
            break;
        case SUD:
            x.sens = EST;
            break;
        case EST:
            x.sens = NORD;
            break;
        case OUEST:
            x.sens = SUD;
            break;
        default:
            break;
        }
    }else{
        switch (x.sens)
        {
        case NORD:
            x.sens = EST;
            break;
        case SUD:
            x.sens = OUEST;
            break;
        case EST:
            x.sens = SUD;
            break;
        case OUEST:
            x.sens = NORD;
            break;
        default:
            break;
        }
    }
}

void OperateurRotation::changeSens(OperateurSymetrie &x, bool reverse)
{
    switch (x.sens)
    {
    case HORIZONTALE:
        x.sens = VERTICALE;
        break;
    default:
        x.sens = HORIZONTALE;
        break;
    }
}

// OperateurSymetrie
OperateurSymetrie::OperateurSymetrie(Piece &source, const pair<int, int> &position, OrientationSymetrie sens)
    : PieceOperateur(source, position), sens{sens} {}

void OperateurSymetrie::visit(OperateurDeplacement &x, Piece &origin, bool reverse)
{
    mapPosition(x, reverse);  
    changeSens(x, reverse);  
    x.source.accept(*this, origin, reverse);
}

void OperateurSymetrie::visit(OperateurRotation &x, Piece &origin, bool reverse)
{
    mapPosition(x, reverse);
    changeSens(x, reverse);    
    x.source.accept(*this, origin, reverse);
}

void OperateurSymetrie::visit(OperateurSymetrie &x, Piece &origin, bool reverse)
{
    mapPosition(x, reverse);    
    x.source.accept(*this, origin, reverse);
}

void OperateurSymetrie::visit(PieceConcrete &p, Piece &origin, bool reverse)
{
    mapPosition(p, reverse);
    if(reverse) {
        p.maps->getActions().pop_back();
    } else {
        Actions *action = new Actions(*this, &origin, p);
        p.maps->getActions().push_back(action);
    }
}

void OperateurSymetrie::accept(PieceOperateur &v, Piece &origin, bool reverse)
{
    v.visit(*this, origin, reverse);
}

void OperateurSymetrie::mapPosition(OperateurDeplacement &op, bool reverse)
{
    mapPosition(op.position, reverse);
}
void OperateurSymetrie::mapPosition(OperateurRotation &op, bool reverse)
{
    mapPosition(op.position, reverse);
}
void OperateurSymetrie::mapPosition(OperateurSymetrie &op, bool reverse)
{
    mapPosition(op.position, reverse);
}
void OperateurSymetrie::mapPosition(PieceConcrete &op, bool reverse)
{   
    for (pair<int, int> &x : op.coordinates)
        mapPosition(x, reverse);
}
OrientationSymetrie OperateurSymetrie::getReverseSens(){
    switch (this->sens)
    {
    case HORIZONTALE:
        return VERTICALE;
    default:
        return HORIZONTALE;
    }
}
void OperateurSymetrie::mapPosition(pair<int, int> &p, bool reverse){
    int x = p.first;
    int y = p.second;
    int x_c = this->position.first;
    int y_c = this->position.second;
    OrientationSymetrie tmp = this->sens;
    // if(reverse) tmp = getReverseSens();
    switch (tmp)
    {
        case HORIZONTALE:
            y = 2 * y_c - y;
            break;
        case VERTICALE:
            x = 2 * x_c - x;
            break;
        default:
            break;
    }
    p = {x, y};   
}

void OperateurSymetrie::changeSens(OperateurDeplacement &x, bool reverse)
{
    switch(this->sens){
        case HORIZONTALE:
            switch(x.sens){
                case NORD:
                    x.sens = SUD;
                    break;
                case SUD:
                    x.sens = NORD;
                    break;
                default:
                    break;
            }
            break;
        case VERTICALE: 
            switch(x.sens){
                case EST:
                    x.sens = OUEST;
                    break;
                case OUEST:
                    x.sens = EST;
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
}

void OperateurSymetrie::changeSens(OperateurRotation &x, bool reverse)
{
    x.sens = (x.sens == HORAIRE) ? ANTI_HORAIRE : HORAIRE;
}