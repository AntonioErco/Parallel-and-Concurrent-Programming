#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <chrono> // para medir el tiempo de ejecución
#include <omp.h>
#include <list>
#include <time.h>
#include "Persona.h"
using namespace std;

void iniciarMatriz();
void actualizarMatriz();
int personasInfectadas(int i, int j);
void actualizarEstado(list<Persona>::iterator it,int inf);
void moverPersonas(int i, int j, list<Persona>::iterator it);

int tamaño = 10;
int cantidadP = 100;
int randomInt1 = 0;
int randomInt2 = 0;
int tics = 0;
list<Persona>* matriz[10][10];



int main() {
	srand(time(NULL));
	iniciarMatriz();
	/*
	while (tics <= 1000000) {
	actualizarMatriz();
	tics++;
	}
	*/
}

void iniciarMatriz() {
	// Creacion de listas
	for (int i = 0; i < tamaño; ++i) {
		for (int j = 0; j < tamaño; ++j) {
			list<Persona>* lista = new list<Persona>;
			matriz[i][j] = lista;
		}
	}
	// Insercion de las Personas
	for (int k = 0; k < cantidadP; ++k) {
		Persona* p = new Persona();
		// Inicializar datos de las Persona p
		randomInt1 = rand() % tamaño;
		randomInt2 = rand() % tamaño;
		matriz[randomInt1][randomInt2]->push_front(*p);
	}
}

void actualizarMatriz() {
	list<Persona>::iterator it;
	int inf;
	for (int i = 0; i < tamaño; ++i) {
		for (int j = 0; j < tamaño; ++j) {
			inf = personasInfectadas(i, j);
			for (it = matriz[i][j]->begin(); it != matriz[i][j]->end(); ++it) {
				actualizarEstado(it,inf);
				moverPersonas(i, j, it);
			}
		}
	}
}

int personasInfectadas(int i, int j) {
	list<Persona>::iterator it;
	Estado estado;
	int nInfectadas = 0;
	int nSusceptibles = 0;
	int nMuertas = 0;
	int nRecuperadas = 0;
	for (it = matriz[i][j]->begin(); it != matriz[i][j]->end(); ++it) {
		estado = (*it).getEstado();
		switch (estado) {
			case Infectada: {
				nInfectadas++;
			}
			case Susceptibles: {
				nSusceptibles++;
			}
			case Muerta: {
				nMuertas++;
			}
			case Recuperada: {
				nRecuperadas;
			}
		}
	}
	return nInfectadas;
}

void actualizarEstado(list<Persona>::iterator it,int inf) {
	if ((*it).getActivo() == true) {
		
	}
	else{
	}
}

void moverPersonas(int i, int j, list<Persona>::iterator it) {
	int indice;
	int random;
	do {
		random = rand() % 3;
		switch (random) {

			case 0: {
				indice = i + 1;
				break;
			}
			case 1: {
				indice = i - 1;
				break;
			}
			case 2: {
				indice = j + 1;
				break;
			}
			case 3: {
				indice = j - 1;
				break;
			}
		}
	} while ((indice < 0) || (indice > tamaño));
	if (random< 2) {
		matriz[indice][j]->push_front(*it);
	}
	else {
		matriz[i][indice]->push_front(*it);
	}
}
