// Juli�n Serrano Chacon 
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

void ImprimeOpcionesDeMen�();

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
	Alquiler a;
	Coche c;
	cin >> c;
	listaCoches.insertaCoche(c);

	cin >> a;
	listaAlquileres.insertaAlquiler(a, listaCoches);
	cout << listaAlquileres;

	//cout << listaCoches;
	//cout << listaAlquileres;
	//listaAlquileres.mostrarAlquileres();
	//ImprimeOpcionesDeMen�();

	return 0;
}

void ImprimeOpcionesDeMen�() 
{
	system("cls");
	cout << "Para mostrar los coches pulse:	 1" << endl << "Para mostrar los alquileres pulse:  2" << endl << "Para a�adir un coche pulse:  3" << endl <<
		"Para a�adir un alquiler pulse:  4" << endl << "para salir pulse cualquier otra tecla" << endl;;
}