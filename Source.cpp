// Julián Serrano Chacon 
// David Palacios Daza
// Grupo 02

#include "ListaCoches.h"
#include "ListaAlquileres.h"
#include <fstream>
#include <string>
#include <Windows.h>

using namespace std;

int main()
{
	//Para windows 11 es el UTF7, para winsows 10 es UTF8
	SetConsoleOutputCP(CP_UTF8);
	ListaCoches listaCoches;
	ListaAlquileres listaAlquileres;

	if (!listaCoches.leerModelos() || !listaAlquileres.leerAlquileres(listaCoches))
		cout << "ERROR: Lectura de datos fallida" << endl;

	listaAlquileres.ordenarAlquileres();
	listaAlquileres.mostrarAlquileres();

	//Destructores
	listaCoches.~ListaCoches();
	listaAlquileres.~ListaAlquileres();

	return 0;
}