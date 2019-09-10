#include "peon.h"

//Constructeur
peon::peon(int posX, int posY, int dureeConstr)
{
	_positionX = posX;
	_positionY = posY;
	_nmSprite = 0;

	_dureeConstr = dureeConstr;

	_text.loadFromFile("peon.png");
	_recSource = { 0 ,0 , 56, 45 };
	_peon.setTextureRect(_recSource);
	_peon.setPosition(posX, posY);
}

//Mouvement du peon
void peon::mouvement()
{
	if (_tempsMouvement.getElapsedTime().asMilliseconds() >= 200)
	{
		_recSource.top = 45 * _nmSprite;

		// équiliber le spritesheet
		if (_nmSprite >= 4)
			_recSource.top -= 2;

		_nmSprite++;
		_nmSprite %= 5;

		_peon.setTextureRect(_recSource);

		_tempsMouvement.restart();
	}
}

//Init du peon
void peon::init()
{
	_peon.setTexture(_text);
}

//Affichage du peon
void peon::affichePeon(RenderWindow &window)
{
	window.draw(_peon);
}

//S'il a fini de construire ou non
bool peon::constrTermine()const
{
	return _constr.getElapsedTime().asSeconds() >= _dureeConstr + 0.5;
}