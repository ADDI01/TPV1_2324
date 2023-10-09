#include "Alquiler.h"

Alquiler::Alquiler() : c�digo(0), fecha(Date()), d�as(0), cocheValido(false), coche(0) {};

Alquiler::Alquiler(int c, Date f, int d, bool cV, Coche* co) : c�digo(c), fecha(f), d�as(d),
	cocheValido(cV), coche(co) {}

bool Alquiler::operator<(const Alquiler& a) const {
	return fecha < a.fecha;
}

ostream& operator<<(std::ostream& out, const Alquiler& a)
{
	if (a.getCocheValido())
	{
		out << a.getFecha() << " " << a.getCoche()->getNombre() << " " <<
			a.getDias() << " d�a (s) por " << a.GetCoste()<< " euros" << endl;
	}
	else
	{
		out << a.getFecha() << "  ERROR: Modelo inexistente" << endl;
	}
	return out;
}

istream& operator>>(std::istream& in, Alquiler& a) 
{
	char ch;
	a.cocheValido = true;
	a.coche = nullptr;
	return in >> a.c�digo >> ch >> a.fecha >> ch >> a.d�as;
}
;