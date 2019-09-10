#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>


using namespace std;
using namespace sf;

class MainMenu
{
private:
	RenderWindow _window;

	Texture		_textPlay;		//Texture bouton play
	IntRect		_recPlay;		//Rectangle bouton play
	Sprite		_buttonPlay;	//Sprite bouton play

	Texture		_textQuit;		//Texture bouton quit
	IntRect		_recQuit;		//Rectangle bouton quit
	Sprite		_buttonQuit;	//Sprite bouton quit

	Texture		_textOiseau;	//Texture de l'oiseau
	IntRect		_recOiseau;		//Rectangle de l'oiseau
	Sprite		_oiseau;		//Sprite de l'oiseau
	Sprite		_oiseau2;

	Texture		_textBackground;//Arriere-plan texture
	Sprite		_background;	//Arriere-plan

	float		_posPlayX;		//Position x bouton play
	float		_posPlayY;		//Position y bouton play

	float		_posQuitX;		//Position x bouton quit
	float		_posQuitY;		//Position y bouton quit

	float		_posOiseauX;	//Position x de l'oiseau
	float		_posOiseauY;	//Position y de l'oiseau
	float		_posOiseauX2;
	float		_posOiseauY2;
	float		_vitesseX;		//Vitesse deplacement de l'oiseau

	float		_mouseX;		//Posiiton x souris
	float		_mouseY;		//Position y souris

	bool		_quit;			//Si on quitte le jeu

	Clock		_tempsSpriteOiseau;	//Pour changer l'animation de l'oiseau
	Clock		_tempsDepOiseau;	//Temps pour changer la position de l'oiseau
	Clock		_tempsSonOiseau;	//Pour faire les cris d'oiseau

	Music		_music;				//Musique du menu principal
	Sound		_sonCrow;			//Bruit des corbeaux
	SoundBuffer _buffer;			//Buffer pour le son

public:
	MainMenu();				//Constructeur

	void	run();			//Fait fonctionner le menu principal

	void	animationOiseau();		//Animation de l'oiseau
	void	deplacementOiseau();	//Deplacement de l'oiseau

	bool	getQuit();		//Si l'utilisateur quitte le jeu
};
