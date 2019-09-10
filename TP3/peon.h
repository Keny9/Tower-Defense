/**/
#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

class peon
{
private:
	int		_positionX;		//position en pixel x
	int		_positionY;		//Position en pixel y
	int		_nmSprite;		//Numero du sprite à selectionner
	int		_dureeConstr;	//Durée de la construction

	Texture		_text;			//Texture de la tour
	IntRect		_recSource;		//Rectangle pour la texture a appliquer
	Sprite		_peon;			//La tour

	Clock		_tempsMouvement;// Pour le changement de sprite
	Clock		_constr;		//Pour la durée de la construction
public:
	peon(int posX, int posY, int dureeConstr);

	void mouvement();		// fait changer de sprite
	void init();			// init la texture
	void affichePeon(RenderWindow &window);	 //affiche le peon

	bool constrTermine()const;	//Si la construction est terminée
};

