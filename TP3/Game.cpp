#include "Game.h"

//Constructeur
Game::Game()
{
	_window.create(VideoMode(1920, 1080), "TowerDefense");
	_window.setFramerateLimit(120);
	readFile(_carte, "Map1.txt");

	_textTile.loadFromFile("tileset-tutorial.png");

	_itSkeleton = _listSkeleton.begin();

	//Met 5 squelettes dans la file
	for (int i = 0; i < 100; i++)
		_fileSkeleton.push(_skeleton);

	initialiserRectPosition(); //Position rectangle sur la map et sprite

	_itTourSpawn = _tour.begin();
	_itLaser = _listLaser.begin();
	_itPeonSpawn = _peon.begin();

	_music.openFromFile("Stage Boss.ogg");
	_buffer.loadFromFile("Laser.ogg");
	_sonLaser.setBuffer(_buffer);
	_sonLaser.setVolume(10);

	_bufferWork.loadFromFile("work.ogg");
	_work.setBuffer(_bufferWork);

	_typeTour = 0;

	_nbVie = 10;
	_victoire = _defaite = false;

	_timerSpawnSkelette = 4;
}

void Game::run()
{
	Event event;
	RectangleShape background(Vector2f(1920, 1080)); //Arriere-plan du jeu
	background.setFillColor(Color::Green);	//Fond vert

	_music.setVolume(14);
	_music.play();
	_music.setLoop(true);

	while (_window.isOpen())
	{
		// Input
		while (_window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
				_window.close();
				break;
			case Event::MouseButtonPressed: // Click sur un bouton de la souris
				_positionClick = Mouse::getPosition(_window);
				positionValide();
				break;
			case Event::KeyPressed:
				if (event.key.code == Keyboard::Num1)
					_typeTour = 0;
				else if (event.key.code == Keyboard::Num2)
					_typeTour = 1;
				break;
			}
		}

		attaqueSquelette();	//Si les tours ont un squelette a attaquer
		
		spawnSquelette();	//gere l'apparition des squelettes
		
		deplacementLaser(); //Deplacement des lasers
		deplacementPeons(); //Deplacement des peons
		
		laserColision();	//Collision entre les lasers et squelettes
	
		// Affichage
		_window.clear();
		_window.draw(background);
		print();

		if (_defaite == true)
		{ 
			cout << "Vous avez perdu" << endl;
			system("pause");
			_window.close();
		}

		_window.display();
	}
	_music.stop();
}

//Initialiser position des rectangles sur la map
void Game::initialiserRectPosition()
{
	int x = 0; //Position colonne sprite tuile

	 //Rectangle dans la map
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			_recTile[i][j].height = 120;
			_recTile[i][j].width = 120;
			_recTile[i][j].left = j * 120;
			_recTile[i][j].top = i * 120;
		}
	}

	//Rectangle du sprite sheet
	for (int i = 0; i < 1; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			_recSprite[i][j].height = 120;
			_recSprite[i][j].width = 120;
			_recSprite[i][j].left = x;
			_recSprite[i][j].top = 0;

			x += 120;
		}
	}
}

//Genere la map du jeu
void Game::genererMap()
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			if (_carte[i][j] == 0 || _carte[i][j] == 4)
				_tile.setTextureRect(_recSprite[0][0]);
			else if (_carte[i][j] == 1)
				_tile.setTextureRect(_recSprite[0][1]);
			else if (_carte[i][j] == 2)
				_tile.setTextureRect(_recSprite[0][2]);
			else if (_carte[i][j] == 3)
				_tile.setTextureRect(_recSprite[0][6]);

			_tile.setTexture(_textTile);
			_tile.setPosition(_recTile[i][j].left, _recTile[i][j].top);
			_window.draw(_tile);
		}
	}
}

//Faire apparaitre les squelettes sur le jeu
void Game::spawnSquelette()
{
	//Sur quelle chemin le squelette va apparaitre
	if (_fileSkeleton.size() % 2 == 1)
		_fileSkeleton.front().setPosition(_fileSkeleton.front().getPosX(), _recTile[2][0].top + 10);

	//Spawn squelettes au 5 secondes
	if (_tempsApparition.getElapsedTime().asMilliseconds() > _timerSpawnSkelette*1000 && !_fileSkeleton.empty())
	{
		if (_fileSkeleton.size() % 4 == 0 && _timerSpawnSkelette > 0.5)
			_timerSpawnSkelette -= 0.30;

		_listSkeleton.insert(_itSkeleton, _fileSkeleton.front());
		_fileSkeleton.pop();
		_tempsApparition.restart();
	}

	//Change deplacement et animation squelette
	for (_it = _listSkeleton.begin(); _it != _listSkeleton.end(); _it++)
	{
		(*_it).changeAnimation(_recTile);
		(*_it).deplacement(_recTile);

		// Si dépassé l'écran
		if ((*_it).getPosX() >= 1920)
		{
			_nbVie--;
			if (_nbVie == 0)
				_defaite = true;

			_listSkeleton.erase(_it);
			_it = _listSkeleton.begin();
			break;
		}
	}

}

//Afficher les objets du jeu
void Game::print()
{
	//Affiche la map
	genererMap();

	//Affiche tous les squelettes
	for (_it = _listSkeleton.begin(); _it != _listSkeleton.end(); _it++)
	{
		(*_it).afficheNpc(_window);
	}

	//Affiche toutes les tours
	for (_itTourAffiche = _tour.begin(); _itTourAffiche != _tour.end(); _itTourAffiche++)
	{
		(*_itTourAffiche).initTexture();
		(*_itTourAffiche).afficheTour(_window);
	}

	//Affiche les lasers actifs
	for (_itLaser = _listLaser.begin(); _itLaser != _listLaser.end(); _itLaser++)
		(*_itLaser).afficheLaser(_window);

	//Affiche les peons
	for (_itPeonAffiche = _peon.begin(); _itPeonAffiche != _peon.end(); _itPeonAffiche++)
	{
		if ((*_itPeonAffiche).constrTermine() == false)
			(*_itPeonAffiche).affichePeon(_window);
		else
		{
				_peon.erase(_itPeonAffiche);
				_itPeonSpawn = _peon.begin();
				break;
		}
			
	}
}

//Place une tour
void Game::placerTour(int posX, int posY)
{
	_tour.insert(_itTourSpawn, tour(_typeTour, posX, posY));
	_itTourSpawn--;
	_peon.insert(_itPeonSpawn, peon(posX, posY + 80, (*_itTourSpawn).getTempsConstr()));
	_itPeonSpawn--;
	(*_itPeonSpawn).init();

	_work.play();


	_carte[posY / 120][posX / 120] = 4; // pour empêcher de remettre une tour
}

//Verifie si la position est valide
bool Game::positionValide()
{
	int posX, posY;
	posX = _positionClick.x - (_positionClick.x % 120);
	posY = _positionClick.y - (_positionClick.y % 120);

	if (_carte[posY / 120][posX / 120] == 0)
	{
		placerTour(posX, posY);
		return true;
	}

	return false;
}

//Si les tours ont un squelette a attaquer
void Game::attaqueSquelette()
{
	//Verifie si les tours ont un squelettes a attaquer
	for (_itTourAffiche = _tour.begin(); _itTourAffiche != _tour.end(); _itTourAffiche++)
	{
		for (_it = _listSkeleton.begin(); _it != _listSkeleton.end(); _it++)
		{
			if ((*_itTourAffiche).tire(*_it))//Si la tour tire
			{
				(*_itTourAffiche).setTir(true);
				_itLaser = _listLaser.insert(_itLaser, _laser);
				(*_itLaser).setPos((*_itTourAffiche).getPosX(), (*_itTourAffiche).getPosY());
				(*_itLaser).setAngle((*_it).getPosX(), (*_it).getPosY(), (*_itTourAffiche).getPosX(), (*_itTourAffiche).getPosY());

				if ((*_itLaser).getPosDepartX() == 0 && (*_itLaser).getPosDepartY() == 0)
				{
					(*_itLaser).setPosDepart((*_itTourAffiche).getPosX(), (*_itTourAffiche).getPosY());
				}

				_sonLaser.play();
			}
			if ((*_it).getVie() <= 0) // Si plus de vie 
			{
				_it = _listSkeleton.erase(_it);
				break;
			}
		}
	}

}

//Deplacement des lasers
void Game::deplacementLaser()
{
	//Gere le deplacement des lasers
	for (_itLaserAffiche = _listLaser.begin(); _itLaserAffiche != _listLaser.end(); _itLaserAffiche++)
	{
		(*_itLaserAffiche).deplacement();
	}
}

//Deplacement des peons
void Game::deplacementPeons()
{
	//Gere le mouvement des peons
	for (_itPeonAffiche = _peon.begin(); _itPeonAffiche != _peon.end(); _itPeonAffiche++)
	{
		(*_itPeonAffiche).mouvement();
	}
}

//Collision entre les lasers et squelettes
void Game::laserColision()
{
	//Effacer les lasers
	for (_it = _listSkeleton.begin(); _it != _listSkeleton.end(); _it++)
	{
		for (_itLaserAffiche = _listLaser.begin(); _itLaserAffiche != _listLaser.end(); _itLaserAffiche++)
		{
			if ((*_itLaserAffiche).getPosDepartY() < (*_it).getPosY()) //Selon position de la tour
			{
				if ((*_itLaserAffiche).getPosY() >= (*_it).getPosY() + 68) //Si laser collision
				{
					_itLaserAffiche = _listLaser.erase(_itLaserAffiche);
					break;
				}
			}
			else if ((*_itLaserAffiche).getPosDepartY() > (*_it).getPosY())//Selon position de la tour
			{
				if ((*_itLaserAffiche).getPosY() <= (*_it).getPosY())//Si laser collision
				{
					_itLaserAffiche = _listLaser.erase(_itLaserAffiche);
					break;
				}
			}
		}
	}
}

//fonction d’ouverture du ficher contenant la matrice
void readFile(Map<int> &mapLabyrinthe, const char* nomFichier)
{
	ifstream fichier(nomFichier);  //ouverture du ficher
	int nbLine, nbCol;

	if (fichier.is_open()) //lit si fichier ouvert
	{
		if (mapLabyrinthe.nbLine() > 0 && mapLabyrinthe.nbCol() > 0)
			mapLabyrinthe.clearMap();

		mapLabyrinthe.setName(nomFichier);
		fichier >> nbLine >> nbCol;
		mapLabyrinthe.resize(nbLine, nbCol);

		fichier >> mapLabyrinthe;		//lecture de la matrice
		fichier.close();
	}
	else
		cout << "Fichier : " << nomFichier << " innexistant";
}
