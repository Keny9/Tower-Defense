#include "Tour.h"

//Constructeur
tour::tour(int type, int posX, int posY)
{
	assert(type < 4 && type >= 0);

	_type = type;
	_positionX = posX;
	_positionY = posY;

	_textConstr.loadFromFile("building.png");

	if (_type == 0) //Type tour 0
	{
		_textTour.loadFromFile("tower0.png");
		_degat = 1;
		_cadence = 2;
		_porte = 115;
		_tempsConstr = 3;
	}	
	else 		//Type tour 1
	{
		_textTour.loadFromFile("tower1.png");
		_degat = 4;
		_cadence = 4;
		_porte = 230;
		_tempsConstr = 10;
	}

	_recSourceTour = { 0,0,120,120 };
	_tour.setTextureRect(_recSourceTour);

	_tour.setPosition(_positionX, _positionY);

	_tir = false;
	_enConstr = true;
}

//Afficher la tour
void tour::afficheTour(RenderWindow &window) const
{
	window.draw(_tour);
}

//Init la texture
void tour::initTexture()
{
	if (_enConstr == true)
	{
		if (_Constr.getElapsedTime().asSeconds() >= _tempsConstr)
		{
			_enConstr = false;
			_tour.setTexture(_textTour);
		}		
		else
			_tour.setTexture(_textConstr);				
	}
}

//La tour tire sur les squelettes selon la portee
bool tour::tire(Skeleton& skelette)
{
	// Si prête à tirer et pas en constrution
	if (_enConstr == false &&_gCDTir.getElapsedTime().asSeconds() >= _cadence)
	{
		if (skelette.getPosX() > (float)(_positionX - _porte) && skelette.getPosX() < (float)(_positionX + _porte + 120) && (skelette.getPosY() < (float)(_positionY + _porte + 120) && skelette.getPosY() > (float)(_positionY - _porte )))
		{
			skelette.degat(_degat); //Enleve la vie du squelette
			_gCDTir.restart();
			return true;
		}
	}
	return false;
}

//Retourne position x de la tour
int tour::getPosX()const
{
	return _positionX;
}

//Retourne position y de la tour
int tour::getPosY()const
{
	return _positionY;
}

//Retourne le tir
bool tour::getTir()const
{
	return _tir;
}

//La tour tir ou non
void tour::setTir(bool siTir)
{
	_tir = siTir;
}

//Retourne temps construction
int tour::getTempsConstr()const
{
	return _tempsConstr;
}