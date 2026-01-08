#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <iomanip> 

using namespace std;

    // Varianza teórica  (b-a)^2 / 12  =  1/12  <- [0,1[
double varT0 = 1.0 / 12.0;
    // Varianza discreta teórica  (n^2 - 1) / 12  =  35/12 <- {1,...6}
double varT6 = 35.0 / 12.0;
    // Varianza discreta teórica  (n^2 - 1) / 12  =  15/12  <- {1,...4}
double varT4 = 15.0 / 12.0;
    // Varianza discreta teórica  (n^2 - 1) / 12  =  63/12  <- {1,...8}
double varT8 = 63.0 / 12.0;
    // Varianza discreta teórica  (n^2 - 1) / 12  =  399/12  <- {1,...20}
double varT20 = 399.0 / 12.0;



double varianzas[] = {varT0, varT6, varT4, varT8, varT20};

void varianza(int rango){
    string nombre = " ";
    double varT = 0.0;
    double men = 997229.05853;
    double may = 1002772.70008;
    switch (rango)
    {
    case 10:
        nombre = "num_0a1.txt";
        varT = varianzas[0];
        break;
    case 4:
        nombre = "num_1a4.txt";
        varT = varianzas[2];
        break;

    case 6:
        nombre = "num_1a6.txt";
        varT = varianzas[1];
        break;

    case 8:
        nombre = "num_1a8.txt";
        varT = varianzas[3];
        break;

    case 20:
        nombre = "num_1a20.txt";
        varT = varianzas[4];
        break;
    }
    ifstream archivo(nombre);  

    if (!archivo) {
        cerr << "Error al abrir el archivo\n";
        return;
    }

    vector<double> datos;
    double x;

    // Leer datos
    while (archivo >> x) {
        datos.push_back(x);
    }
    archivo.close();

    int n = datos.size();

    
    double suma = 0.0;
    for (double v : datos)
        suma += v;

    double media = suma / n;

    
    double sumaVar = 0.0;
    for (double v : datos)
        sumaVar += pow(v - media, 2);

    double varM = sumaVar / (n - 1);

    double chiT = ((n-1) * varM) / varT;

    cout << "Varianza muestral: " << varM << endl;
    cout << "Varianza Teorica : " << varT << endl;
    cout    << setprecision(5) << fixed << men << " <= " 
            << setprecision(5) << fixed << chiT << " <= " 
            << setprecision(5) << fixed << may << endl;

    if(chiT >= men && chiT <= may) cout << " Se mantiene la hipotesis de H0 "<< 
    "y por lo tanto se concluye que los numeros generados provienen de una distribucion" << endl <<
    " cuya varianza concuerda con la distribucion uniforme." << endl;
    else cout <<"No sigue unba distribucion uniforme, se rechaza H0" << endl;
    
}


int main() {
    
    varianza(10);
    varianza(6);
    varianza(4);
    varianza(8);
    varianza(20);
    return 0;
}
