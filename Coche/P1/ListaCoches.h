#pragma once
#include <iostream>
#include "checkML.h"
#include "Coche.h"

#ifndef LISTACOCHES_H_
#define LISTACOCHES_H_
using namespace std;


class ListaCoches
{
private:
	Coche** coches;
	int cont, nElems;
	void ampliaArray();

public:
	ListaCoches();
	ListaCoches(Coche** c, int co, int nE);
	~ListaCoches();

	friend class ListaAlquileres;
	bool leerModelos();
	int buscarCoche(int codigo);
	friend std::ostream& operator<<(std::ostream& out, const ListaCoches& c);
	void insertaCoche( Coche& c);
};

#endif // !LISTACOCHES_H_

