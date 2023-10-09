#include "Alquiler.h"

Alquiler::Alquiler() : código(0), fecha(Date()), días(0), cocheValido(false), coche(0) {};

Alquiler::Alquiler(int c, Date f, int d, bool cV, Coche* co) : código(c), fecha(f), días(d),
	cocheValido(cV), coche(co) {}

bool Alquiler::operator<(const Alquiler& a) const {
	return fecha < a.fecha;
}

ostream& operator<<(std::ostream& out, const Alquiler& a)
{
	if (a.getCocheValido())
	{
		out << a.getFecha() << " " << a.getCoche()->getNombre() << " " <<
			a.getDias() << " día (s) por " << a.GetCoste()<< " euros" << endl;
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
	return in >> a.código >> ch >> a.fecha >> ch >> a.días;
}
;