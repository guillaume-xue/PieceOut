#include "ebaucheVue.hpp"

EbaucheVue::EbaucheVue()
{
	init();
}
void EbaucheVue::init()
{
	map = new Maps();
	RenderWindow window;
	window.setFramerateLimit(30);
	initTexture();
	initCentralPane();
	// initSelectPlateau();
	initButton();
	initWindow(window);

	while (window.isOpen())
	{
		mouseController.updateMousePosition(window);
		// updateTitle(window);
		while (window.pollEvent(keyboardController.event))
		{
			keyboardController.updateKeyboardEvent(window);
			addSprite();
		}
		draw(window);
	}
}

void EbaucheVue::initWindow(RenderWindow &window)
{
	window.create(VideoMode(nbPix_x, nbPix_y), "Ebauche Vue", Style::Titlebar | Style::Close);
}

void EbaucheVue::initTexture()
{
	if (!homeTexture.loadFromFile("resources/home.png"))
	{
		cout << "Error loading home.png" << endl;
	}
}

void EbaucheVue::initButton()
{
	homeButton.setTexture(homeTexture);
	homeButton.setScale(0.2, 0.2);
	homeButton.setPosition(10, 10);
}

void EbaucheVue::initCentralPane()
{
	// définition d'un panneau "central"
	centralPane.setSize(Vector2f(NB_COL * TILE_SIZE, NB_LIGNE * TILE_SIZE));
	centralPane.setPosition(MARGIN_LEFT, MARGIN_TOP);
	centralPane.setFillColor(Color::White);
	scene_generale.push_back(&centralPane);
}

void EbaucheVue::addSprite()
{

	if (keyboardController.event.type == Event::MouseButtonPressed && keyboardController.event.mouseButton.button == Mouse::Left)
	{
		Vector2f mousePos = mouseController.getMouseWorldPos();

		// Vérifier si le bouton home est cliqué
		if (homeButton.getGlobalBounds().contains(mousePos))
		{
			scene_particuliere.clear();
			pieces.clear();
			initSelectPlateau();
			return;
		}

		if (!scene_generale.empty())
			for (Drawable *drawable : scene_generale)
			{
				RectangleShape *square = dynamic_cast<RectangleShape *>(drawable);
				if (square && square->getGlobalBounds().contains(mousePos))
				{
					cout << "Square clicked at position: " << square->getPosition().x << ", " << square->getPosition().y << endl;
					square->setFillColor(Color::Red); // Exemple de changement d'affichage

					// Cacher scene_generale et afficher scene_particuliere
					scene_generale.clear();
					initNewTerrain();
					return;
				}
			}
		else if (!scene_particuliere.empty())
			for (RectangleShape *piece : pieces)
			{
				if (piece->getGlobalBounds().contains(mousePos))
				{
					cout << "Piece clicked at position: " << piece->getPosition().x << ", " << piece->getPosition().y << endl;
					selectedPiece = piece;
					offset = mousePos - piece->getPosition();
					isDragging = true;
					return;
				}
			}
	}

	else if (keyboardController.event.type == Event::MouseButtonReleased && keyboardController.event.mouseButton.button == Mouse::Left)
	{
		isDragging = false;
		selectedPiece = nullptr;
	}

	else if (keyboardController.event.type == Event::MouseMoved && isDragging && selectedPiece)
	{
		Vector2f mousePos = mouseController.getMouseWorldPos();
		selectedPiece->setPosition(mousePos - offset);
	}
}

void EbaucheVue::draw(RenderWindow &window)
{
	window.clear(sf::Color::White);
	window.setView(window.getDefaultView());

	if (!scene_generale.empty())
	{
		for (Drawable *x : scene_generale)
			window.draw(*x);
	}
	else
	{
		for (Drawable *x : scene_particuliere)
			window.draw(*x);

		// Dessiner les pièces par-dessus la carte
		for (RectangleShape *piece : pieces)
			window.draw(*piece);
	}
	// Dessiner le bouton
	window.draw(homeButton);
	window.draw(buttonText);

	window.display();
}

void EbaucheVue::initSelectPlateau()
{
	float startX = (nbPix_x - 3 * TILE_SIZE) / 2;
	float startY = (nbPix_y - 3 * TILE_SIZE) / 2;
	int index = 0;
	Color colors[4] = {Color::Red, Color::Green, Color::Blue, Color::Yellow};

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			RectangleShape *square = new RectangleShape(Vector2f(TILE_SIZE, TILE_SIZE));
			square->setPosition(startX + j * TILE_SIZE, startY + i * TILE_SIZE);
			square->setFillColor(colors[index++ % 4]);
			scene_generale.push_back(square);
		}
	}
}

void EbaucheVue::initNewTerrain()
{
	// Initialiser la carte
	map->map1();

	// Calculer les positions de départ pour centrer la carte
	float startX = (nbPix_x - map->nbCol * map->TILE_SIZE) / 2;
	float startY = (nbPix_y - map->nbLigne * map->TILE_SIZE) / 2;

	// Créer les cases de la carte
	for (int i = 0; i < map->nbLigne; ++i)
	{
		for (int j = 0; j < map->nbCol; ++j)
		{
			RectangleShape *square = new RectangleShape(Vector2f(map->TILE_SIZE, map->TILE_SIZE));
			square->setPosition(startX + j * map->TILE_SIZE, startY + i * map->TILE_SIZE);
			square->setFillColor(Color::White);		 // Couleur de remplissage des cases
			square->setOutlineColor(Color::Black); // Couleur du bord
			square->setOutlineThickness(1);				 // Épaisseur du bord
			scene_particuliere.push_back(square);
		}
	}

	// Ajouter les pièces par-dessus la carte
	const vector<pair<int, int>> &coords = map->piece->getCoordinates();
	for (const auto &coord : coords)
	{
		int x = coord.first;
		int y = coord.second;
		RectangleShape *piece = new RectangleShape(Vector2f(map->TILE_SIZE, map->TILE_SIZE));
		piece->setPosition(startX + x * map->TILE_SIZE, startY + y * map->TILE_SIZE);
		piece->setFillColor(Color::Red); // Couleur de la pièce
		piece->setOutlineThickness(1);	 // Épaisseur du bord
		pieces.push_back(piece);
	}
}
