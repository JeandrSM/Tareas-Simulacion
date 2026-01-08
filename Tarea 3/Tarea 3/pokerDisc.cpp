#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <string>
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

void probabili(int rango, double prob[7]) {
   if (rango == 4) {
        prob[DIFERENTES] = 0.0;  
        prob[UN_PAR] = 0.234375;      
        prob[DOS_PARES] = 0.3515625;   
        prob[TERCIA] = 0.234375;      
        prob[FULL] = 0.1171875;        
        prob[POKER] = 0.05859375;       
        prob[QUINTILLA] = 0.00390625;   
        return;
    }
    if (rango == 6) {
        prob[DIFERENTES] = 0.09259259;  
        prob[UN_PAR] = 0.46296296;      
        prob[DOS_PARES] = 0.23148148;   
        prob[TERCIA] = 0.15432099;      
        prob[FULL] = 0.03858025;        
        prob[POKER] = 0.01929012;       
        prob[QUINTILLA] = 0.00077160;  
        return;
    }
    if (rango == 8) {
        prob[DIFERENTES] = 0.205078125;  
        prob[UN_PAR] = 0.5126953125;     
        prob[DOS_PARES] = 0.1538085938;
        prob[TERCIA] = 0.1025390625;     
        prob[FULL] = 0.01708984375;    
        prob[POKER] = 0.008544921875;    
        prob[QUINTILLA] = 0.000244140625;
        return;
    }
    if (rango == 20) {
        prob[DIFERENTES] = 0.58140000;
        prob[UN_PAR] = 0.36337500;
        prob[DOS_PARES] = 0.0320625;
        prob[TERCIA] = 0.02137500;
        prob[FULL] = 0.00118750;
        prob[POKER] = 0.00059375;
        prob[QUINTILLA] = 0.00000625;
    return;
}

}


void poker(int rango){

    string nombre = " ";
    switch (rango)
    {
    case 4:
        nombre = "num_1a4.txt";
        break;

    case 6:
        nombre = "num_1a6.txt";
        break;

    case 8:
        nombre = "num_1a8.txt";
        break;

    case 20:
        nombre = "num_1a20.txt";
        break;
    }
    ifstream archivo(nombre);  
    if (!archivo) {
        cerr << "Error al abrir el archivo\n";
        return;
    }


    vector<int> datos;  
    int numero;
    
    
    while (archivo >> numero) {
                datos.push_back(numero);
    }
    archivo.close();
    
    if (datos.empty()) {
        cerr << "Error: No se leyeron datos válidos.\n";
        return;
    }
    
    

    int clases[7] = {0};
    int total_manos = 0;  

    int tam_freq = rango + 1;  
    
    for (size_t i = 0; i <= datos.size() - 5; i += 5) {
        vector<int> mano(5);
        
        for (int j = 0; j < 5; j++) {
            mano[j] = datos[i + j];
        }
        
        
        vector<int> freq(tam_freq, 0);  
        
        for (int num : mano) {
                freq[num]++; 
            
        }
        
        vector<int> f;
        for (int val = 1; val <= rango; val++) {  
            if (freq[val] > 0) {
                f.push_back(freq[val]);
            }
        }
        
        // Ordenar de mayor a menor
        sort(f.begin(), f.end(), greater<int>());
        
        // Clasificar la mano
        if (f.empty()) {
            clases[DIFERENTES]++;
        }
        else if (f[0] == 5) {
            clases[QUINTILLA]++;
        }
        else if (f[0] == 4) {
            clases[POKER]++;
        }
        else if (f[0] == 3 && f.size() > 1 && f[1] == 2) {
            clases[FULL]++;
        }
        else if (f[0] == 3) {
            clases[TERCIA]++;
        }
        else if (f[0] == 2 && f.size() > 1 && f[1] == 2) {
            clases[DOS_PARES]++;
        }
        else if (f[0] == 2) {
            clases[UN_PAR]++;
        }
        else {
            clases[DIFERENTES]++;
        }
        
        total_manos++; 
        
    }

    double prob[7];
    probabili(rango, prob);

    const char* nombres[7] = {
        "Diferentes", "Un par", "Dos pares", "Tercia", 
        "Full", "Poker", "Quintilla"
    };

    
    
    double chi2 = 0.0;


    for (int i = 0; i < 7; i++) {
        double fe = total_manos * prob[i];
        double foe = (clases[i] - fe);
        double res = (foe * foe) / fe;
        if(fe == 0) res = 0;
            
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
    cout << "====================== Numeros de 1 a 6 ======================" << endl;
    poker(6);
    cout << "====================== Numeros de 1 a 4 ======================" << endl;
    poker(4);
    cout << "====================== Numeros de 1 a 8 ======================" << endl;
    poker(8);
    cout << "====================== Numeros de 1 a 20 =====================" << endl;
    poker(20);

    return 1;
}