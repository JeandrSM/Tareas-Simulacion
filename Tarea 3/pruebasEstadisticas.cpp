#include <bits/stdc++.h>
using namespace std;

string pruebaPromedio(string nombre, string tipo){
    double resultado;
    double nume;
    double mu=0.5;
    double varianza = sqrt(1.0/1.12); 
    ifstream archivo(nombre);
    if (!archivo) {
        std::cout << "No se pudo abrir el archivo\n";
        return "malo";
    }
    while(archivo>>nume){
        resultado+=nume;
    }
    archivo.close();
    resultado = resultado/1000000.0;
    double zO = (resultado-mu)/(varianza/1000);
    cout<<zO<<endl;
    if(-1.96 < zO && zO < 1.96){
        return "Si cumple con esta PruebaPromedio";
    } else {return "No cumple con esta pruebaPromedio";}
}

int main (){
    string a = pruebaPromedio("numeros_aleatorios.txt", "no implementado");
    cout<<a; 
}