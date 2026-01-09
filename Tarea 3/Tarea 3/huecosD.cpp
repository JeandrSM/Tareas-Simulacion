#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <cctype>
#include <algorithm>
#include <cmath>

using namespace std;

void huecos(int rango) {

    string nombre = " ";
    double chi2_critico = 16.9190;
    double proba[11];

    switch (rango) {
    case 10:
        chi2_critico = 16.91898;
        nombre = "num_0a1.txt";
        proba[0]=0.1; proba[1]=0.09; proba[2]=0.081; proba[3]=0.0729;
        proba[4]=0.06561; proba[5]=0.059049; proba[6]=0.0531441;
        proba[7]=0.04782969; proba[8]=0.043046721; proba[9]=0.0387420489;
        break;

    case 4:
        chi2_critico = 7.81473;
        nombre = "num_1a4.txt";
        proba[0]=0.25; proba[1]=0.1875; proba[2]=0.140625;
        proba[3]=0.10546875; proba[4]=0.0791015625;
        proba[5]=0.0593261719; proba[6]=0.0444946289;
        proba[7]=0.0333709717; proba[8]=0.0250282288;
        proba[9]=0.0187711716;
        break;

    case 6:
        chi2_critico = 11.07050;
        nombre = "num_1a6.txt";
        proba[0]=0.1666666667; proba[1]=0.1388888889;
        proba[2]=0.1157407407; proba[3]=0.0964506173;
        proba[4]=0.0803755144; proba[5]=0.0669795953;
        proba[6]=0.0558163294; proba[7]=0.0465136079;
        proba[8]=0.0387613399; proba[9]=0.0323011166;
        break;

    case 8:
        chi2_critico = 14.06714;
        nombre = "num_1a8.txt";
        proba[0]=0.125; proba[1]=0.109375; proba[2]=0.095703125;
        proba[3]=0.0837402344; proba[4]=0.0732727051;
        proba[5]=0.0641136169; proba[6]=0.0560994148;
        proba[7]=0.0490870149; proba[8]=0.0429511391;
        proba[9]=0.0375822467;
        break;
    
    case 20: 
        chi2_critico = 16.91898;  
        nombre = "num_1a20.txt";
        
        proba[0] = 0.1;    proba[1] = 0.237253;  
        proba[2] = 0.11;    proba[3] = 0.07565; 
        proba[4] = 0.051;    proba[5] =0.040; 
        proba[6] = 0.032;    proba[7] = 0.0275;  
        proba[8] = 0.0245;    proba[9] = 0.0245;  
        proba[10] = 1;
        for(int i = 0; i<10;i++){
            proba[10] -= proba[i];
        }  
        break;
    }

    proba[10] = 1.0;
    for (int i = 0; i < 10; i++) proba[10] -= proba[i];

    ifstream archivoEntrada(nombre);
    if (!archivoEntrada) {
        cerr << "Error al abrir el archivo de entrada: " << nombre << endl;
        return;
    }

    vector<string> datos;
    string linea;

    while (getline(archivoEntrada, linea)) {
        linea.erase(remove_if(linea.begin(), linea.end(), ::isspace), linea.end());
        if (linea.empty()) continue;
        if (linea.size() >= 2 && linea[0]=='0' && linea[1]=='.')
            linea = linea.substr(2);
        datos.push_back(linea);
    }
    archivoEntrada.close();

    const int MAX_HUECO = 11;
    double hueco[MAX_HUECO] = {0};
    int hueco_dig[MAX_HUECO][10] = {{0}};
    double n = 0.0;

    int d_inicio, d_fin;

    if (rango == 10 || rango == 20) {
        d_inicio = 0;
        d_fin = 9;
    } else {
        d_inicio = 1;
        d_fin = rango;
    }

    for (int d = d_inicio; d <= d_fin; d++) {
        bool encontrado = false;
        int contador_hueco = 0;

        for (string s : datos) {
            for (char c : s) {
                int actual = c - '0';
                if (encontrado) {
                    if (actual == d) {
                        int h = (contador_hueco < MAX_HUECO) ? contador_hueco : MAX_HUECO - 1;
                        hueco[h]++;
                        hueco_dig[h][d]++;
                        n++;
                        contador_hueco = 0;
                    } else {
                        contador_hueco++;
                    }
                } else if (actual == d) {
                    encontrado = true;
                }
            }
        }
    }
    cout << "\nHueco";
    for (int d = d_inicio; d <= d_fin; d++)
        cout << setw(12) << d;
    cout << setw(12) << "Total" << endl;
    long long total = 0;
    for (int h = 0; h < MAX_HUECO; h++) {
        cout << setw(5) << h;
        long long total_fila = 0;

        for (int d = d_inicio; d <= d_fin; d++) {
            cout << setw(12) << hueco_dig[h][d];
            total_fila += hueco_dig[h][d];
        }

        cout << setw(12) << total_fila << endl;
        total += total_fila;
    }

    cout << endl <<"=====      "<< setw(10) <<"Total de Huecos: "<< setw(10)  << total << setw(10) << "=====" << endl;



    double chi2 = 0;

    for (int i = 0; i < 11; i++) {
        double fe = n * proba[i];
        double foe = (hueco[i] - fe);
        double res = (foe * foe) / fe;

        cout << "Hueco " << i  << ":" << endl 
            << "  fo:          " << setprecision(5) << fixed << hueco[i] << endl 
            << "  pe:          " << setprecision(5) << fixed << proba[i] << endl
            << "  fe:          " << setprecision(5) << fixed << fe << endl
            << " (fo-fe):      " << setprecision(5) << fixed << foe << endl
            << " (fo-fe)^2/fe: " << setprecision(5) << fixed << res << endl << endl;

        chi2 += res;
    }

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

    cout << "====================== Numeros de [0,1[ ======================" << endl;
    huecos(10);

    cout << "====================== Numeros de 1 a 4 ======================" << endl;
    huecos(4);

    cout << "====================== Numeros de 1 a 6 ======================" << endl;
    huecos(6);

    cout << "====================== Numeros de 1 a 8 ======================" << endl;
    huecos(8);

    cout << "====================== Numeros de 1 a 20 =====================" << endl;
    huecos(20);

    return 0;
}
