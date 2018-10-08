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

	cout << "Probabilidad de Recuperacion [0-10]: ";
	cin >> probaRecu;

	cout << "Tics para Muerte: ";
	cin >> ticsMuerte;

	cout << "Porcentaje de Personas Originalmente Infectadas: ";
	cin >> cantInfectada;
	cantInfectada = (cantidadP / 100)*cantInfectada;

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

	// Insercion de las Personas
	int pInfectadas = cantInfectada * 10;
	int pSaludables = cantidadP - pInfectadas;

	for (int k = 0; k < pSaludables; ++k) {
		Persona* p = new Persona();
		// Inicializar datos de las Persona p
		p->setEstado(Susceptible);
		// Escoger Posición
		randomInt1 = rand() % tamaño;
		randomInt2 = rand() % tamaño;
		matriz[randomInt1][randomInt2].push_back(*p);
		tSusceptibles++;
	}
	for (int k = 0; k < pInfectadas; ++k) {
		Persona* p = new Persona();
		// Inicializar datos de las Persona p
		p->setEstado(Infectada);
		// Escoger Posición
		randomInt1 = rand() % tamaño;
		randomInt2 = rand() % tamaño;
		matriz[randomInt1][randomInt2].push_back(*p);
		tInfectadas++;
	}

	cout << "Muertas: " << tMuertas << endl;
	cout << "Recuperadas: " << tRecuperadas << endl;
	cout << "Infectadas: " << tInfectadas << endl;
	cout << "Susceptibles: " << tSusceptibles << endl;
}


string Simulador::actualizarMatriz() {
	string output;
	tMuertas = 0;
	tRecuperadas = 0;
	tInfectadas = 0;
	tSusceptibles = 0;
	int infectadas = 0;

	// Recorrido actualizando la posicion de las personas
#pragma omp parallel for num_threads(hilos)
	{
		for (int i = 0; i < tamaño; ++i) {
			for (int j = 0; j < tamaño; ++j) {
				for (int y = 0; y < matriz[i][j].size(); ++y) {
					moverPersonas(i, j, y);
				}
			}
		}

#pragma omp barrier
	// Recorrrido actualizando el estado de las personas
		for (int i = 0; i < tamaño; ++i) {
			for (int j = 0; j < tamaño; ++j) {
				infectadas = personasInfectadas(i, j);
				for (int y = 0; y < matriz[i][j].size(); ++y) {
					actualizarEstado(i, j, y, infectadas);
				}
			}
		}
	}

	output += "\nSusceptibles: " + to_string(tSusceptibles);
	output += "\nInfectadas: " + to_string(tInfectadas);
	output += "\nRecuperadas: " + to_string(tRecuperadas);
	output += "\nMuertas: " + to_string(tMuertas);
	return output;
}

// Cuenta el numero de personas infectadas en la misma posicion
int Simulador::personasInfectadas(int i, int j) {
	list<Persona>::iterator it;
	Estado estado;
	int nInfectadas = 0;
	for (int y = 0; y < matriz[i][j].size(); ++y) {
		if (matriz[i][j][y].getActivo()&&(matriz[i][j][y].getEstado() == Infectada)){
			nInfectadas++;
		}
	}
	return nInfectadas;
}

// Actualiza el estado de la persona
void Simulador::actualizarEstado(int i, int j, int y, int inf) {
	int randomInt = rand() % 10;
	Estado est = matriz[i][j][y].getEstado();

	switch (est) {
	case Infectada: {
		if (randomInt < probaRecu) {

			matriz[i][j][y].setEstado(Recuperada);
			matriz[i][j][y].resetTiempo();
			tRecuperadas++;
		}
		else if(matriz[i][j][y].getTiempoInfectado() >= ticsMuerte){
			matriz[i][j][y].setEstado(Muerta);
			tMuertas++;
		}
		else {
			matriz[i][j][y].addTiempo();
			tInfectadas++;
		}
		break;
	}
	case Susceptible: {
		if (randomInt < cantInfectada*inf) {
			matriz[i][j][y].setEstado(Infectada);
			tInfectadas++;
		}
		else {
			tSusceptibles++;
		}
		break;
	}
	case Muerta: {
		tMuertas++;
		break;
	}
	case Recuperada: {
		tRecuperadas++;
		break;
	}
	}
}

// Cambia de posicion a la persona
void Simulador::moverPersonas(int i, int j, int y) {
	int indice;
	int random;
	Persona p = matriz[i][j][y];
	do {
		random = rand() % 4;
		switch (random) {

		case 0: {
			indice = i + 1;
			//p.setActivo(false);
			break;
		}
		case 1: {
			indice = i - 1;
			//p.setActivo(true);
			break;
		}
		case 2: {
			indice = j + 1;
			//p.setActivo(false);
			break;
		}
		case 3: {
			indice = j - 1;
			//p.setActivo(true);
			break;
		}
		}
	} while ((indice < 0) || (indice >= tamaño));
	matriz[i][j].erase(matriz[i][j].begin() + y);
	if (random < 2) {
		matriz[indice][j].push_back(p);
	}
	else {
		matriz[i][indice].push_back(p);
	}
}

void Simulador::cantidadHilos(int n) {
		hilos = n;
}
