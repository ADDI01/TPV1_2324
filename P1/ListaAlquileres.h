#pragma once
#include "checkML.h"
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
	~ListaAlquileres();

	bool leerAlquileres(ListaCoches& listaCoches);
	static bool comparador(const Alquiler* a, const Alquiler* b);
	void ordenarAlquileres();
	void mostrarAlquileres();
};



#endif // !LISTAALQUILERES_H_

