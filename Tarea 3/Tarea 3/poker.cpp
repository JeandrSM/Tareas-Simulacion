#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>
using namespace std;


enum Clase {
    DIFERENTES = 0,
    UN_PAR = 1,
    DOS_PARES = 2,
    TERCIA = 3,
    FULL = 4,
    POKER = 5,
    QUINTILLA = 6
};

void pokerDecimal(){
    ifstream archivo("num_0a1.txt");   //datos_decimales   /libro
    if (!archivo) {
        cerr << "Error al abrir el archivo\n";
        return;
    }

    vector<double> datos;
    double numero;
    
    while (archivo >> numero) {
        datos.push_back(numero);
    }
    archivo.close();
    int clases[7] = {0};
    int total_manos = datos.size();

    for (double num : datos) {

        vector<int> digitos_precisos(5);
        stringstream ss;
        ss << fixed << setprecision(10) << num;
        string num_str = ss.str();
        
        size_t punto = num_str.find('.');
        if (punto != string::npos) {
            for (int i = 1; i <= 5 && (punto + i) < num_str.length(); i++) {
                char c = num_str[punto + i];
                if (isdigit(c)) {
                    digitos_precisos[i-1] = c - '0';
                }
            }
        }


        int freq[10] = {0};
        for (int d : digitos_precisos) {
            if (d >= 0 && d <= 9) {
                freq[d]++;
            }
        }



        // Obtener frecuencias 
        vector<int> f;
        for (int i = 0; i < 10; i++) {
            if (freq[i] > 0) {
                f.push_back(freq[i]);
            }
        }

        sort(f.begin(), f.end(), greater<int>());

        // Clasificar
        string clase_nombre;
        if (f.size() == 0) {
            clases[DIFERENTES]++;
            clase_nombre = "Diff";
            continue;
        }
        if (f[0] == 5) {
            clases[QUINTILLA]++;
            clase_nombre = "Quintilla";
            continue;
        }
        if (f[0] == 4) {
            clases[POKER]++;
            clase_nombre = "Poker";
            continue;
        }
        if (f[0] == 3 && f.size() > 1 && f[1] == 2) {
            clases[FULL]++;
            clase_nombre = "FULL";
            continue;
        }
        if (f[0] == 3) {
            clases[TERCIA]++;
            clase_nombre = "Tercia";
            continue;
        }
        if (f[0] == 2 && f.size() > 1 && f[1] == 2) {
            clases[DOS_PARES]++;
            clase_nombre = "2 pares";
            continue;
        }
        if (f[0] == 2) {
            clases[UN_PAR]++;
            clase_nombre = "par";
            continue;

        }
        
        clases[DIFERENTES]++;
        clase_nombre = "Diff";
        

    }


    const char* nombres[7] = {
        "Diferentes", "Un par", "Dos pares", "Tercia", 
        "Full", "Poker", "Quintilla"
    };
    
        // Probabilidad teórica
    double prob[7] = {
        0.3024, // diferentes
        0.5040, // un par
        0.1080, // dos pares
        0.0720, // tercia
        0.0090, // full
        0.0045, // poker
        0.0001  // quintilla
    };

    double chi2 = 0.0;


    for (int i = 0; i < 7; i++) {
        double fe = total_manos * prob[i];
        double foe = (clases[i] - fe);
        double res = (foe * foe) / fe;
        
        cout << nombres[i] << endl 
            << "  fo:          " << setprecision(5) << fixed << clases[i] << endl 
            << "  pe:          " << setprecision(5) << fixed << prob[i] << endl
            << "  fe:          " << setprecision(5) << fixed << fe << endl
            << " (fo-fe):      " << setprecision(5) << fixed << foe << endl
            << " (fo-fe)^2/fe: " << setprecision(5) << fixed << res << endl << endl;
            chi2 += res;
    }

    double chi2_critico = 12.5916;
        cout << "CHI^2 observado: " << setprecision(5) << fixed << chi2 << endl;
    
        cout << setprecision(5) << fixed << chi2 << " <= " 
            << setprecision(5) << fixed << chi2_critico << endl;
    
    if (chi2 <= chi2_critico) {
        cout << "Se acepta H0, los números generados corresponden a una distribución uniforme" << endl;
    } else {
        cout << "Se rechaza H0, los números generados NO corresponden a una distribución uniforme" << endl;
    }

}
int main() {
    pokerDecimal();
    return 0;
}