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

	int getCodigo() { return código; };
	int getDias() { return días; };
	Date getFecha() { return fecha; };
	bool getCocheValido() { return cocheValido; };
	void setCocheValido(bool c) { cocheValido = c; };
	Coche* getCoche() { return coche; };
	void setCoche(Coche* c) { coche = c; };
};

#endif
