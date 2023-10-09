#include "Coche.h"
using namespace std;

Coche::Coche() : c�digo(0), precio(0), nombre("") {};

Coche::Coche(int c, int p, string n)
	: c�digo(c), precio(p), nombre(n) { }

Coche::Coche(const Coche& c) : c�digo(c.c�digo), precio(c.precio), nombre(c.nombre) {}

Coche Coche:: operator=(const Coche& a) const 
{
	Coche c(a.c�digo, a.precio, a.nombre);
	return c;
}

ostream& operator<<(std::ostream& out, const Coche& c)
{
	return out << "C�digo: " << c.c�digo << "	Precio: " << c.precio << "	Nombre del coche todo junto: " << c.nombre << endl;;
}

istream& operator>>(std::istream& in, Coche& c) 
{
	char ch; // para saltos de l�nea
	return in >> c.c�digo >> ch >> c.precio >> ch >> c.nombre;

}
