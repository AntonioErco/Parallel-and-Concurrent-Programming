#include <chrono>
#include "Simulador.h"

using namespace std;

int main() {
	using namespace std::chrono;

	int x = 0;
	int hilos = 0;
	cout << "Cantidad de Hilos: " << endl;
	cin >> hilos;

	while (x == 0) {
		Simulador *sim = new Simulador();

		steady_clock::time_point t1 = steady_clock::now();

		sim->iniciarMatriz();

		sim->cantidadHilos(hilos);
		string output = sim->actualizarMatriz();

		cout << output << endl;
		ofstream out("C:/Users/ExtremeTech/source/repos/Proyecto/dias.txt");
		out << output;
		out.close();

		steady_clock::time_point t2 = steady_clock::now();
		duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
		std::cout << "Duracion " << time_span.count() << " segundos.";
		cout << "\n 0 para continuar" << endl;
		cin >> x;
	}
	return 0;
}
