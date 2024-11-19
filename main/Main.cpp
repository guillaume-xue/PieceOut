#include "Piece.hpp"
#include "PieceOperateur.hpp"

int main() {
	vector<pair<int, int>> coords { {0, 0}, {0, 1}, {0, 2}, {1, 2}};     
	PieceConcrete tetris_L(coords);
	Piece *p = new OperateurDeplacement {tetris_L,{0,0},EST};
	p->trigger(make_pair(0,0));
	p->trigger(make_pair(1,0));
}