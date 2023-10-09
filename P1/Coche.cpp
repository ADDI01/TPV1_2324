#include "Coche.h"
using namespace std;

Coche::Coche() : código(0), precio(0), nombre("") {};

Coche::Coche(int c, int p, string n)
	: código(c), precio(p), nombre(n) { }

Coche::Coche(const Coche& c) : código(c.código), precio(c.precio), nombre(c.nombre) {}

Coche Coche:: operator=(const Coche& a) const 
{
	Coche c(a.código, a.precio, a.nombre);
	return c;
}

ostream& operator<<(std::ostream& out, const Coche& c)
{
	return out << "Código: " << c.código << "	Precio: " << c.precio << "	Nombre del coche todo junto: " << c.nombre << endl;;
}

istream& operator>>(std::istream& in, Coche& c) 
{
	char ch; // para saltos de línea
	return in >> c.código >> ch >> c.precio >> ch >> c.nombre;

}
