#pragma once

#include <SFML/Graphics.hpp>
#include<queue>	

using namespace sf;

class Skeleton
{
private:
	float		_positionX;	//position en pixel x
	float		_positionY;	//Position en pixel y
	float		_vitesseX;	//Vitesse x
	float		_vitesseY;	//Vitesse y

	int			_vie;		//Vie du squelette

	Texture		_textSkeleton;		//Texture du squelette
	IntRect		_recSourceSkeleton;	//Rectangle pour la texture a appliquer
	Sprite		_skeleton;			//Le squelette

	Clock		_tempsSpriteSkeleton;	//Temps pour changer le sprite
	Clock		_tempsDepSkeleton;		//Temps pour changer le deplacement

public:
	Skeleton();		//Constructeur

	void	changeAnimation(IntRect tile[9][16]);	//Change l'animation du squelette
	void	deplacement(IntRect tile[9][16]);		//Deplacement fluide du squelette

	void	afficheNpc(RenderWindow& window)const;	//Afficher le personnage

	void	setPosition(float x, float y);			//Changer la posiiton du npc
	void	setVitesse(float vitesseX);				//Changer la vitesse du personnage
	void	degat(int degat);						//Degat recu 

	float	getPosX()const;		//Retourne position de x
	float	getPosY()const;		//Retourne position de y
	int		getVie()const;		//Retourne la vie
};

