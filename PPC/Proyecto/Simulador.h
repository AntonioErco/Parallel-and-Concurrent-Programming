#pragma once
#ifndef PPC_GoL_S // Programación Paralela y Concurrente - Conway's Game of Life
#define PPC_GoL_S

#include <iostream>
using namespace std;

#include "Persona.h"

class Simulador {

public:
    Simulador();
    ~Simulador();

	void iniciarMatriz();
	void actualizarMatriz();
	int personasInfectadas(int i, int j);
	void actualizarEstado(list<Persona>::iterator it, int inf);
	void moverPersonas(int i, int j, list<Persona>::iterator it);
    void init();

private:
    int cantidadP;
    int potenciaVirus;
    int probaRecu;
    int probaMuerte;
    int ogInfectada;
    int tamaño;
    int tics;
	int randomInt1;
	int randomInt2;
	list<Persona>* matriz[10][10];

};

#endif
