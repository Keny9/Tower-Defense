/*Programme: main.cpp
Auteur: Karl Boutin
Date: 2018-11-16
But du programme: Création de la classe liste
avec différentes méthodes nous permettant de manipuler
une liste.*/

#pragma once

#include<assert.h>

template <typename TYPE> class list;

//Classe cellule
template <typename TYPE>
class cellule
{
	friend class list<TYPE>;	//la seule classe ayant accès à la 
								//représentation de la cellule
	TYPE element;				//Contenu de la cellule
	cellule <TYPE> *next;		//Pointeur vers la cellule suivante 
	cellule <TYPE> *previous;	//Pointeur vers la cellule precedente

	cellule(const TYPE &e, cellule<TYPE> *n = nullptr, cellule<TYPE> *p = nullptr)
	{
		element = e;
		next = n;
		previous = p;
	}
};

template <typename TYPE>
class list
{
private:
	cellule <TYPE> *_first;			//Adresse du premier élément 

	list(const list<TYPE> &l);		//Copieur désactivé
public:
	class iterator
	{
		friend class list<TYPE>;

	private:
		cellule<TYPE>* 	_current;	//adresse de la cellule
		const list<TYPE>* _list;	//adresse de la liste

	public:
		iterator();					//constructeur
		~iterator();				//destructeur

		const iterator& operator=(const iterator& it);//pour j=i

		bool operator==(const iterator& it)const; //pour if(j==i)
		bool operator!=(const iterator& it)const; //pour if(j!=i)

		iterator operator++(int i);			//i++
		const iterator& operator++();		//++i

		iterator operator--(int i);			//i--
		const iterator& operator--();		//--i

		TYPE& operator*();					//accès à un élément
		const TYPE& operator*()const;		//idem, en mode const

	};
	list();		//Constructeur
	~list();	//Destructeur

	void clear();
	bool empty()const;				//verifie si la liste est vide

	iterator begin()const;			//return premier
	iterator end()const;			//return nullptr

	iterator insert(iterator it, const TYPE& e);	//Insere une cellule dans la liste
	iterator erase(iterator it);					//Supprime une cellule
	iterator erase(iterator first, iterator last);

	TYPE& operator[](iterator it);	//pas ds la STL
	const TYPE& operator[](iterator it)const;

	//chercher dans la liste l’élément reçu en paramètre
	//et à partir de l’itérateur reçu pour la version 2
	//la méthode  retourne un iterator sur l’element trouvé
	//s’il est innexistant, l’iterator est à la fin 
	iterator operator()(const TYPE&)const;
	iterator operator()(const TYPE&, iterator)const;

	//const list<TYPE>& operator=(const list<TYPE>& l);
};

//Constructeur iterator
template <typename TYPE>
list<TYPE>::iterator::iterator()
{
	_current = nullptr;
	_list = nullptr;
}

//Destructeur iterator
template <typename TYPE>
list<TYPE>::iterator::~iterator()
{
	_current = nullptr;
	_list = nullptr;
}

//Affectateur de l'iterateur
template <typename TYPE>
typename const list<TYPE>::iterator& list<TYPE>::iterator::operator=(const iterator&
	it)
{
	_current = it._current;
	_list = it._list;
	return *this;
}

//Surcharge de l'operateur ==
template <typename TYPE>
bool list<TYPE>::iterator::operator==(const iterator& it)const
{
	assert(_list == it._list);
	return _current == it._current;
}

//Surcharge de l'operateur !=
template <typename TYPE>
bool list<TYPE>::iterator::operator!=(const iterator& it)const
{
	assert(_list == it._list);
	return _current != it._current;
}

//Surcharge de l'operateur ++ post-incrementateur
template <typename TYPE>
typename list<TYPE>::iterator list<TYPE>::iterator::operator++(int i) //it++
{
	list<TYPE>::iterator it = *this;
	operator++();
	return it;
}

//Surcharge de l'operateur ++ pre-incrementation
template <typename TYPE>
typename const list<TYPE>::iterator& list<TYPE>::iterator::operator++() //++it
{
	assert(_list != nullptr);
	assert(_current != nullptr);

	if (_list->_first->previous != _current)
		_current = _current->next;
	else
		_current = nullptr;

	return *this;
}

//Surcharge de l'operateur -- post-decrementation
template <typename TYPE>
typename list<TYPE>::iterator list<TYPE>::iterator::operator--(int i) //it--
{
	list<TYPE>::iterator it = *this;
	operator--();
	return it;
}

//Surcharge de l'operateur -- pre-decrementation
template <typename TYPE>
typename const list<TYPE>::iterator& list<TYPE>::iterator::operator--() //--it
{
	assert(_list != nullptr);
	assert(_current != _list->_first);

	if (_current != nullptr)
		_current = _current->previous;
	else
		_current = _list->_first->previous;

	return *this;
}

//Retourne l'element en reference
template <typename TYPE>
TYPE& list<TYPE>::iterator::operator*()
{
	assert(_list != nullptr); //Iterateur positionne
	assert(_current != nullptr);
	return _current->element;
}

//Retourne l'element ou est l'iterateur en constante reference
template <typename TYPE>
const TYPE& list<TYPE>::iterator::operator*()const
{
	assert(_list != nullptr);	//Iterateur positionne
	assert(_current != nullptr);
	return _current->element;
}

//Constructeur liste
template <typename TYPE>
list<TYPE>::list()
{
	_first = nullptr;
}

//Destructeur liste
template <typename TYPE>
list<TYPE>::~list()
{
	clear();
}

//Vide la liste
template <typename TYPE>
void list<TYPE>::clear()
{
	list<TYPE>::iterator it;

	for (it = begin(); it != end();)
		it = erase(it);
}

//Verifie si la liste est vide
template <typename TYPE>
bool list<TYPE>::empty()const
{
	return _first == nullptr;
}

//Retourne un iterateur qui pointe au debut de la liste
template <typename TYPE>
typename list<TYPE>::iterator list<TYPE>::begin()const
{
	list<TYPE>::iterator it;	//Iterateur sur le debut (1ere cellule)

	it._list = this;
	it._current = _first;

	return it;
}

//Retourner un iterateur qui pointe a la fin de la liste
template <typename TYPE>
typename list<TYPE>::iterator list<TYPE>::end()const
{
	list<TYPE>::iterator it;	//Iterateur sur le debut (1ere cellule)

	it._list = this;
	it._current = nullptr;

	return it;
}

//Inserer une nouvelle cellule dans la liste
template <typename TYPE>
typename list<TYPE>::iterator list<TYPE>::insert(iterator it, const TYPE& ele)
{
	assert(it._list == this);

	if (empty()) //1ere cellule a creer
		it._current = _first->previous = _first->next = _first = new cellule<TYPE>(ele);
	else if (it._current == nullptr) //insere a la fin
		it._current = _first->previous = _first->previous->next =
		new cellule<TYPE>(ele, _first, _first->previous);
	else
	{
		it._current->previous = it._current->previous->next =
			new cellule<TYPE>(ele, it._current, it._current->previous);

		if (it._current == _first)
			_first = _first->previous;

		it._current = it._current->previous;
	}
	return it;
}

//Supprimer une cellule
template <typename TYPE>
typename list<TYPE>::iterator list<TYPE>::erase(iterator it)
{
	assert(it._current != nullptr);
	assert(it._list == this);
	assert(!empty());

	cellule<TYPE> *aDetruire = it._current;

	if (_first == _first->next) //Si un seul element
	{
		it._current = _first = nullptr;
	}
	else if (it._current == _first->previous) //Si sur le dernier element
	{
		it._current->previous->next = _first;
		it._current = _first->previous = it._current->previous;
	}
	else
	{
		//Cellule apres pointe avant celle supprimer
		it._current->next->previous = it._current->previous;
		//Cellule avant pointe apres celui supprimer
		it._current->previous->next = it._current->next;
		//Pointe sur la cellule qui a pris la position de l'ancienne
		it._current = it._current->next;

		if (aDetruire == _first) //Cas limite, reste qu'une seule cellule
			_first = _first->next;
	}

	delete aDetruire;

	return it;
}

//Effacer entre 2 positions
template <typename TYPE>
typename list<TYPE>::iterator list<TYPE>::erase(iterator first, iterator last)
{
	assert(first._list == this && last._list == this);
	assert(!empty());

	while (first != last)
		first = erase(first);

	if (first != last)
		first = erase(first);

	return first;
}

//Retourne l'element ou l'iterateur pointe
template <typename TYPE>
TYPE& list<TYPE>::operator[](iterator it)
{
	assert(it._list == this);
	return *it;
}

//Retourne l'element en constante reference
template <typename TYPE>
const TYPE& list<TYPE>::operator[](iterator it)const
{
	return *it;
}

//Recherche dans la liste l'element pour renvoyer un iterateur
template <typename TYPE>
typename list<TYPE>::iterator list<TYPE>::operator()(const TYPE& ele)const
{
	return operator()(ele, begin());
}

//Recherche un element a l'aide d'un element et un iterateur en parametre
template <typename TYPE>
typename list<TYPE>::iterator list<TYPE>::operator()(const TYPE& ele, iterator it)const
{
	assert(it._list == this);

	for (; it != end(); it++) //Cherche l'element en parametre
	{
		if (it._current->element == ele)
			return it;
	}
	return it;
}

