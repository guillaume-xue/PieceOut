#include "../../src/models/Piece.hpp"
#include "../../src/models/PieceOperateur.hpp"

// int main()
// {
// 	vector<pair<int, int>> coords{{0, 0}, {0, 1}, {0, 2}, {1, 2}};
// 	PieceConcrete tetris_L(coords);
// 	Piece *p = new OperateurDeplacement{tetris_L, {0, 0}, EST};
// 	p = new OperateurDeplacement{*p, {0, 0}, SUD};
// 	for (auto x : p->getCoordinates())
// 		cout << x.first << " " << x.second << endl;
// 	cout << "---------------" << endl;
// 	p->trigger(make_pair(0, 0));
// 	for (auto x : p->getCoordinates())
// 		cout << x.first << " " << x.second << endl;
// 	cout << "---------------" << endl;
// 	p->trigger(make_pair(0, 1));
// 	for (auto x : p->getCoordinates())
// 		cout << x.first << " " << x.second << endl;
// 	return 0;
// }