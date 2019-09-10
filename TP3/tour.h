/**/

#pragma once

#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Skeleton.h"

using namespace sf;
class tour
{
private:
	int		_positionX;		//position en pixel x
	int		_positionY;		//Position en pixel y
	int		_porte;			//Porté de tir
	int		_degat;			//Nombre de dégat par tir
	int		_cadence;		//Cadence de tir
	int		_tempsConstr;	//Temps requis pour la construction

	bool	_tir;
	bool	_enConstr;		//Si en construction

	Clock	_gCDTir;			// Global cooldown pour les tires
	Clock	_Constr;			// Clock pour la construction

	Texture		_textTour;		//Texture de la tour
	Texture		_textConstr;	//Texture de la tour en construction
	IntRect		_recSourceTour;	//Rectangle pour la texture a appliquer
	Sprite		_tour;			//La tour


	int			_type;			// Type de tour


public:
	tour(int type, int posX, int posY);

	void	afficheTour(RenderWindow &window) const;	//Affiche les tours

	void	initTexture();		//Initialise la texture des tours

	bool	tire(Skeleton&);	//Tir sur les squelettes

	int		getPosX()const;		//Retourne position x de la tour
	int		getPosY()const;		//Retourne position y de la tour

	bool	getTir()const;		//Retourne le tir
	void	setTir(bool siTir);	//La tour tir ou non 	

	int getTempsConstr() const;
};