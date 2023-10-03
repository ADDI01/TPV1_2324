// Julián Serrano Chacon 
// David Palacios Daza
// Grupo 02

#include "ListaCoches.h"
#include "ListaAlquileres.h"
#include <fstream>
#include <string>
#include <Windows.h>
#include "checkML.h"

using namespace std;

//TODO:


int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//Para windows 11 es el UTF7, para winsows 10 es UTF8
	SetConsoleOutputCP(CP_UTF8);
	ListaCoches listaCoches;
	ListaAlquileres listaAlquileres;

	int* i = new int(5);

	if (!listaCoches.leerModelos() || !listaAlquileres.leerAlquileres(listaCoches))
		cout << "ERROR: Lectura de datos fallida" << endl;

	listaAlquileres.ordenarAlquileres();
	listaAlquileres.mostrarAlquileres();

	//Destructores
	listaCoches.~ListaCoches();
	listaAlquileres.~ListaAlquileres();

	return 0;
}