#include "Skeleton.h"


//Constructeur
Skeleton::Skeleton()
{
	_positionX = -100;
	_positionY = 750;
	_vitesseX = 2;
	_vitesseY = 0.5;

	_textSkeleton.loadFromFile("skeleton.png");

	_recSourceSkeleton.left = 256;
	_recSourceSkeleton.top = 192;
	_recSourceSkeleton.width = 64;
	_recSourceSkeleton.height = 64;

	_skeleton.setTexture(_textSkeleton);
	_skeleton.setTextureRect(_recSourceSkeleton);
	_skeleton.setPosition(_positionX, _positionY);

	_vie = 12;
}

//Change l'animatiomn du squelette
void Skeleton::changeAnimation(IntRect tile[9][16])
{
	if (_tempsSpriteSkeleton.getElapsedTime().asMilliseconds() > 75)
	{
		if (_positionX == tile[2][10].left + 40 && _positionY >= tile[2][10].top && _positionY <= tile[4][10].top) //Direction vers le bas
			_recSourceSkeleton.top = 128;
		else if (_positionX == tile[6][10].left + 40 && _positionY <= tile[7][10].top && _positionY >= tile[4][10].top + 5) //Aller vers le haut
			_recSourceSkeleton.top = 0;
		else
			_recSourceSkeleton.top = 192;		//Vers la droite

												//Passe au travers du sprite sheet
		if (_recSourceSkeleton.left == 512)
			_recSourceSkeleton.left = 0;
		else
			_recSourceSkeleton.left += 64;

		_skeleton.setTextureRect(_recSourceSkeleton);
		_tempsSpriteSkeleton.restart();
	}
}

//Deplacement fluide du squelette
void Skeleton::deplacement(IntRect tile[9][16])
{
	if (_tempsDepSkeleton.getElapsedTime().asMilliseconds() > 50)
	{
		if (_positionX == tile[2][10].left + 40 && _positionY >= tile[2][10].top && _positionY <= tile[4][10].top) //Pour aller vers le bas
			_skeleton.setPosition(_positionX, _positionY += _vitesseY);
		else if (_positionX == tile[6][10].left + 40 && _positionY <= tile[7][10].top && _positionY >= tile[4][10].top + 5) //Aller vers le haut
			_skeleton.setPosition(_positionX, _positionY -= _vitesseY);
		else	//Aller vers la droite
		{
			_skeleton.setPosition(_positionX += _vitesseX, _positionY);
			_tempsDepSkeleton.restart();
		}
	}
}

//Affiche le personnage
void Skeleton::afficheNpc(RenderWindow& window)const
{
	window.draw(_skeleton);
}

//Changer la position du npc
void Skeleton::setPosition(float x, float y)
{
	_positionX = x;
	_positionY = y;
}

//Perd de la vie
void Skeleton::degat(int degat)
{
	_vie -= degat;
}

//Changer la vitesse 
void Skeleton::setVitesse(float vitesseX)
{
	_vitesseX = vitesseX;
}

//Retorune la vie
int Skeleton::getVie()const
{
	return _vie;
}

//Retourne position de x
float Skeleton::getPosX()const
{
	return _positionX;
}

//Retourne position de y
float Skeleton::getPosY()const
{
	return _positionY;
}