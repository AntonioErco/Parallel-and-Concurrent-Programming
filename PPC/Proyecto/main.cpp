#include "Simulador.h"

using namespace std;

int main() {
	Simulador *sim = new Simulador();
	sim->iniciarMatriz();
	int tics = 0;
	int hilos = 0;

	cout << "Duracion de la Simulacion/Cantidad de Tics: " << endl;
	cin >> tics;
	cout << "Cantidad de Hilos: " << endl;
	cin >> hilos;

	sim->cantidadHilosYTics(hilos,tics);
	string output = sim->actualizarMatriz();

	cout << output << endl;
	ofstream out("C:/Users/ExtremeTech/source/repos/Proyecto/dias.txt");
	out << output;
	out.close();

	int n;
	cin >> n;
	return 0;
}
