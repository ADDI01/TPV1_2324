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

void ImprimeOpcionesDeMenú();

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//Para windows 11 es el UTF7, para winsows 10 es UTF8
	SetConsoleOutputCP(CP_UTF7);
	ListaCoches listaCoches;
	ListaAlquileres listaAlquileres;

	if (!listaCoches.leerModelos() || !listaAlquileres.leerAlquileres(listaCoches))
		cout << "ERROR: Lectura de datos fallida" << endl;
	listaAlquileres.ordenarAlquileres();
	//cout << listaCoches;
	//cout << listaAlquileres;
	//listaAlquileres.mostrarAlquileres();

	return 0;
}

void ImprimeOpcionesDeMenú() 
{
	system("cls");
	cout << " Para Mostrar los Coches pulse:	1" << " Para Mostrar los Alquileres pulse:	2";
}