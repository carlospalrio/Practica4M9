#include <iostream>
#include <thread>
#include <mutex>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;

bool ganador = false;  // Variable para indicar si hay un ganador
const int meta = 50;   // Distancia de la meta
mutex mtx;             // Mutex para proteger el acceso a la variable 'ganador'

// Función para simular el movimiento de un animal en la carrera
void correr(const string& nombre, const string& simbolo) {
    int distancia = 0;
    srand(static_cast<unsigned>(time(0)) + distancia); // Semilla aleatoria para cada hilo

    while (distancia < meta && !ganador) {
        int avance = rand() % 5 + 1;  // Genera un número aleatorio entre 1 y 5
        this_thread::sleep_for(chrono::milliseconds(100 * avance)); // Pausa para simular movimiento
        distancia += avance; // Incrementa la distancia

        {
            lock_guard<mutex> lock(mtx);  // Bloqueo seguro de mutex
            cout << nombre << ": " << string(distancia, '.') << simbolo << endl;
        }

        // Comprobación de ganador
        if (distancia >= meta) {
            lock_guard<mutex> lock(mtx);  // Bloqueo seguro de mutex
            if (!ganador) {
                ganador = true;
                cout << nombre << " ha ganado la carrera!" << endl;
            }
        }
    }
}

int main() {
    // Crear hilos para cada animal
    thread t1(correr, "Jamon", "🐇");
    thread t2(correr, "Queso", "🐢");
    thread t3(correr, "Caballo", "🐕");

    // Esperar a que todos los hilos terminen
    t1.join();
    t2.join();
    t3.join();

    return 0;
}
