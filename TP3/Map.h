/*Nom:Karl Boutin
Programme:map.hpp
Date:2018-10-10
But du programme:Classe d'une map a 2 dimensions qu'on peut utiliser
a l'aide de diverses methodes nous permettant de la gerer
*/

#pragma once

#include<assert.h>
#include<iostream>

using namespace std;

template <class TYPE>
class Map
{
private:
	char	*_name;		//pointeur sur le nom de la map
	TYPE	**_map;		//La map dynamique en ligne et colonne
	int		_nbLine;	//Nombre de ligne pour la matrice
	int		_nbCol;		//Nombre de colonne pour la matrice

public:
	Map();
	Map(const char* name, int line, int col);
	Map(const Map<TYPE>& map);
	~Map();
	void clearName();						//Supprime le nom
	void clearMap();						//Supprime la map

											//getteurs et setteurs
	int nbLine()const;						//retourne le nb de ligne
	int nbCol()const;						//retourne le nb de colonne
	void resize(int line, int col);			//resize la matrice avec nouv dims

	TYPE& at(int posI, int posJ)const;		//retourne une référence à l’élément 
											//à la position i,j pour accéder

	const char* getName()const;				//retourne le nom de la map		
	void setName(const char* name);			//modifie le nom de la map

	void print(ostream& sortie)const;		//print la matrice (sans le nom)
	void read(istream& entree);				//lit la matrice de la map ds le flux

	TYPE* operator[](int line)const;		//Surcharge []
	const Map<TYPE>& operator=(const Map<TYPE>&);//Affectateur
};

//Constructeur de la map sans parametre
template <class TYPE>
Map<TYPE>::Map()
{
	_map = nullptr;
	_name = nullptr;
	_nbLine = 0;
	_nbCol = 0;
}

//Constructeur avec parametre
template <class TYPE>
Map<TYPE>::Map(const char* name, int line, int col)
{
	assert(line >= 0 && col >= 0);

	_name = nullptr;
	_map = nullptr;

	if (strlen(name) > 0)	//Si name n'est pas vide
	{
		_name = new char[strlen(name) + 1];
		strcpy_s(_name, strlen(name) + 1, name); //Copie le parametre a _name
	}

	_nbLine = line;
	_nbCol = col;

	if (_nbLine > 0 && _nbCol > 0) //Creer la map avec son nb ligne et nb col
	{
		_map = new TYPE*[_nbLine];

		for (int i = 0; i < _nbLine; i++)
			*(_map + i) = new TYPE[_nbCol];
	}
}

//Copieur
template <class TYPE>
Map<TYPE>::Map(const Map<TYPE>& m)
{
	_map = nullptr;
	_name = nullptr;
	_nbLine = m._nbLine;
	_nbCol = m._nbCol;

	if (_nbLine > 0 && _nbCol > 0) //Creer la map
	{
		_map = new TYPE*[_nbLine];

		for (int i = 0; i < _nbLine; i++)
			*(_map + i) = new TYPE[_nbCol];

		for (int i = 0; i < _nbLine; i++)	//Copie des éléments
			for (int j = 0; j < _nbCol; j++)
				*(*(_map + i) + j) = *(*(m._map + i) + j);
	}

	if (strlen(m._name) > 0) // Si nom n'est pas vide creer nom
	{
		_name = new char[strlen(m._name) + 1];
		strcpy_s(_name, strlen(m._name) + 1, m._name); //Copie le parametre a _name
	}
}

//Destructeur
template <class TYPE>
Map<TYPE>::~Map()
{
	clearName();
	clearMap();
}

//Clear le nom
template <class TYPE>
void Map<TYPE>::clearName()
{
	delete[]_name;
	_name = nullptr;
}

//Clear la matrice
template <class TYPE>
void Map<TYPE>::clearMap()
{
	for (int i = 0; i < _nbLine; i++)
		delete[] * (_map + i);
	delete[]_map;

	_map = nullptr;
	_nbCol = 0;
	_nbLine = 0;
}

//Retourne le nb de ligne
template <class TYPE>
int Map<TYPE>::nbLine()const
{
	return _nbLine;
}

//Retourne le nb colonne
template <class TYPE>
int Map<TYPE>::nbCol()const
{
	return _nbCol;
}

//Retourner le nom de la map
template <class TYPE>
const char* Map<TYPE>::getName()const
{
	if (_name == nullptr)
		return "\0";
	return _name;
}

//Modifier le nom de la map
template <class TYPE>
void Map<TYPE>::setName(const char* name)
{
	clearName();

	if (strlen(name) > 0)	//Si name n'est pas vide
	{
		_name = new char[strlen(name) + 1];
		strcpy_s(_name, strlen(name) + 1, name); //Copie le parametre a _name
	}
}

//Afficher la map
template <class TYPE>
void Map<TYPE>::print(ostream& sortie)const
{
	for (int i = 0; i < _nbLine; i++)
	{
		for (int j = 0; j < _nbCol; j++)
		{
			sortie << *(*(_map + i) + j) << " ";
		}
		sortie << endl;
	}
}

//Lire la map dans un fichier
template <class TYPE>
void Map<TYPE>::read(istream& entree)
{
	for (int i = 0; i < _nbLine; i++) //Lecture de la map
		for (int j = 0; j < _nbCol; j++)
			entree >> *(*(_map + i) + j);
}

//Retourne un element de la map
template <class TYPE>
TYPE& Map<TYPE>::at(int posI, int posJ)const
{
	assert(posI >= 0 && posJ >= 0 && posI <= _nbLine && posJ <= _nbCol);
	return *(*(_map + posI) + posJ);
}

//Redimensionner la map
template <class TYPE>
void Map<TYPE>::resize(int line, int col)
{
	assert(line >= 0 && col >= 0);

	if (line == 0 && col == 0) //Redimensionne a une map vide
	{
		clearMap();
		return;
	}

	if (line == _nbLine && col == _nbCol) //On fait rien 
		return;

	TYPE **newMap = new TYPE*[line]; //Creation de la nouvelle map

	for (int i = 0; i < line; i++)
		*(newMap + i) = new TYPE[col];

	//Ajout des nombres jusqu'a la plus petite dim 
	for (int i = 0; i < _nbLine && i < line; i++)
		for (int j = 0; j < _nbCol && j < col; j++)
			*(*(newMap + i) + j) = *(*(_map + i) + j);

	clearMap();

	_nbCol = col;
	_nbLine = line;
	_map = newMap;
}

//Affectateur
template <class TYPE>
const Map<TYPE>& Map<TYPE>::operator=(const Map<TYPE>& map)
{
	//On retourne la map pusiqu'on veut affecter le meme
	if (this == &map) return *this;

	clearMap();
	_nbLine = map._nbLine;
	_nbCol = map._nbCol;

	if (_nbLine > 0 && _nbCol > 0)//Creer la map
	{
		_map = new TYPE*[_nbLine];

		for (int i = 0; i < _nbLine; i++)
			*(_map + i) = new TYPE[_nbCol];

		for (int i = 0; i < _nbLine; i++)	//Copie des éléments
			for (int j = 0; j < _nbCol; j++)
				*(*(_map + i) + j) = *(*(map._map + i) + j);
	}

	return *this;
}

//Surcharge []
template <class TYPE>
TYPE* Map<TYPE>::operator[](int line)const
{
	assert(line >= 0 && line < _nbLine);
	return *(_map + line);
}

template <class TYPE>
ostream& operator<<(ostream& sortie, const Map<TYPE>& map)
{
	map.print(sortie);
	return sortie;
}

template <class TYPE>
istream& operator >> (istream& entree, Map<TYPE>& map)
{
	map.read(entree);
	return entree;
}
