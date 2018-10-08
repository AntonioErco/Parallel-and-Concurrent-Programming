#include "Persona.h"

Persona::Persona() {
	tiempoInfect = 0;
}

Persona::~Persona() {

}

void Persona::setEstado(Estado est) {
	estado = est;
}

void Persona::resetTiempo() {
	tiempoInfect = 0;
}

void Persona::addTiempo() {
	++tiempoInfect;
}

Estado Persona::getEstado() {
	return estado;
}

int Persona::getTiempoInfectado() {
	return tiempoInfect;
}
