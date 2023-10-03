#include "Alquiler.h"

Alquiler::Alquiler() : código(0), fecha(Date()), días(0), cocheValido(false), coche(0) {};
Alquiler::Alquiler(int c, Date f, int d, bool cV, Coche* co) : código(c), fecha(f), días(d),
	cocheValido(cV), coche(co) {}