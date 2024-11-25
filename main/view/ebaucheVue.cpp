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
		handleMouseEvent(window);
		updateTitle(window);
		while (window.pollEvent(event))
		{
			handleKeyboardEvent(window);
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
	if (!texture_rouge.loadFromFile("texture.jpg"))
	{
		cerr << "Erreur lors du chargement de l'image" << endl;
	}
}

void EbaucheVue::addSprite()
{
	if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left && centralPane.getGlobalBounds().contains(mouseWorldPos)) // clic gauche
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
	string message = "Mouse Position: (" + to_string(int(mouseWorldPos.x)) + ", " +
									 to_string(int(mouseWorldPos.y)) + ")";

	if (centralPane.getGlobalBounds().contains(mouseWorldPos)) // si la souris est dans le cadre
	{
		Vector2f topLeft = centralPane.getPosition();
		trig_x = (mouseWorldPos.x - topLeft.x) / TILE_SIZE;
		trig_y = (mouseWorldPos.y - topLeft.y) / TILE_SIZE;
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

void EbaucheVue::handleKeyboardEvent(RenderWindow &window)
{
	if (event.type == Event::Closed ||
			(event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)) // fermeture de la fenêtre
		window.close();
}

void EbaucheVue::handleMouseEvent(RenderWindow &window)
{
	mousePos = Mouse::getPosition(window);
	mouseWorldPos = window.mapPixelToCoords(mousePos);
}

int main()
{
	EbaucheVue ebaucheVue = EbaucheVue();
	return EXIT_SUCCESS;
}
