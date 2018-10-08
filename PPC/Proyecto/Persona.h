#ifndef PPC_GoL_P // Programación Paralela y Concurrente - Conway's Game of Life
#define PPC_GoL_P
#include <iostream>

using namespace std;

enum Estado { Susceptible, Infectada, Muerta, Recuperada };

class Persona {

public:
	Persona();
	~Persona();

	void setEstado(Estado est);
	void setActivo(bool act);
	void resetTiempo();
	void addTiempo();
	Estado getEstado();
	bool getActivo();
	int getTiempoInfectado();



private:

	Estado estado;
	bool activo;
	int tiempoInfect;
};

#endif
