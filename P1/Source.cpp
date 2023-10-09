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
void vueltaAlMenú();

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
		ImprimeOpcionesDeMenú();
		cin >> answer;

		if (answer == '1')
		{
			system("cls");
			cout << listaCoches;
			vueltaAlMenú();
		}
		else if (answer == '2')
		{
			system("cls");
			cout << listaAlquileres;
			vueltaAlMenú();
		}
		else if (answer == '3')
		{
			system("cls");
			cout << "Escriba el coche con el siguiente formato: Código/precio/marca modelo (separados por un espacio)" << endl;
			Coche c;
			cin >> c;
			listaCoches.insertaCoche(c);
			vueltaAlMenú();
		}
		else if (answer == '4')
		{
			system("cls");
			cout << "Escribe el alquiler con el formato:  código del coche/fecha en formato dd/mm/aa, siendo el año 22 2022/días de alquiler" << endl;
			Alquiler a;
			cin >> a;
			listaAlquileres.insertaAlquiler(a, listaCoches);
			vueltaAlMenú();
		}

		//por alguna razón no va el switch
		/*switch (answer)
		{
			case 1: 
			{
				system("cls");
				cout << listaCoches;
				vueltaAlMenú();
			}
			case 2: 
			{
				system("cls");
				cout << listaAlquileres;
				vueltaAlMenú();
			}
			case 3:
			{
				system("cls");
				cout << "Escriba el coche con el siguiente formato: Código/precio/marca/modelo" << endl;
				Coche c;
				cin >> c;
				listaCoches.insertaCoche(c);
				vueltaAlMenú();
			}
			case 4:
			{
				system("cls");
				cout << "Escribe el alquiler con el formato:  código del coche/fecha en formato dd/mm/aa, siendo el año 22 2022/días de alquiler" << endl;
				Alquiler a;
				cin >> a;
				listaAlquileres.insertaAlquiler(a,listaCoches);
				vueltaAlMenú();
			}
			default :
			{
				answer = 0;
			}*/
		//}
	}
	return 0;
}

void ImprimeOpcionesDeMenú() 
{
	system("cls");
	cout << "Para mostrar los coches pulse:	 1" << endl << "Para mostrar los alquileres pulse:  2" << endl << "Para añadir un coche pulse:  3" << endl <<
		"Para añadir un alquiler pulse:  4" << endl << "Para añadir un alquiler pulse:  5" << endl;;
}

void vueltaAlMenú() 
{
	cout << "pulse cualquier tecla + enter para colver al menú." << endl;
	char c;
	cin >> c;
}