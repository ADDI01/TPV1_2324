#include "Coche.h"

Coche::Coche() : c�digo(0), precio(0), nombre("") {};

Coche::Coche(int c, int p, string n)
	: c�digo(c), precio(p), nombre(n) { }

Coche::Coche(const Coche& c) : c�digo(c.c�digo), precio(c.precio), nombre(c.nombre) {}
