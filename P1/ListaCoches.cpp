#include "ListaCoches.h"
#include <fstream>
#include <string>

using namespace std;

ListaCoches::ListaCoches() : coches(nullptr), cont(0), nElems(0) {};
ListaCoches::ListaCoches(Coche** c, int co, int nE) : coches(c), cont(co), nElems(nE) {}
ListaCoches::~ListaCoches() {
	for (int i = 0; i < cont; ++i) {
		delete coches[i];
		coches[i] = nullptr;
	}
	delete[] coches;
	coches = nullptr;
}

bool ListaCoches::leerModelos()
{
	ifstream entrada("coches.txt");
	int cod, pre;
	string mod = "";
	if (!entrada.is_open()) return false;

	entrada >> cont;
	nElems = cont + 10;
	coches = new Coche * [nElems];
	for (int i = 0; i < cont; i++)
	{
		entrada >> cod;
		entrada >> pre;
		getline(entrada, mod);
		coches[i] = new Coche(cod, pre, mod);
	}
	entrada.close();
	
	return true;
}

int ListaCoches::buscarCoche(int codigo) {
	int abajo = 0, arriba = cont - 1, indice = -1, centro;

	while (abajo <= arriba && indice == -1)
	{
		centro = (abajo + arriba) / 2;
		if (coches[centro]->getCodigo() == codigo)
		{
			indice = centro;
		}
		else if (codigo < coches[centro]->getCodigo())
		{
			arriba = centro - 1;
		}
		else if (codigo > coches[centro]->getCodigo())
		{
			abajo = centro + 1;
		}
	}
	return indice;
}