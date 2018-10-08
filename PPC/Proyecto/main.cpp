#include "Simulador.h"

using namespace std;

int main() {
	Simulador *sim = new Simulador();
	sim->iniciarMatriz();
	int tics = 0;

	cout << "Duracion de la Simulacion/Cantidad de Tics: " << endl;
	cin >> tics;

	string output;
	for (int x = 0; x < tics; ++x) {
		output += "\n\nTic: " + to_string(x);
		output += sim->actualizarMatriz();
	}

	cout << output << endl;
	ofstream out("C:/Users/ExtremeTech/source/repos/Proyecto/dias.txt");
	out << output;
	out.close();

	int n;
	cin >> n;
	return 0;
}
