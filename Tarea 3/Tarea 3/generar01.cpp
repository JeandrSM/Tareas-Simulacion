#include <iostream>
#include <fstream>
#include <random>
#include <chrono>
#include <iomanip>
using namespace std;

int main() {
    const long long TOTAL_NUMEROS = 1000000;  // 1 millón
    const string ARCHIVO_SALIDA = "datos_decimales.txt";
    
    int precision;
    cout << "Precision de decimales (1-15): ";
    cin >> precision;
    cout << endl;
    
    // Semilla basada en tiempo
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    mt19937 generador(seed);
    uniform_real_distribution<double> distribucion(0.0, 1.0);
    
    cout << "Generando " << TOTAL_NUMEROS << " números aleatorios entre [0,1)..." << endl;
    cout << "Precisión: " << precision << " decimales" << endl;
    
    ofstream archivo(ARCHIVO_SALIDA);
    if (!archivo) {
        cerr << "Error al crear archivo" << endl;
        return 1;
    }
    
    // Configurar precisión para el archivo
    archivo << fixed << setprecision(precision);
    
    // Generar números
    for (long long i = 0; i < TOTAL_NUMEROS; i++) {
        archivo << distribucion(generador);
        


        archivo << endl;
        
        
    }
    
    archivo.close();
    

    return 0;
}