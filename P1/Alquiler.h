#pragma once
#include <iostream>
#include "Coche.h"
#include "Date.h"

#ifndef ALQUILER_H_
#define ALQUILER_H_
using namespace std;

class Alquiler
{
private:
	int código, días;
	Date fecha;
	bool cocheValido = true;
	Coche* coche;

public:
	Alquiler();
	Alquiler(int c, Date f, int d, bool cV, Coche* co);

	bool operator<(const Alquiler& a) const;

	int getCodigo() const { return código; };
	int getDias() const { return días; };
	Date getFecha() const { return fecha; };
	bool getCocheValido() const { return cocheValido; };
	void setCocheValido(bool c) { cocheValido = c; };
	Coche* getCoche() const { return coche; };
	void setCoche(Coche* c) { coche = c; };

	friend std::ostream& operator<<(std::ostream& out, const Alquiler& a);
};

#endif
