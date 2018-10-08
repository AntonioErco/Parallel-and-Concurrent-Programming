#include "Simulador.h"
#include "Persona.h"

using namespace std;

Simulador::Simulador() {
	this->init();
}

Simulador::~Simulador() {

}

void Simulador::init() {

	cout << "Tics para Muerte: ";
	cin >> ticsMuerte;

	cout << "Potencia Infecciosa de Virus [0-100]: ";
	cin >> potenciaVirus;

	cout << "Probabilidad de Recuperacion [0-100]: ";
	cin >> probaRecu;

	cout << "Cantidad de Personas: ";
	cin >> cantidadP;

	cout << "Porcentaje de Personas Originalmente Infectadas [0 - 100]: ";
	cin >> cantInfectada;
	cantInfectada = (cantidadP / cantInfectada);

	cout << "Tamaño del Espacio Bidimensional: " << endl;

	cout << "1) 100x100 \n2) 500x500 \n3) 1000x1000 \n4) 35x35" << endl;
	cin >> tamano;

	if (tamano == 1) {
		tamano = 100;
	}
	else if (tamano == 2) {
		tamano = 500;
	}
	else if (tamano == 3) {
		tamano = 1000;
	}
	else {
		tamano = 35;
	}
}

void Simulador::iniciarMatriz() {
	int randomInt1;
	int randomInt2;

	matriz.resize(tamano);
	for (int i = 0; i < tamano; ++i) {
		matriz[i].resize(tamano);
	}

	// Insercion de las Personas
	int pInfectadas = cantInfectada;
	int pSaludables = cantidadP - pInfectadas;

	for (int k = 0; k < pSaludables; ++k) {
		Persona* p = new Persona();
		// Inicializar datos de las Persona p
		p->setEstado(Susceptible);
		// Escoger Posición
		randomInt1 = rand() % tamano;
		randomInt2 = rand() % tamano;
		matriz[randomInt1][randomInt2].push_back(*p);
		tSusceptibles++;
	}
	for (int k = 0; k < pInfectadas; ++k) {
		Persona* p = new Persona();
		// Inicializar datos de las Persona p
		p->setEstado(Infectada);
		// Escoger Posición
		randomInt1 = rand() % tamano;
		randomInt2 = rand() % tamano;
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
	int tics = 0;

	while (tInfectadas != 0) {

		tMuertas = 0;
		tRecuperadas = 0;
		tInfectadas = 0;
		tSusceptibles = 0;
		int infectadas = 0;

		// Recorrido actualizando la posicion de las personas
#pragma omp parallel for num_threads(hilos)
		for (int i = 0; i < tamano; ++i) {
			for (int j = 0; j < tamano; ++j) {
				for (int y = 0; y < matriz[i][j].size(); ++y) {
					moverPersonas(i, j, y);
				}
			}
		}

		//ragma omp barrier

		// Recorrrido actualizando el estado de las personas
#pragma omp parallel for num_threads(hilos)
		for (int i = 0; i < tamano; ++i) {
			for (int j = 0; j < tamano; ++j) {
				infectadas = personasInfectadas(i, j);
				for (int y = 0; y < matriz[i][j].size(); ++y) {
					actualizarEstado(i, j, y, infectadas);
				}
			}
		}

		output += "\nTic#: " + to_string(tics);
		output += "\nSusceptibles: " + to_string(tSusceptibles);
		output += "\nInfectadas: " + to_string(tInfectadas);
		output += "\nRecuperadas: " + to_string(tRecuperadas);
		output += "\nMuertas: " + to_string(tMuertas);
		++tics;
	}
	output += "\n Tics totales: " + to_string(tics);
	return output;
}

// Cuenta el numero de personas infectadas en la misma posicion
int Simulador::personasInfectadas(int i, int j) {
	list<Persona>::iterator it;
	Estado estado;
	int nInfectadas = 0;
	for (int y = 0; y < matriz[i][j].size(); ++y) {
		if (matriz[i][j][y].getEstado() == Infectada) {
			nInfectadas++;
		}
	}
	return nInfectadas;
}

// Actualiza el estado de la persona
void Simulador::actualizarEstado(int i, int j, int y, int inf) {
	Estado est = matriz[i][j][y].getEstado();
	switch (est) {
	case Infectada: {
		if (matriz[i][j][y].getTiempoInfectado() >= ticsMuerte) {
			random_device rd;
			int randomInt1 = rd() % 100;
			if (randomInt1 < probaRecu) {
				matriz[i][j][y].setEstado(Recuperada);
				matriz[i][j][y].resetTiempo();
				tRecuperadas++;
			}
			else {
				matriz[i][j][y].setEstado(Muerta);
				tMuertas++;
			}
		}
		else {
			matriz[i][j][y].addTiempo();
			tInfectadas++;
		}
		break;
	}
	case Susceptible: {
		random_device rd;
		int randomInt2 = rd() % 100;
		bool infectada = false;
		for (int g = 0; g < inf; g++) {
			if (randomInt2 < cantInfectada) {
				infectada = true;
			}
		}
		if (infectada) {
			matriz[i][j][y].setEstado(Infectada);
			tInfectadas++;

		}else {
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
	random_device rd;
	Persona p = matriz[i][j][y];
	random = rd() % 4;
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
	if (indice < 0) {
		indice = tamano - 1;
	}
	else if (indice >= tamano) {
		indice = 0;
	}
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
