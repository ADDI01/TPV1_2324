#pragma once
#include <iostream>

#ifndef COCHE_H_
#define COCHE_H_
using namespace std;

class Coche
{
protected:
	int código, precio;
	string nombre;
public:
	Coche();
	Coche(int c, int p, string n);
	Coche(const Coche& c);

	int getCodigo() const{ return código; };
	void setPrecio(int p) { precio = p; };
	int getPrecio() { return precio; };
	string getNombre() { return nombre; };
	Coche operator=(const Coche& a) const;
	friend std::ostream& operator<<(std::ostream& out, const Coche& c);
	friend std::istream& operator>>(std::istream& in, Coche& c);
};
#endif

