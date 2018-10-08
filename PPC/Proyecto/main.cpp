#include "Simulador.h"

using namespace std;

int main() {

	Simulador *sim = new Simulador();
	sim->iniciarMatriz();
	int tics = 0;
	int hilos = 0;

	cout << "Cantidad de Hilos: " << endl;
	cin >> hilos;

	sim->cantidadHilos(hilos);
	string output = sim->actualizarMatriz();

	cout << output << endl;
	ofstream out("C:/Users/ExtremeTech/source/repos/Proyecto/dias.txt");
	out << output;
	out.close();

	int n;
	cin >> n;
	return 0;
}
