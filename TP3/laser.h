#pragma once

#define _USE_MATH_DEFINES // pi (3,14...)

#include <SFML/Graphics.hpp>
#include <cmath>

using namespace sf;

class laser
{
private:
	Texture		_textLaser;	//Texture du laser
	IntRect		_recLaser;	//Rectangle pour la texture
	Sprite		_laser;		//Sprite du laser

	int			_positionX;			//Position x du laser
	int			_positionY;			//Posiiton y du laser
	int			_positionXDepart;	//Position depart x de la tour
	int			_positionYDepart;	//Position depart y de la tour
	int			_vitesseX;			//Vitesse x de deplacement
	int			_vitesseY;			//Vitesse y de deplacement
	int			_distance;			//Distance entre tour et squelette (direction du laser)
	int			_vitesse;			//Vitesse generale

	float		_angle;	//L'angle du laser (sa direction)

	Clock		_tempsLaser;	//Temps pour un laser

public:
	laser();	//Constructeur

	void	deplacement();
	void	afficheLaser(RenderWindow& window)const; //Affiche le laser

	void	setAngle(int posSkX, int posSkY, int posTourX, int posTourY);	//Trouver l'angle du laser
	void	setPos(int posX, int posY);										//set la posiiton du laser
	void	setPosDepart(int posX, int posY);								//Set la posiiton de depart du laser

	int		getPosX()const; //Obtenir la position x
	int		getPosY()const; //Obtenir la position y	

	int		getPosDepartX()const; //Obtenir position de depart du laser x
	int		getPosDepartY()const; //Obtenir position de depart laser y
};