#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <list>
#include <queue>
#include "Skeleton.h"
#include "Map.h"
#include <fstream>
#include <iostream>
#include "tour.h"
#include "laser.h"
#include "peon.h"

using namespace std;
using namespace sf;

class Game
{
private:
	int _typeTour;				//Type de tour selectionné
	bool _victoire;				//Gagné
	bool _defaite;				//Perdu
	int _nbVie;					//Nombre de vie avant la défaite
	float _timerSpawnSkelette;	//

	RenderWindow		_window;	//Fenetre du jeu
	Map<int>			_carte;		//Carte du jeu en int
	Skeleton			_skeleton;	//Squelette ennemi

	queue<Skeleton>		_fileSkeleton;	//File de squelette pour aller dans le jeu

	list<Skeleton>				_listSkeleton;	//Liste des squelettes
	list<Skeleton>::iterator	_itSkeleton;	//Itere sur la liste de squelette a l'ajout
	list<Skeleton>::iterator	_it;			//Pour iterer sur toute la liste

	Clock		_tempsApparition;	//Le temps pour faire apparaitre nouveau bonhomme
	Clock		_tempsAttaque;		//Gère la vitesse de la boucle d'interaction tour/skelette

	Texture		_textTile;			//Texture de la map
	IntRect		_recTile[9][16];	//Les rectangles de la map
	IntRect		_recSprite[1][8];	//Les rectangles de chaque tuile du sprite
	Sprite		_tile;				//La tuile a afficher

	list<tour>	_tour;						//Liste des tours
	list<tour>::iterator _itTourSpawn;		//Itérateur pour la liste des tours
	list<tour>::iterator _itTourAffiche;	//Itérateur pour afficher les tours

	laser					_laser;				//Laser
	list<laser>				_listLaser;			//Liste des lasers tirer
	list<laser>::iterator	_itLaser;			//Iterateur laser 
	list<laser>::iterator	_itLaserAffiche;	//Itere sur toute la liste

	list<peon>				_peon;				//Liste de peon
	list<peon>::iterator	_itPeonSpawn;		//Iterateur pour faire spawn un peon
	list<peon>::iterator	_itPeonAffiche;		//Iterateur pour afficher les peons

	Vector2i	_positionClick;			//Position du curseur après un click

	Music			_music;				//Musique du jeu principal
	SoundBuffer		_buffer;			//Buffer pour le son
	Sound			_sonLaser;			//Bruit du laser

	SoundBuffer		_bufferWork;		//Buffer pour le "work work"
	Sound			_work;				//"work work"

public:

	Game();

	void	run();						//Demarrage du jeu

	void	initialiserRectPosition();	//Initialise les rectangles
	void	genererMap();				//Genere la map

	void	spawnSquelette();			//Gere les squelettes

	void	print();					//Affiche les differents objets du jeu

	void	placerTour(int posX, int posY); //Place une tour
	bool	positionValide();				//Verifie si on peut placer une tour
	void	attaqueSquelette();				//Si les tours ont un squelette a attaquer
	
	void	deplacementLaser();				//Deplacement des lasers
	void	deplacementPeons();				//Deplacement des peons

	void	laserColision();				//Collision entre les lasers et squelettes
};
void readFile(Map<int> &mapLabyrinthe, const char* nomFichier);
