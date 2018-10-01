#pragma once
#ifndef PPC_GoL_S // Programación Paralela y Concurrente - Conway's Game of Life
#define PPC_GoL_S
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <chrono> // para medir el tiempo de ejecución
#include <omp.h>
#include <list>
#include <time.h>
#include <iostream>
#include <vector>
#include "Persona.h"

using namespace std;

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
	int probaInfectada;
	int tamaño;
	int tics;

	int tInfectadas;
	int tSusceptibles;
	int tMuertas;
	int tRecuperadas;
	vector <vector<list<Persona>>> matriz;
};

#endif
