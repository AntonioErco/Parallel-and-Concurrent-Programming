#include "Simulador.h"
#include "Persona.h"

using namespace std;

Simulador::Simulador() {
	this->init();
}

Simulador::~Simulador() {

}

void Simulador::init() {

	cout << "Cantidad de Personas: ";
	cin >> cantidadP;

	cout << "Potencia Infecciosa de Virus [0-10]: ";
	cin >> potenciaVirus;

	cout << "Probabilidad de Recuperación [0-10]: ";
	cin >> probaRecu;

	cout << "Probabilidad de Muerte [0-10]: ";
	cin >> probaMuerte;

	cout << "Porcentaje de Personas Originalmente Infectadas: ";
	cin >> probaInfectada;
	probaInfectada = (cantidadP / 100)*probaInfectada;

	cout << "Tamaño del Espacio Bidimensional: " << endl;

	cout << "1) 100x100 \n2) 500x500 \n3) 1000x1000" << endl;
	cin >> tamaño;

	if (tamaño == 1) {
		tamaño = 100;
	}
	else if (tamaño == 2) {
		tamaño = 500;
	}
	else {
		tamaño = 1000;
	}

}

void Simulador::iniciarMatriz() {
	int randomInt1;
	int randomInt2;

	matriz.resize(tamaño);
	for (int i = 0; i < tamaño; ++i) {
		matriz[i].resize(tamaño);
	}

	int cn = 0;
	// Insercion de las Personas
	for (int k = 0; k < cantidadP; ++k) {
		Persona* p = new Persona();
		randomInt1 = rand() % 10;
		if (randomInt1 < potenciaVirus) {
			p->setEstado(Infectada);
		}
		else {
			p->setEstado(Susceptible);
		}
		// Inicializar datos de las Persona p
		randomInt1 = rand() % tamaño;
		randomInt2 = rand() % tamaño;
		matriz[randomInt1][randomInt2].push_back(*p);
	}

	/*
	for (int l = 0; l < tamaño-1; ++l) {
		for (int g = 0; g < tamaño; ++g) {
			cout << matriz[l][g].size() << " l " << l << " g " << g <<  endl;
		}
	}*/

}


void Simulador::actualizarMatriz() {
	tMuertas = 0;
	tRecuperadas = 0;
	tInfectadas = 0;
	tSusceptibles = 0;
	list<Persona>::iterator it;
	int infectadas;
	for (int i = 0; i < tamaño; ++i) {
		for (int j = 0; j < tamaño; ++j) {
			infectadas = personasInfectadas(i, j);
			for (it = matriz[i][j].begin(); it != matriz[i][j].end(); ++it) {
				actualizarEstado(it, infectadas);
				//moverPersonas(i, j, it);
			}
		}
	}
	cout << "Muertas: " << tMuertas << endl;
	cout << "Recuperadas: " << tRecuperadas << endl;
	cout << "Infectadas: " << tInfectadas << endl;
	cout << "Susceptibles: " << tSusceptibles << endl;
}


int Simulador::personasInfectadas(int i, int j) {
	list<Persona>::iterator it;
	Estado estado;
	int nInfectadas = 0;
	int nSusceptibles = 0;
	int nMuertas = 0;
	int nRecuperadas = 0;
	for (it = matriz[i][j].begin(); it != matriz[i][j].end(); ++it) {
		estado = (*it).getEstado();
		switch (estado) {
			case Infectada: {
				nInfectadas++;
				break;
			}
			case Susceptible: {
				nSusceptibles++;
				break;
			}
			case Muerta: {
				nMuertas++;
				break;
			}
			case Recuperada: {
				nRecuperadas;
				break;
			}
		}
	}
	tRecuperadas = tRecuperadas + nRecuperadas;
	tMuertas = tMuertas + nMuertas;
	tSusceptibles = tSusceptibles + nSusceptibles;
	tInfectadas = tInfectadas + nInfectadas;
	return nInfectadas;
}

void Simulador::actualizarEstado(list<Persona>::iterator it, int inf) {
	int randomInt =  rand() % 10;
	Estado est = (*it).getEstado();
	if ((*it).getActivo() == true) {

		switch (est) {
			case Infectada: {
				if (randomInt < probaRecu) {
					(*it).setEstado(Recuperada);
				}
				else if (randomInt > (9 - probaMuerte)) {
					(*it).setEstado(Muerta);
				}
				break;
			}
			case Susceptible: {
				if (randomInt < probaInfectada*inf) {
					(*it).setEstado(Infectada);
				}
				break;
			}
		}
	}

	else {
		(*it).setActivo(true);
	}
}

void Simulador::moverPersonas(int i, int j, list<Persona>::iterator it) {
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
	} while ((indice < 0) || (indice >= tamaño));
	if (random < 2) {
		matriz[indice][j].push_front(*it);
	}
	else {
		matriz[i][indice].push_front(*it);
	}
}
