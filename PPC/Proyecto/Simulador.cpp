
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
	for (int i = 0; i < tamaño; i++) {
		for (int j = 0; j < tamaño; j++) {
			list<Persona>* lista = new list<Persona>;
			matriz[i][j] = lista;
		}
	}
	// Insercion de las Personas
	for (int k = 0; k < cantidadP; k++) {
		 Persona* p = new Persona();
		 // Inicializar datos de las Persona p
		 randomInt1 = rand() % tamaño;
		 randomInt2 = rand() % tamaño;
		 matriz[randomInt1][randomInt2]->push_front(*p);
	}
}

void actualizarMatriz() {
	list<Persona>::iterator it;
	for (int i = 0; i < tamaño; i++) {
		for (int j = 0; j < tamaño; j++) {
			for (it = matriz[i][j]->begin(); it != matriz[i][j]->end(); ++it) {

				// Random para decidir si 1 o -1
				randomInt1 = rand() % 2;
				if (randomInt1 == 0) {
					randomInt2 = -1;
				}
				else {
					randomInt2 = 1;
				}

				// Random para decidir si se mueve persona por el eje i o eje j
				randomInt1 = rand() % 2;
				if (randomInt1 == 0) {
					matriz[i+randomInt2][j]->push_front(*it);
				}
				else {
					matriz[i][j + randomInt2]->push_front(*it);
				}
			}
		}
	}
}
