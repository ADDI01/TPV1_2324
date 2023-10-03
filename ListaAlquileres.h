#pragma once
#include "Alquiler.h"
#include "ListaCoches.h"
#include <iostream>

#ifndef LISTAALQUILERES_H_
#define LISTAALQUILERES_H_
using namespace std;

class ListaAlquileres
{
private:
	Alquiler** alquileres;
	int cont, nElems;
public:
	ListaAlquileres();
	//ListaAlquileres(Alquiler* a, int c, int elems);
	~ListaAlquileres();

	bool leerAlquileres(ListaCoches& listaCoches);
	bool comparador(const Alquiler* a, const Alquiler* b);
	void ordenarAlquileres();
	void mostrarAlquileres();
};



#endif // !LISTAALQUILERES_H_

