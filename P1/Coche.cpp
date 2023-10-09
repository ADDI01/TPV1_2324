#include "Coche.h"

Coche::Coche() : código(0), precio(0), nombre("") {};

Coche::Coche(int c, int p, string n)
	: código(c), precio(p), nombre(n) { }

Coche::Coche(const Coche& c) : código(c.código), precio(c.precio), nombre(c.nombre) {}

ostream& operator<<(std::ostream& out, const Coche& c)
{
	out << "Código: " << c.código << "	Precio: " << c.precio << "	Nombre del coche: " << c.nombre<< endl;
	return out;
}
