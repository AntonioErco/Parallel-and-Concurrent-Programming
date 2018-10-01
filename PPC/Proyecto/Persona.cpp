#include "Persona.h"

Persona::Persona() {
	activo = true;
	tiempoInfect = 0;
}

Persona::~Persona() {

}

void Persona::setEstado(Estado est) {
	estado = est;
}

void Persona::setActivo(bool act) {
	activo = act;
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

bool Persona::getActivo() {
	return activo;
}

int Persona::getTiempoInfectado() {
	return tiempoInfect;
}
