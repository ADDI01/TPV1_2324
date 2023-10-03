#pragma once
#include <iostream>
#include "Coche.h"

#ifndef LISTACOCHES_H_
#define LISTACOCHES_H_
using namespace std;


class ListaCoches
{
private:
	Coche** coches;
	int cont, nElems;

public:
	ListaCoches();
	ListaCoches(Coche** c, int co, int nE);
	~ListaCoches();

	friend class ListaAlquileres;
	bool leerModelos();
	int buscarCoche(int codigo);
};

#endif // !LISTACOCHES_H_

