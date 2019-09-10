#include"laser.h"

//Constructeur
laser::laser()
{
	_textLaser.loadFromFile("laser_red.png");

	_recLaser.height = 16;
	_recLaser.width = 60;
	_recLaser.left = 0;
	_recLaser.top = 0;

	_laser.setTexture(_textLaser);
	_laser.setTextureRect(_recLaser);

	_vitesse = 20;

	_positionXDepart = 0;
	_positionYDepart = 0;
}

//Deplacer le laser avec rotation
void laser::deplacement()
{
	if (_tempsLaser.getElapsedTime().asMilliseconds() > 10);
	{
		_laser.setPosition(_positionX += _vitesseX,_positionY += _vitesseY);
		_tempsLaser.restart();
	}
}

//Affiche le laser
void laser::afficheLaser(RenderWindow& window)const
{
	window.draw(_laser);
}

//Positionner le laser
void laser::setPos(int posX, int posY)
{
	_positionX = posX + 40;
	_positionY = posY + 60;
	_laser.setPosition(_positionX, _positionY);
}

//Posiiton de depart
void laser::setPosDepart(int posX, int posY)
{
	_positionXDepart = posX + 60;
	_positionYDepart = posY + 40;
}

//Set l'angle du tir
void laser::setAngle(int posSkX, int posSkY, int posTourX, int posTourY)
{
	//Trouve l'angle de la direction
	_angle = atan2(posTourY - posSkY, posTourX - posSkX);
	_angle = (_angle * 180) / M_PI;

	//Calcule la distance entre la tour et l'ennemi
	_distance = sqrt((posSkX - posTourX)*(posSkX - posTourX) + (posSkY - posTourY)*(posSkY - posTourY));

	//Les vitesses de deplacements
	_vitesseX = _vitesse*(posSkX - posTourX) / _distance;
	_vitesseY = _vitesse*(posSkY - posTourY) / _distance;

	_laser.setRotation(_angle);
}


//Obtenir la position x
int laser::getPosX()const
{
	return _positionX;
}

//Obtenir la position y	
int laser::getPosY()const
{
	return _positionY;
}

//Obtenir position de depart du laser x
int	laser::getPosDepartX()const
{
	return _positionXDepart;
}

//Obtenir position de depart laser y
int	laser::getPosDepartY()const
{
	return _positionYDepart;
}