#include "Simulador.h"

using namespace std;

int main() {

	Simulador *sim = new Simulador();
	sim->iniciarMatriz();
	int tics = 0;

	cout << "Duración de la Simulación/Cantidad de Tics: " << endl;
	cin >> tics;
	for (int x = 0; x < tics; ++x) {
		sim->actualizarMatriz();
		sim->actualizarMatriz();
	}

	int n;
	cin >> n;
	return 0;
}
