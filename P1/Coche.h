#pragma once
#include <iostream>

#ifndef COCHE_H_
#define COCHE_H_
using namespace std;

class Coche
{
protected:
	int c�digo, precio;
	string nombre;
public:
	Coche();
	Coche(int c, int p, string n);
	Coche(const Coche& c);

	int getCodigo() { return c�digo; };
	void setPrecio(int p) { precio = p; };
	int getPrecio() { return precio; };
	string getNombre() { return nombre; };
	friend std::ostream& operator<<(std::ostream& out, const Coche& c);
};
#endif

