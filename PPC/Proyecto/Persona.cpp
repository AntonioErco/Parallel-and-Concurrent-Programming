
#include "Persona.h"

Persona::Persona() {

}

Persona::~Persona() {

}

void Persona::setEstado(Estado est) {
	estado = est;
}

void Persona::setActivo(bool act) {
	activo = act;
}

Estado Persona::getEstado() {
	return estado;
}

bool Persona::getActivo() {
	return activo;
}
