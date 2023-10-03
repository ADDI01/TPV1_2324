#include "Alquiler.h"

Alquiler::Alquiler() : c�digo(0), fecha(Date()), d�as(0), cocheValido(false), coche(0) {};
Alquiler::Alquiler(int c, Date f, int d, bool cV, Coche* co) : c�digo(c), fecha(f), d�as(d),
	cocheValido(cV), coche(co) {}