#include "PieceOperateur.hpp"

// PieceOperateur
PieceOperateur::PieceOperateur(Piece &source, const pair<int, int> &position)
    : source{source}, position{position} {}

void PieceOperateur::trigger(const pair<int, int> &relativePos, Piece &origin)
{
    // cout << "PieceOperateur::trigger" << endl;
    if (relativePos == position) {
        origin.accept(*this, origin);
    } else {
        source.trigger(relativePos, origin);
    }
}

void PieceOperateur::visit(PieceConcrete &p, Piece &origin)
{
    // cout << "PieceOperateur::visit" << endl;
    for (pair<int, int> &x : p.coordinates)
        mapPosition(x);
    // cout << "PieceOperateur::visit" << endl;
    Actions *action = new Actions(*this, &origin, p);
    p.maps->getActions().push_back(action);
    // cout << "PieceOperateur::visit: " << p.maps->getActions().size() << endl;
}

void PieceOperateur::reVisit(PieceConcrete &p, Piece &origin)
{
    // cout << "PieceOperateur::reVisit" << endl;
    for (pair<int, int> &x : p.coordinates)
        mapPositionReverse(x);
    p.maps->getActions().pop_back();
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

void PieceOperateur::visit(PieceOperateur *x, Piece &origin)
{
    mapPosition(x);
    x->source.accept(*this, origin);
}

void PieceOperateur::reVisit(PieceOperateur *x, Piece &origin)
{
    mapPositionReverse(x);
    x->source.reAccept(*this, origin);
}

void PieceOperateur::accept(PieceOperateur &v, Piece &origin)
{
    v.visit(this, origin);
}

void PieceOperateur::reAccept(PieceOperateur &v, Piece &origin)
{
    v.reVisit(this, origin);
}

// OperateurDeplacement
OperateurDeplacement::OperateurDeplacement(Piece &source, const pair<int, int> &position, OrientationDeplacement sens)
    : PieceOperateur(source, position), sens{sens} {}

// void OperateurDeplacement::accept(const PieceOperateur &v, Piece &origin)
// {
//     // cout << "OperateurDeplacement::accept" << endl;
//     v.visit(*this, origin);
// }

// void OperateurDeplacement::visit(OperateurDeplacement &x, Piece &origin) 
// {
//     // cout << "OperateurDeplacement::visit" << endl;
//     mapPosition(x.position);
//     x.source.accept(*this, origin);
// }
// void OperateurDeplacement::reAccept(const PieceOperateur &v, Piece &origin)
// {
//     // cout << "OperateurDeplacement::reAccept" << endl;
//     v.reVisit(*this, origin);
// }
// void OperateurDeplacement::reVisit(OperateurDeplacement &x, Piece &origin)
// {
//     // cout << "OperateurDeplacement::reVisit" << endl;
//     mapPositionReverse(x.position);
//     x.source.reAccept(*this, origin);
// }

void PieceOperateur::mapPosition(PieceOperateur *x)
{
    pair<int, int> &pos = x->position;
    if(OperateurDeplacement *op = dynamic_cast<OperateurDeplacement *>(this)){
        switch (op->sens)
        {
        case NORD:
            pos.second--;
            break;
        case SUD:
            pos.second++;
            break;
        case EST:
            pos.first++;
            break;
        case OUEST:
            pos.first--;
            break;
        default:
            break;
        }
    } else if (OperateurRotation *op = dynamic_cast<OperateurRotation *>(this)){
        int x2 = pos.first;
        int y = pos.second;
        int x_c = this->position.first;
        int y_c = this->position.second;
        x2 -= x_c;
        y -= y_c;
        int xtemp = x2;
        int ytemp = y;
        
        switch (op->sens)
        {
        case HORAIRE:
            x2 = -ytemp;
            y = xtemp;
            x2 += x_c;
            y += y_c;
            pos = {x2, y};
            changeSensRot(x, HORAIRE);
            break;
        case ANTI_HORAIRE:
            x2 = ytemp;
            y = -xtemp;
            x2 += x_c;
            y += y_c;
            pos = {x2, y};
            changeSensRot(x, ANTI_HORAIRE);
            break;
        default:
            break;
        }
    }

}

void PieceOperateur::mapPositionReverse(PieceOperateur *x)
{
    pair<int, int> &pos = x->position;
    if(OperateurDeplacement *op = dynamic_cast<OperateurDeplacement *>(this)){
        switch (op->sens)
        {
        case NORD:
            pos.second++;
            break;
        case SUD:
            pos.second--;
            break;
        case EST:
            pos.first--;
            break;
        case OUEST:
            pos.first++;
            break;
        default:
            break;
        }
    } else if (OperateurRotation *op = dynamic_cast<OperateurRotation *>(this)){
        int x2 = pos.first;
        int y = pos.second;
        int x_c = this->position.first;
        int y_c = this->position.second;

        x2 -= x_c;
        y -= y_c;

        int xtemp = x2;
        int ytemp = y;

        switch (op->sens)
        {
        case ANTI_HORAIRE:
            x2 = -ytemp;
            y = xtemp;
            x2 += x_c;
            y += y_c;
            pos = {x2, y};
            changeSensRot(x, HORAIRE);
            break;
        case HORAIRE:
            x2 = ytemp;
            y = -xtemp;
            x2 += x_c;
            y += y_c;
            pos = {x2, y};
            changeSensRot(x, ANTI_HORAIRE);
            break;
        default:
            break;
        }
    }
}

// OperateurRotation

OperateurRotation::OperateurRotation(Piece &source, const pair<int, int> &position, OrientationRotation sens)
    : PieceOperateur(source, position), sens{sens} {}

// void OperateurRotation::accept(const PieceOperateur &v, Piece &origin){
//     v.visit(*this, origin);
// }

// void OperateurRotation::visit(OperateurRotation &x, Piece &origin) const
// {
//     mapPosition(x.position);
//     x.source.accept(*this, origin);
// }

// void OperateurRotation::reAccept(const PieceOperateur &v, Piece &origin)
// {
//     v.reVisit(*this, origin);
// }

// void OperateurRotation::reVisit(OperateurRotation &x, Piece &origin) const
// {
//     mapPositionReverse(x.position);
//     x.source.reAccept(*this, origin);
// }

// void OperateurRotation::mapPosition(pair<int, int> &pos) const
// {
//     int x = pos.first;
//     int y = pos.second;
//     int x_c = this->position.first;
//     int y_c = this->position.second;

//     switch (sens)
//     {
//     case HORAIRE:
//         pos = {y - y_c + x_c, x_c - x + y_c};
//         break;
//     case ANTI_HORAIRE:
//         pos = {y_c - y + x_c, x - x_c + y_c};
//         break;
//     default:
//         break;
//     }
// }

// void OperateurRotation::mapPositionReverse(pair<int, int> &pos) const
// {
//     int x = pos.first;
//     int y = pos.second;
//     int x_c = this->position.first;
//     int y_c = this->position.second;

//     switch (sens)
//     {
//     case HORAIRE:
//         pos = {y_c - y + x_c, x - x_c + y_c};
//         break;
//     case ANTI_HORAIRE:
//         pos = {y - y_c + x_c, x_c - x + y_c};
//         break;
//     default:
//         break;
//     }
// }

// OperateurSymetrie

OperateurSymetrie::OperateurSymetrie(Piece &source, const pair<int, int> &position, OrientationSymetrie sens)
    : PieceOperateur(source, position), sens{sens} {}



void PieceOperateur::mapPosition(pair<int, int> &pos)
{
    if(OperateurDeplacement *op = dynamic_cast<OperateurDeplacement *>(this)){
        switch (op->sens)
        {
        case NORD:
            pos.second--;
            break;
        case SUD:
            pos.second++;
            break;
        case EST:
            pos.first++;
            break;
        case OUEST:
            pos.first--;
            break;
        default:
            break;
        }
    } else if (OperateurRotation *op = dynamic_cast<OperateurRotation *>(this)){
        int x = pos.first;
        int y = pos.second;
        int x_c = this->position.first;
        int y_c = this->position.second;
        x -= x_c;
        y -= y_c;

        int xtemp = x;
        int ytemp = y;

        switch (op->sens)
        {
        case HORAIRE:
            x = -ytemp;
            y = xtemp;
            x += x_c;
            y += y_c;
            pos = {x, y};
            break;
        case ANTI_HORAIRE:
            x = ytemp;
            y = -xtemp;
            x += x_c;
            y += y_c;
            pos = {x, y};
            break;
        default:
            break;
        }
    }

}

void PieceOperateur::mapPositionReverse(pair<int, int> &pos)
{
    if(OperateurDeplacement *op = dynamic_cast<OperateurDeplacement *>(this)){
        switch (op->sens)
        {
        case NORD:
            pos.second++;
            break;
        case SUD:
            pos.second--;
            break;
        case EST:
            pos.first--;
            break;
        case OUEST:
            pos.first++;
            break;
        default:
            break;
        }
    } else if (OperateurRotation *op = dynamic_cast<OperateurRotation *>(this)){
        int x = pos.first;
        int y = pos.second;
        int x_c = this->position.first;
        int y_c = this->position.second;
        x -= x_c;
        y -= y_c;

        int xtemp = x;
        int ytemp = y;

        switch (op->sens)
        {
        case ANTI_HORAIRE:
            x = -ytemp;
            y = xtemp;
            x += x_c;
            y += y_c;
            pos = {x, y};
            break;
        case HORAIRE:
            x = ytemp;
            y = -xtemp;
            x += x_c;
            y += y_c;
            pos = {x, y};
            break;
        default:
            break;
        }
    }
}

void PieceOperateur::changeSensRot(PieceOperateur *x, OrientationRotation sens)
{
    if(OperateurDeplacement *op = dynamic_cast<OperateurDeplacement *>(x)){
        switch(sens)
        {
        case HORAIRE:
            switch (op->sens)
            {
            case NORD:
                op->sens = EST;
                break;
            case EST:
                op->sens = SUD;
                break;
            case SUD:
                op->sens = OUEST;
                break;
            case OUEST:
                op->sens = NORD;
                break;
            default:
                break;
            }
            break;
        case ANTI_HORAIRE:
            switch (op->sens)
            {
            case NORD:
                op->sens = OUEST;
                break;
            case OUEST:
                op->sens = SUD;
                break;
            case SUD:
                op->sens = EST;
                break;
            case EST:
                op->sens = NORD;
                break;
            default:
                break;
            }
            break;
        }
    }else if(OperateurSymetrie *op = dynamic_cast<OperateurSymetrie *>(x)){
        switch(op->sens)
        {
        case HORIZONTALE:
            op->sens = VERTICALE;
            break;
        case VERTICALE:
            op->sens = HORIZONTALE;
            break;
        default:
            break;
        }
    }
}