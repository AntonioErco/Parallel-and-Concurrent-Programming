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
	string actualizarMatriz();
	int personasInfectadas(int i, int j);
	void actualizarEstado(int i, int j, int y, int inf);
	void moverPersonas(int i, int j, int y);
	void cantidadHilosYTics(int n,int t);
	void init();

private:

	int cantidadP;
	int potenciaVirus;
	int probaRecu;
	int ticsMuerte;
	int cantInfectada;
	int tamaño;
	int tics;

	int tInfectadas;
	int tSusceptibles;
	int tMuertas;
	int tRecuperadas;

	int hilos;

	vector <vector< vector <Persona> > > matriz;
};

#endif
