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
    case 10: // Dígitos decimales 0-9 (p=0.1)
        chi2_critico = 16.91898;
        nombre = "num_0a1.txt";
        
        proba[0] = 0.1000000000;    proba[1] = 0.0900000000;  
        proba[2] = 0.0810000000;    proba[3] = 0.0729000000; 
        proba[4] = 0.0656100000;    proba[5] = 0.0590490000; 
        proba[6] = 0.0531441000;    proba[7] = 0.0478296900;  
        proba[8] = 0.0430467210;    proba[9] = 0.0387420489;  
        proba[10] = 1;
        for(int i = 0; i<10;i++){
            proba[10] -= proba[i];
        }  
        break;
        
    case 6: // Valores 1-6 (p=1/6≈0.166667)
        chi2_critico = 11.07050;
        nombre = "num_1a6.txt";
        
        proba[0] = 0.1666666667;    proba[1] = 0.1388888889;  
        proba[2] = 0.1157407407;    proba[3] = 0.0964506173; 
        proba[4] = 0.0803755144;    proba[5] = 0.0669795953; 
        proba[6] = 0.0558163294;    proba[7] = 0.0465136079;  
        proba[8] = 0.0387613399;    proba[9] = 0.0323011166;  
        proba[10] = 1;
        for(int i = 0; i<10;i++){
            proba[10] -= proba[i];
        }   
        break;
        
    case 4: // Valores 1-4 (p=0.25)
        chi2_critico = 7.81473;
        nombre = "num_1a4.txt";
        
        proba[0] = 0.2500000000;    proba[1] = 0.1875000000;  
        proba[2] = 0.1406250000;    proba[3] = 0.1054687500; 
        proba[4] = 0.0791015625;    proba[5] = 0.0593261719; 
        proba[6] = 0.0444946289;    proba[7] = 0.0333709717;  
        proba[8] = 0.0250282288;    proba[9] = 0.0187711716;  
        proba[10] = 1;
        for(int i = 0; i<10;i++){
            proba[10] -= proba[i];
        }  
        break;
        
    case 8: // Valores 1-8 (p=0.125)
        chi2_critico = 14.06714;
        nombre = "num_1a8.txt";
        
        proba[0] = 0.1250000000;    proba[1] = 0.1093750000;  
        proba[2] = 0.0957031250;    proba[3] = 0.0837402344; 
        proba[4] = 0.0732727051;    proba[5] = 0.0641136169; 
        proba[6] = 0.0560994148;    proba[7] = 0.0490870149;  
        proba[8] = 0.0429511391;    proba[9] = 0.0375822467;  
        proba[10] = 1;
        for(int i = 0; i<10;i++){
            proba[10] -= proba[i];
        }    
        break;
        
    case 20: // Valores 1-20 (p=0.05)
        chi2_critico = 16.91898;  //??? Sería lo mismo que 0 a 9?
        nombre = "num_1a20.txt";
        
        proba[0] = 0.1000000000;    proba[1] = 0.0900000000;  
        proba[2] = 0.0810000000;    proba[3] = 0.0729000000; 
        proba[4] = 0.0656100000;    proba[5] = 0.0590490000; 
        proba[6] = 0.0531441000;    proba[7] = 0.0478296900;  
        proba[8] = 0.0430467210;    proba[9] = 0.0387420489;  
        proba[10] = 1;
        for(int i = 0; i<10;i++){
            proba[10] -= proba[i];
        }  
        break;


        /*
        1 2 3 4 5 6 7 8 9 1-0 1-1 1-2 1-3 1-4 1-5 1-6 1-7 1-8 1-9 2-0
                No tienen la misma probabilidad
            0 = 1 /31
            1 = 12/31
            2 = 3 /31
            3 = 2 /31
            4 = 2 /31
            5 = 2 /31
            6 = 2 /31
            7 = 2 /31
            8 = 2 /31
            9 = 2 /31
        */
    }
        
    ifstream archivoEntrada(nombre);
    
    if (!archivoEntrada) {
        cerr << "Error al abrir el archivo de entrada: " << nombre << endl;
        return;
    }

    vector<string> resultado;
    string linea;
    int lineasProcesadas = 0;

    while (getline(archivoEntrada, linea)) {
        
        linea.erase(remove_if(linea.begin(), linea.end(), ::isspace), linea.end());
        
        if (linea.empty()) {
            continue;  
        }

        string digitosProcesados;

        // Caso 1: Formato "0.xxxx"
        if (linea.length() >= 2 && linea[0] == '0' && linea[1] == '.') {
            digitosProcesados = linea.substr(2);
        } 
        else digitosProcesados = linea;

        resultado.push_back(digitosProcesados);
        lineasProcesadas++;
    }
 
    archivoEntrada.close();

    vector<string> datos = resultado;

    const int MAX_HUECO = 11; 
    
    
    double n = 0.00000;
    double hueco[MAX_HUECO] = {0};
    int d = 0;
    if(rango == 10 || rango == 20) d = 1;
    if(rango == 20) rango = 9;
    for(int d = 0; d < rango; d++) { 
        bool encontrado = false;
        int contador_hueco = 0;
        
        for(string s : datos) {
            int lon = s.length();
            for(int i = 0; i<lon; i++){
                int actual = s[i] - '0';
                if(encontrado) {
                        if(actual == d) {
                            if(contador_hueco < MAX_HUECO) {
                                hueco[contador_hueco]+= 1.00000;
                                n++;
                            } else {
                                hueco[MAX_HUECO-1]+= 1.00000;
                                n+= 1.00000;
                            }
                            contador_hueco = 0;
                        } else {
                            contador_hueco++;
                        }
                    } else {
                        if(actual == d) {
                            encontrado = true;
                        }
                    }
            }
        }
    }
    

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
    huecos(20); //Malo - Incompleto
    
        
    
    return 0;
}