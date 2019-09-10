#include"MainMenu.h"

//Constructeur
MainMenu::MainMenu()
{
	_window.create(VideoMode(1920, 1080), "TowerDefense", Style::Titlebar | Style::Close);
	_window.setFramerateLimit(120);

	_posPlayX = 690;
	_posPlayY = 240;

	_posQuitX = 690;
	_posQuitY = 480;

	_posOiseauX = 2150;
	_posOiseauY = 70;
	_vitesseX = 2;

	_posOiseauX2 = 2300;
	_posOiseauY2 = 25;

	//Chargement des images
	_textPlay.loadFromFile("play.png");
	_textQuit.loadFromFile("quit.png");
	_textOiseau.loadFromFile("oiseau.png");
	_textBackground.loadFromFile("background.png");

	//Bouton quit
	_recQuit.left = 0;
	_recQuit.top = 0;
	_recQuit.height = 173;
	_recQuit.width = 562;

	//Bouton Play
	_recPlay.left = 0;
	_recPlay.top = 0;
	_recPlay.height = 173;
	_recPlay.width = 562;

	//L'oiseau
	_recOiseau.left = 0;
	_recOiseau.top = 0;
	_recOiseau.height = 100;
	_recOiseau.width = 80;

	//Bouton quit
	_buttonQuit.setTexture(_textQuit);
	_buttonQuit.setTextureRect(_recQuit);
	_buttonQuit.setPosition(_posQuitX, _posQuitY);

	//Bouton Play
	_buttonPlay.setTexture(_textPlay);
	_buttonPlay.setTextureRect(_recPlay);
	_buttonPlay.setPosition(_posPlayX, _posPlayY);

	//L'oiseau
	_oiseau.setTexture(_textOiseau);
	_oiseau.setTextureRect(_recOiseau);
	_oiseau.setPosition(_posOiseauX, _posOiseauY);

	_oiseau2.setTexture(_textOiseau);
	_oiseau2.setTextureRect(_recOiseau);
	_oiseau.setPosition(_posOiseauX2, _posOiseauY2);

	_background.setTexture(_textBackground);

	_music.openFromFile("Wind.ogg");
	_buffer.loadFromFile("Crow.ogg");
	_sonCrow.setBuffer(_buffer);

	_quit = false;
}

//Fait fonctionner le menu principal
void MainMenu::run()
{
	Event event;
	RectangleShape background(Vector2f(1920, 1080));	//Arriere-plan du jeu
	background.setFillColor(Color::Cyan);				//Fond vert

	_music.play();
	_music.setLoop(true);

	while (_window.isOpen())
	{
		Vector2i mousePos = Mouse::getPosition(_window);
		// Input
		while (_window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
				_window.close();
				_quit = true;
				break;
			}

			//Event click gauche
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				if (mousePos.x >= _buttonPlay.getPosition().x && mousePos.x <= _buttonPlay.getPosition().x + 562 && mousePos.y >= _buttonPlay.getPosition().y && mousePos.y <= _buttonPlay.getPosition().y + 173) //Si sur bouton play
				{
					_window.close();
				}
				else if (mousePos.x >= _buttonQuit.getPosition().x && mousePos.x <= _buttonQuit.getPosition().x + 562 && mousePos.y >= _buttonQuit.getPosition().y && mousePos.y <= _buttonQuit.getPosition().y + 173) //Si sur boutton quit
				{
					_window.close();
					_quit = true;
				}
			}
		}

		animationOiseau();		//Change l'animation de l'oiseau
		deplacementOiseau();	//Deplace l'oiseau

								// Affichage
		_window.clear();
		_window.draw(background);
		_window.draw(_background);
		_window.draw(_buttonPlay);
		_window.draw(_buttonQuit);
		_window.draw(_oiseau);
		_window.draw(_oiseau2);

		_window.display();
	}
	_music.stop();
	_sonCrow.stop();
}

//Animation de l'oiseau
void MainMenu::animationOiseau()
{
	if (_tempsSpriteOiseau.getElapsedTime().asMilliseconds() > 30)
	{
		//Passe au travers du sprite sheet
		if (_recOiseau.left == 320)
		{
			_recOiseau.left = 0;

			if (_recOiseau.top == 300)
				_recOiseau.top = 0;
			else
				_recOiseau.top += 100;
		}
		else
			_recOiseau.left += 80;

		_oiseau.setTextureRect(_recOiseau);
		_oiseau2.setTextureRect(_recOiseau);
		_tempsSpriteOiseau.restart();
	}
	if (_tempsSonOiseau.getElapsedTime().asSeconds() > 5)
	{
		_sonCrow.play();
		_tempsSonOiseau.restart();
	}
}

//Deplacement de l'oiseau
void MainMenu::deplacementOiseau()
{
	if (_tempsDepOiseau.getElapsedTime().asMilliseconds() > 10)
	{
		if (_posOiseauX == -150)
			_posOiseauX = 2020;

		if (_posOiseauX2 == -150)
			_posOiseauX2 = 2020 + 150;

		_oiseau.setPosition(_posOiseauX -= _vitesseX, _posOiseauY);
		_oiseau2.setPosition(_posOiseauX2  -= _vitesseX, _posOiseauY2 );
		_tempsDepOiseau.restart();
	}
}

//Si l'utilisateur quitte le jeu
bool MainMenu::getQuit()
{
	return _quit;
}