#include "ebaucheVue.hpp"

EbaucheVue::EbaucheVue()
{
	init();
}

void EbaucheVue::init()
{
	RenderWindow window;
	initCentralPane();
	initTrame();
	initTexture();
	initWindow(window);

	while (window.isOpen())
	{
		mouseController.updateMousePosition(window);
		updateTitle(window);
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
	window.create(VideoMode(nbPix_x, nbPix_y), "Ebauche Vue");
}

void EbaucheVue::initTrame()
{
	// plus une trame (lignes horizontales+verticales). En SFML on peut passer par VertexArray
	// Lines est une sf::enum, VertexArray encapsule autant de points que nécessaires pour ces lignes
	trame = VertexArray(Lines, 2 * (NB_COL + NB_LIGNE + 2));
	// pour les lignes horizontales
	int n = 0;
	for (int i = 0; i <= NB_LIGNE; ++i)
	{
		trame[n++].position = Vector2f(MARGIN_LEFT, MARGIN_TOP + i * TILE_SIZE);
		trame[n].color = Color::Blue;
		trame[n++].position = Vector2f(nbPix_x - MARGIN_RIGHT, MARGIN_TOP + i * TILE_SIZE);
	}
	// pour les verticales
	for (int i = 0; i <= NB_COL; ++i)
	{
		trame[n++].position = Vector2f(MARGIN_LEFT + i * TILE_SIZE, MARGIN_TOP);
		trame[n].color = Color::Blue;
		trame[n++].position = Vector2f(MARGIN_LEFT + i * TILE_SIZE, nbPix_y - MARGIN_BOTTOM);
	}
	// on peut (ou pas) distinguer la scène générale cadre+frame et la scène particulière (les cases actuelles)
	scene_generale.push_back(&trame);
}

void EbaucheVue::initCentralPane()
{
	// définition d'un panneau "central"
	centralPane.setSize(Vector2f(NB_COL * TILE_SIZE, NB_LIGNE * TILE_SIZE));
	centralPane.setPosition(MARGIN_LEFT, MARGIN_TOP);
	centralPane.setFillColor(Color::Black);
	scene_generale.push_back(&centralPane);
}

void EbaucheVue::initTexture()
{
	if (!texture_rouge.loadFromFile("resources/texture.jpg"))
	{
		cerr << "Erreur lors du chargement de l'image" << endl;
	}
}

void EbaucheVue::addSprite()
{
	if (keyboardController.event.type == Event::MouseButtonPressed && keyboardController.event.mouseButton.button == Mouse::Left && centralPane.getGlobalBounds().contains(mouseController.getMouseWorldPos())) // clic gauche
	{
		cout << "trigger " << trig_x << " " << trig_y << endl;
		// création d'un sprite pour afficher une case d'exemple
		Sprite *sprite = new Sprite;
		sprite->setTexture(texture_rouge);
		Vector2u textureSize = texture_rouge.getSize();
		sprite->setScale(static_cast<float>(TILE_SIZE) / textureSize.x,
										 static_cast<float>(TILE_SIZE) / textureSize.y);
		sprite->setPosition(centralPane.getPosition() + Vector2f(trig_x * TILE_SIZE, trig_y * TILE_SIZE));
		scene_particuliere.push_back(sprite);
	}
}

void EbaucheVue::updateTitle(RenderWindow &window)
{
	string message = "Mouse Position: (" + to_string(int(mouseController.getMouseWorldPos().x)) + ", " +
									 to_string(int(mouseController.getMouseWorldPos().y)) + ")";

	if (centralPane.getGlobalBounds().contains(mouseController.getMouseWorldPos())) // si la souris est dans le cadre
	{
		Vector2f topLeft = centralPane.getPosition();
		trig_x = (mouseController.getMouseWorldPos().x - topLeft.x) / TILE_SIZE;
		trig_y = (mouseController.getMouseWorldPos().y - topLeft.y) / TILE_SIZE;
		message += " case :" + to_string(trig_x) + " ; " + to_string(trig_y);
	}
	window.setTitle(message);
}

void EbaucheVue::draw(RenderWindow &window)
{
	window.clear();
	window.setView(window.getDefaultView());

	// les affichages
	for (Drawable *x : scene_generale)
		window.draw(*x);
	for (Drawable *x : scene_particuliere)
		window.draw(*x);

	window.display();
}
