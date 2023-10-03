#include "ListaAlquileres.h"
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

ListaAlquileres::ListaAlquileres() : alquileres(nullptr), cont(0), nElems(0) {}
ListaAlquileres::~ListaAlquileres() {
	for (int i = 0; i < cont; i++) {
		delete alquileres[i];
		alquileres[i] = nullptr;
	}
	delete[] alquileres;
	alquileres = nullptr;
}

bool ListaAlquileres::leerAlquileres(ListaCoches& listaCoches) {
	ifstream entrada("rent.txt");
	int cod, d;
	bool valido = false;
	Date f;
	Coche* c = nullptr;

	if (!entrada.is_open()) return false;
	
	entrada >> cont;
	nElems = cont + 10;
	alquileres = new Alquiler * [nElems];

	for (int i = 0; i < cont; i++)
	{
		entrada >> cod;
		entrada >> f;
		entrada >> d;
		alquileres[i] = new Alquiler(cod, f, d, valido, c); //Se crea el alquiler una vez recogidos los datos

		int indiceCoche = listaCoches.buscarCoche(cod);
		if (indiceCoche != -1)
		{
			int aux = listaCoches.coches[indiceCoche]->getPrecio();
			alquileres[i]->setCoche(listaCoches.coches[indiceCoche]);
			alquileres[i]->setCocheValido(true);
		}
	}
	entrada.close();

	return true;
}

bool ListaAlquileres::comparador(const Alquiler* a, const Alquiler* b) {
	return *a < *b;
}

void ListaAlquileres::ordenarAlquileres() {
	sort(alquileres, &alquileres[cont], &comparador);
}

void ListaAlquileres::mostrarAlquileres() {
	//Renderiza en consola
	for (int i = 0; i < cont; i++)
	{
		if (alquileres[i]->getCocheValido())
		{
			cout << alquileres[i]->getFecha() << " " << alquileres[i]->getCoche()->getNombre() << " " <<
				alquileres[i]->getDias() << " dia (s) por " << alquileres[i]->getCoche()->getPrecio() *
				alquileres[i]->getDias() << " euros" << endl;
		}
		else
		{
			cout << alquileres[i]->getFecha() << "  ERROR: Modelo inexistente" << endl;
		}

	}
	//Salida como archivo de texto
	ofstream salida("Nueva Salita.txt");
	if (salida.is_open())
	{
		for (int i = 0; i < cont; i++)
		{
			if (alquileres[i]->getCocheValido())
			{
				salida << alquileres[i]->getFecha() << " " << alquileres[i]->getCoche()->getNombre() << " " <<
					alquileres[i]->getDias() << " dia (s) por " << alquileres[i]->getCoche()->getPrecio() *
					alquileres[i]->getDias() << " euros" << endl;
			}
			else
			{
				salida << alquileres[i]->getFecha() << "  ERROR: Modelo inexistente" << endl;
			}
		}
	}
	salida.close();
}