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
void vueltaAlMen�();

int main()
{

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_crtBreakAlloc = 156;
	//Para windows 11 es el UTF7, para winsows 10 es UTF8
	SetConsoleOutputCP(CP_UTF7);
	ListaCoches listaCoches;
	ListaAlquileres listaAlquileres;
	char answer = '0';
	int* n = new int(5);

	if (!listaCoches.leerModelos() || !listaAlquileres.leerAlquileres(listaCoches))
		cout << "ERROR: Lectura de datos fallida" << endl;
	
	listaAlquileres.ordenarAlquileres();
	while (answer != '5')
	{
		answer = '0';
		ImprimeOpcionesDeMen�();
		cin >> answer;

		if (answer == '1')
		{
			system("cls");
			cout << listaCoches;
			vueltaAlMen�();
		}
		else if (answer == '2')
		{
			system("cls");
			cout << listaAlquileres;
			vueltaAlMen�();
		}
		else if (answer == '3')
		{
			system("cls");
			cout << "Escriba el coche con el siguiente formato: C�digo/precio/marca modelo (separados por un espacio)" << endl;
			Coche c;
			cin >> c;
			listaCoches.insertaCoche(c);
			vueltaAlMen�();
		}
		else if (answer == '4')
		{
			system("cls");
			cout << "Escribe el alquiler con el formato:  c�digo del coche/fecha en formato dd/mm/aa, siendo el a�o 22 2022/d�as de alquiler" << endl;
			Alquiler a;
			cin >> a;
			listaAlquileres.insertaAlquiler(a, listaCoches);
			vueltaAlMen�();
		}

		//por alguna raz�n no va el switch
		/*switch (answer)
		{
			case 1: 
			{
				system("cls");
				cout << listaCoches;
				vueltaAlMen�();
			}
			case 2: 
			{
				system("cls");
				cout << listaAlquileres;
				vueltaAlMen�();
			}
			case 3:
			{
				system("cls");
				cout << "Escriba el coche con el siguiente formato: C�digo/precio/marca/modelo" << endl;
				Coche c;
				cin >> c;
				listaCoches.insertaCoche(c);
				vueltaAlMen�();
			}
			case 4:
			{
				system("cls");
				cout << "Escribe el alquiler con el formato:  c�digo del coche/fecha en formato dd/mm/aa, siendo el a�o 22 2022/d�as de alquiler" << endl;
				Alquiler a;
				cin >> a;
				listaAlquileres.insertaAlquiler(a,listaCoches);
				vueltaAlMen�();
			}
			default :
			{
				answer = 0;
			}*/
		//}
	}
	return 0;
}

void ImprimeOpcionesDeMen�() 
{
	system("cls");
	cout << "Para mostrar los coches pulse:	 1" << endl << "Para mostrar los alquileres pulse:  2" << endl << "Para a�adir un coche pulse:  3" << endl <<
		"Para a�adir un alquiler pulse:  4" << endl << "Para a�adir un alquiler pulse:  5" << endl;;
}

void vueltaAlMen�() 
{
	cout << "pulse cualquier tecla + enter para colver al men�." << endl;
	char c;
	cin >> c;
}