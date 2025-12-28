#include <iostream>
#include <bits/stdc++.h>
using namespace std;


int SET(int n, int i) {
    return n | (1 << i);
}

int congruBin(int n, int NUMBITS) {
    int ub = n & 1;          // bit posición 0
    int pb = (n & 4) >> 2;   // bit posición 2
    int xb = ub ^ pb;        // XOR

    if (xb)
        return SET(n >> 1, NUMBITS - 1);
    return n >> 1;
}


long long int cantDigi(long long int n){
	if(n) return 1+cantDigi(n/10);
	return 0;
}

long long int cuadraMedi(long long int n){
	n*=n;
	int cant=cantDigi(n);
	if(cant&1) cant++;
	long long int pote=pow(10,((cant-4)>>1));
	return (n/pote)%10000;
}
void imprimir_lista(vector<long long int> lista){
    for (auto x : lista) cout << x << ' ';
    cout << '\n';
}

long long int congruMixto(long long int n, long long int a, long long int c, long long int m){
    __int128 temp = (__int128)n * a + c; //Chat dice que se hace así pero se ve diabolico eso
    return (long long)(temp % m);
}


bool conMixto(long long int semilla, long long int a, long long int c, long long int m, bool imprimir){
    vector<bool> visto(m, false);
    vector<long long int> lista;
    
    lista.push_back(semilla);
    visto[semilla] = true;
    bool bien = true;
    for(int i = 1; i<m; i++){
        long long int temp = a * semilla + c;
        semilla =  (temp % m);
        if(visto[semilla]){
            cout << "Repeticion de " << semilla << " en i : " << i << endl;
            bien = false;
            lista.push_back(semilla);
            break;
        }
        visto[semilla] = true;
        if(imprimir) lista.push_back(semilla);
    }
    if(imprimir) imprimir_lista(lista);
    
    return bien;
}




bool revisarM(long long int semilla, long long int a, long long int c, long long int m){
	vector<bool> visto(m, false);
    for(long long int i=0; i<m; i++){
    	cout<<semilla<<endl;
        if(visto[semilla]){
            cout<<"Fallo en : "<<semilla<<" En el i :"<<i<<endl;
            return false;
        }
        visto[semilla]=true;
        semilla=congruMixto(semilla, a, c, m);
    }
    return true;
}
void ejercicio1(){
    cout << "---  Semilla: 0110 ---" << endl;
    int n = 6; // 0110, Si realiza todo el recorrido
    for (int i = 0; i <= 7; i++) {
        cout << n << " ";
        n = congruBin(n,3);
    } 
    cout << endl;
    cout << "---  Semilla: 1111 ---" << endl;
    int n2 = 15; // 1111 No realiza todo el recorrido
    for (int i = 0; i <= 16; i++) {
        cout << n2 << " ";
        n2 = congruBin(n2,4);
    }
    cout << endl;
}
void ejercicio2(){
    int n = 17; // Cosas muy raras de polinomios primitivos, pero al ser 2**5 -1 = 31 primo
    //sirve bien con el 0 y 1
    cout << "---  Semilla: 17 ---" << endl;
    for (int i = 0; i <= 31; i++) {
        cout << n << " ";
        n = congruBin(n,5);
    }
    cout << endl;
}
void ejercicio3(){
    long long int x=3567345;
    cout << "---  Semilla: "<< x << " ---" << endl;
    for(int i=0; i<=50;i++){
    	cout<<i<<": "<<x<<endl;
    	x=cuadraMedi(x);
    }
    
    long long int x1=1234500012;
    cout << "---  Semilla: "<< x1 << " ---" << endl;
    for(int i=0; i<=50;i++){
    	cout<<i<<": "<<x1<<endl;
    	x1=cuadraMedi(x1);
    }
   
    long long int x2=4567234902;
    cout << "---  Semilla: "<< x2 << " ---" << endl;
    for(int i=0; i<=50;i++){
    	cout<<i<<": "<<x2<<endl;
    	x2=cuadraMedi(x2);
    }
}
void ejercicio4(){
    cout << "a." << endl;
    if(conMixto(7,5,24,32, true)) cout << "---Si Cumple con el Periodo---" << endl; else cout << "---No Cumple con el Periodo---" << endl;
    cout << "_________________________" << endl;
    cout << "b." << endl;
    if(conMixto(8,9,13,32, true)) cout << "---Si Cumple con el Periodo---" << endl; else cout << "---No Cumple con el Periodo---" << endl;
    cout << "_________________________" << endl;
    cout << "c." << endl;
    if(conMixto(13,50,17,64, true)) cout << "---Si Cumple con el Periodo---" << endl; else cout << "---No Cumple con el Periodo---" << endl;
    cout << "_________________________" << endl;
    cout << "d." << endl;
    if(conMixto(15,8,16,100, true)) cout << "---Si Cumple con el Periodo---" << endl; else cout << "---No Cumple con el Periodo---" << endl;
    cout << "_________________________" << endl;
    cout << "e." << endl;
    if(conMixto(3,5,21,100, true)) cout << "---Si Cumple con el Periodo---" << endl; else cout << "---No Cumple con el Periodo---" << endl;
    cout << "_________________________" << endl;
}

void ejercicio5(){
    cout << "a." << endl;
    if(conMixto(7,5,0,64, false)) cout << "---Si Cumple con el Periodo---" << endl; else cout << "---No Cumple con el Periodo---" << endl;
    cout << "_________________________" << endl;
    cout << "b." << endl;
    if(conMixto(9,11,0,128, false)) cout << "---Si Cumple con el Periodo---" << endl; else cout << "---No Cumple con el Periodo---" << endl;
    cout << "_________________________" << endl;
    cout << "c." << endl;
    if(conMixto(3,221,0,1000, false)) cout << "---Si Cumple con el Periodo---" << endl; else cout << "---No Cumple con el Periodo---" << endl;
    cout << "_________________________" << endl;
    cout << "d." << endl;
    if(conMixto(17,203,0,100000, false)) cout << "---Si Cumple con el Periodo---" << endl; else cout << "---No Cumple con el Periodo---" << endl;
    cout << "_________________________" << endl;
    cout << "e." << endl;
    if(conMixto(19,211,0,100000000, false)) cout << "---Si Cumple con el Periodo---" << endl; else cout << "---No Cumple con el Periodo---" << endl;
    cout << "_________________________" << endl;
}

void ejercicio6(){
    cout << "x(0): 1" << endl;
    cout << "a   : 16" << endl;
    cout << "c   : 4" << endl;
    cout << "m   : 15" << endl;
    if(conMixto(1,16,4,15, true)) cout << "---Si Cumple con el Periodo---" << endl; else cout << "---No Cumple con el Periodo---" << endl;
    /*
    Este funciona por esto:
    Para numeros entre 0 a 14, solo esta el M= 15 (Por ser los que componen el modulo)
    Para sacar un buen C, se ocupa que el maximo comun divisor de C,M sea 1 (coprimos) 
    15 y 4 son coprimos
    Para sacar un buen a, se ocupa (a-1)mod(factorizacion prima de M) sea 0
    (a-1)mod(3) y (a-1)mod(5), el a que cumple eso es 16
    */
}

void ejercicio7(){
    cout << "x(0): 1" << endl;
    cout << "a   : 13" << endl;
    cout << "c   : 2" << endl;
    cout << "m   : 9" << endl;
    if(conMixto(1,13,2,9, true)) cout << "---Si Cumple con el Periodo---" << endl; else cout << "---No Cumple con el Periodo---" << endl;
}

void ejercicio8(){
    cout << "x(0): 1" << endl;
    cout << "a   : 20" << endl;
    cout << "c   : 5" << endl;
    cout << "m   : 19" << endl;
    if(conMixto(1,20,5,19, true)) cout << "---Si Cumple con el Periodo---" << endl; else cout << "---No Cumple con el Periodo---" << endl;
}


void ejercicio9(){
    cout << "Mixto:" << endl;
    cout << "   x(0): 1" << endl;
    cout << "   a   : 1" << endl;
    cout << "   c   : 7" << endl;
    cout << "   m   : 10" << endl;
    if(conMixto(1,1,7,10, true)) cout << "---Si Cumple con el Periodo---" << endl; else cout << "---No Cumple con el Periodo---" << endl;
    cout << "_________________________" << endl;
    cout << "Multiplicativo:" << endl;
    cout << "   x(0): 1" << endl;
    cout << "   a   : 7" << endl;
    cout << "   m   : 11" << endl;
    if(conMixto(1,7,0,11, true)) cout << "---Si Cumple con el Periodo---" << endl; else cout << "---No Cumple con el Periodo---" << endl;
    cout << "_________________________" << endl;


}



int main() {
    while (true) {
        cout << "\n========== MENÚ DE EJERCICIOS ==========" << endl;
        cout << "1.  Ejercicio 1" << endl;
        cout << "2.  Ejercicio 2" << endl;
        cout << "3.  Ejercicio 3" << endl;
        cout << "4.  Ejercicio 4" << endl;
        cout << "5.  Ejercicio 5" << endl;
        cout << "6.  Ejercicio 6" << endl;
        cout << "7.  Ejercicio 7" << endl;
        cout << "8.  Ejercicio 8" << endl;
        cout << "9.  Ejercicio 9" << endl;
        cout << "10. Ejercicio 10" << endl;
        cout << "0. Salir" << endl;
        cout << "Seleccione una opción: ";

        int op;
        cin >> op;

        switch (op) {
            case 1:
                cout << "\n" << "\n" << "\n" << "\n" << endl;
                cout << "================= Ejercicio 1 =================" << endl;
                ejercicio1();
                break;

            case 2:
                cout << "\n" << "\n" << "\n" << "\n" << endl;
                cout << "================= Ejercicio 2 =================" << endl;
                ejercicio2();
                break;

            case 3:
                cout << "\n" << "\n" << "\n" << "\n" << endl;
                cout << "================= Ejercicio 3 =================" << endl;
                ejercicio3();
                break;

            case 4:
                cout << "\n" << "\n" << "\n" << "\n" << endl;
                cout << "================= Ejercicio 4 =================" << endl;
                ejercicio4();
                break;

            case 5:
                cout << "\n" << "\n" << "\n" << "\n" << endl;
                cout << "================= Ejercicio 5 =================" << endl;
                ejercicio5(); // revisar
                break;

            case 6:
                cout << "\n" << "\n" << "\n" << "\n" << endl;
                cout << "================= Ejercicio 6 =================" << endl;
                ejercicio6();
                break;

            case 7:
                cout << "\n" << "\n" << "\n" << "\n" << endl;
                cout << "================= Ejercicio 7 =================" << endl;
                ejercicio7();
                break;

            case 8:
                cout << "\n" << "\n" << "\n" << "\n" << endl;
                cout << "================= Ejercicio 8 =================" << endl;
                ejercicio8();
                break;

            case 9:
                cout << "\n" << "\n" << "\n" << "\n" << endl;
                cout << "================= Ejercicio 9 =================" << endl;
                ejercicio9();
                break;
            case 10:
                cout << "\n" << "\n" << "\n" << "\n" << endl;
                cout << "================= Ejercicio 10 =================" << endl;
                //ejercicio10();
                break;

            case 0:
                return 0;

            default:
                cout << "Opción inválida. Intente de nuevo." << endl;
        }
    }
    return 0;
}
    
