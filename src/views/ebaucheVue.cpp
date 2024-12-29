// #include "ebaucheVue.hpp"

// EbaucheVue::EbaucheVue()
// {
// 	init();
// }
// void EbaucheVue::init()
// {
// 	RenderWindow window;
// 	window.setFramerateLimit(30);
// 	initTexture();
// 	initCentralPane();
// 	// initSelectPlateau();
// 	initButton();
// 	initWindow(window);

// 	while (window.isOpen())
// 	{
// 		mouseController.updateMousePosition(window);
// 		// updateTitle(window);
// 		while (window.pollEvent(keyboardController.getEvent()))
// 		{
// 			keyboardController.updateKeyboardEvent(window);
// 			addSprite();
// 		}
// 		draw(window);
// 	}
// }

// void EbaucheVue::initWindow(RenderWindow &window)
// {
// 	window.create(VideoMode(nbPix_x, nbPix_y), "Ebauche Vue", Style::Titlebar | Style::Close);
// }

// void EbaucheVue::initTexture()
// {
// 	if (!homeTexture.loadFromFile("resources/home.png"))
// 	{
// 		cout << "Error loading home.png" << endl;
// 	}
// }

// void EbaucheVue::initButton()
// {
// 	homeButton.setTexture(homeTexture);
// 	homeButton.setScale(0.2, 0.2);
// 	homeButton.setPosition(10, 10);
// }

// void EbaucheVue::initCentralPane()
// {
// 	// définition d'un panneau "central"
// 	centralPane.setSize(Vector2f(NB_COL * TILE_SIZE, NB_LIGNE * TILE_SIZE));
// 	centralPane.setPosition(MARGIN_LEFT, MARGIN_TOP);
// 	centralPane.setFillColor(Color::White);
// 	scene_generale.push_back(&centralPane);
// }

// void EbaucheVue::addSprite()
// {

// 	if (keyboardController.event.type == Event::MouseButtonPressed && keyboardController.event.mouseButton.button == Mouse::Left)
// 	{
// 		Vector2f mousePos = mouseController.getMouseWorldPos();

// 		// Vérifier si le bouton home est cliqué
// 		if (homeButton.getGlobalBounds().contains(mousePos))
// 		{
// 			scene_particuliere.clear();
// 			pieces.clear();
// 			initSelectPlateau();
// 			return;
// 		}

// 		if (!scene_generale.empty())
// 			for (Drawable *drawable : scene_generale)
// 			{
// 				RectangleShape *square = dynamic_cast<RectangleShape *>(drawable);
// 				if (square && square->getGlobalBounds().contains(mousePos))
// 				{
// 					cout << "Square clicked at position: " << square->getPosition().x << ", " << square->getPosition().y << endl;
// 					square->setFillColor(Color::Red); // Exemple de changement d'affichage

// 					// Cacher scene_generale et afficher scene_particuliere
// 					scene_generale.clear();
// 					return;
// 				}
// 			}
// 		else if (!scene_particuliere.empty())
// 			for (RectangleShape *piece : pieces)
// 			{
// 				if (piece->getGlobalBounds().contains(mousePos))
// 				{
// 					cout << "Piece clicked at position: " << piece->getPosition().x << ", " << piece->getPosition().y << endl;
// 					selectedPiece = piece;
// 					offset = mousePos - piece->getPosition();
// 					isDragging = true;
// 					return;
// 				}
// 			}
// 	}

// 	else if (keyboardController.event.type == Event::MouseButtonReleased && keyboardController.event.mouseButton.button == Mouse::Left)
// 	{
// 		isDragging = false;
// 		selectedPiece = nullptr;
// 	}

// 	else if (keyboardController.event.type == Event::MouseMoved && isDragging && selectedPiece)
// 	{
// 		Vector2f mousePos = mouseController.getMouseWorldPos();
// 		selectedPiece->setPosition(mousePos - offset);
// 	}
// }

// void EbaucheVue::draw(RenderWindow &window)
// {
// 	window.clear(sf::Color::White);
// 	window.setView(window.getDefaultView());

// 	if (!scene_generale.empty())
// 	{
// 		for (Drawable *x : scene_generale)
// 			window.draw(*x);
// 	}
// 	else
// 	{
// 		for (Drawable *x : scene_particuliere)
// 			window.draw(*x);

// 		// Dessiner les pièces par-dessus la carte
// 		for (RectangleShape *piece : pieces)
// 			window.draw(*piece);
// 	}
// 	// Dessiner le bouton
// 	window.draw(homeButton);
// 	window.draw(buttonText);

// 	window.display();
// }

// void EbaucheVue::initSelectPlateau()
// {
// 	float startX = (nbPix_x - 3 * TILE_SIZE) / 2;
// 	float startY = (nbPix_y - 3 * TILE_SIZE) / 2;
// 	int index = 0;
// 	Color colors[4] = {Color::Red, Color::Green, Color::Blue, Color::Yellow};

// 	for (int i = 0; i < 3; ++i)
// 	{
// 		for (int j = 0; j < 3; ++j)
// 		{
// 			RectangleShape *square = new RectangleShape(Vector2f(TILE_SIZE, TILE_SIZE));
// 			square->setPosition(startX + j * TILE_SIZE, startY + i * TILE_SIZE);
// 			square->setFillColor(colors[index++ % 4]);
// 			scene_generale.push_back(square);
// 		}
// 	}
// }
