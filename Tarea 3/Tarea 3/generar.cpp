#include <iostream>
#include <fstream>
#include <random>
#include <chrono>
using namespace std;

int main() {
    const long long TOTAL_NUMEROS = 1000000;  // 1 millón
    const string ARCHIVO_SALIDA = "datos_1a20_grande.txt";
    int max;
    cout << " De 1 a ";
    cin >> max;
    cout << endl;
    
    // Semilla basada en tiempo
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    mt19937 generador(seed);
    uniform_int_distribution<int> distribucion(1, max);
    
    cout << "Generando " << TOTAL_NUMEROS << " números aleatorios 1-max..." << endl;
    
    ofstream archivo(ARCHIVO_SALIDA);
    if (!archivo) {
        cerr << "Error al crear archivo" << endl;
        return 1;
    }
    
    // Generar números
    for (long long i = 0; i < TOTAL_NUMEROS; i++) {
        archivo << distribucion(generador);
        archivo << endl;
        

    }
    
    archivo.close();
    cout << "Archivo generado: " << ARCHIVO_SALIDA << endl;
    cout << "Tamaño aproximado: " << (TOTAL_NUMEROS * 2 / 1024 / 1024) << " MB" << endl;
    
    return 0;
}