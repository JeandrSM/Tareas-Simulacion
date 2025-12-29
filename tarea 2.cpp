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
    __int128 temp = (__int128)n * a + c; 
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

bool nconMixto(long long int semilla, long long int a, long long int c, long long int m, bool imprimir){
    vector<bool> visto(m, false);
    vector<long long int> lista;
    
    lista.push_back(semilla);
    visto[semilla] = true;
    bool bien = true;
    for(int i = 1; i<m; i++){
        long long int temp = a * semilla + c;
        semilla =  (temp % m);
        if(visto[semilla]){
            bien = false;
            lista.push_back(semilla-1);
            break;
        }
        visto[semilla] = true;
        if(imprimir) lista.push_back(semilla);
    }
    if(imprimir) imprimir_lista(lista);
    
    return bien;
}


long long int fibo(long long int x0, long long int x1, long long int m){
	return (x0 + x1) % m;
}

void revisarFib(long long int x0, long long int x1, long long int m){
	cout<<x0<<" ";
	cout<<x1<<" ";
	for(int i=2; i<m; i++){
		int nume = fibo(x0,x1,m);
		x0=x1;
		x1=nume;
		cout<<nume<<" ";
	}
}

void nrevisarFib(long long int x0, long long int x1, long long int m){
	cout<<x0-1<<" ";
	cout<<x1-1<<" ";
	for(int i=2; i<=m-2; i++){
		int nume = fibo(x0,x1,m);
		x0=x1;
		x1=nume;
		cout<<nume-1<<" ";
	}
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
    cout << "---  Semilla: 0110 --- Si realiza todo el recorrido" << endl;
    int n = 6; // 0110, Si realiza todo el recorrido
    for (int i = 0; i <= 7; i++) {
        cout << n << " ";
        n = congruBin(n,3);
    } 
    cout << endl;
    cout << "---  Semilla: 1111 --- No realiza todo el recorrido" << endl;
    int n2 = 15; // 1111 No realiza todo el recorrido
    for (int i = 0; i <= 16; i++) {
        cout << n2 << " ";
        n2 = congruBin(n2,4);
    }
    cout << endl;
}
void ejercicio2(){
    int n = 17; // Al ser 2**5 -1 = 31 primo
                //sirve bien con el 0 y 2
    cout << "---  Semilla: 17 --- Se implementa igual que la anterior bits 0,2 y la operacion que se realiza es igual (xor)" << endl;
    cout << "Se logra apreciar que realiza todo el recorrido" << endl;
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
    if(conMixto(7,5,0,64, false)) cout << "---Si Cumple con el Periodo---" << endl; else cout << "---No Cumple con el Periodo de 0 hasta M-1 pero si cumple con el maximo periodo teorico para m=64---"  << endl;
    cout << "_________________________" << endl;
    cout << "b." << endl;
    if(conMixto(9,11,0,128, false)) cout << "---Si Cumple con el Periodo---" << endl; else cout << "---No Cumple con el Periodo de 0 hasta M-1 pero si cumple con el maximo periodo teorico para m=128---"  << endl;
    cout << "_________________________" << endl;
    cout << "c." << endl;
    if(conMixto(3,221,0,1000, false)) cout << "---Si Cumple con el Periodo---" << endl; else cout << "---No Cumple con el Periodo de 0 hasta M-1 ni tampoco el maximo periodo teorico para m=1000---" << endl;
    cout << "_________________________" << endl;
    cout << "d." << endl;
    if(conMixto(17,203,0,100000, false)) cout << "---Si Cumple con el Periodo---" << endl; else cout << "---No Cumple con el Periodo de 0 hasta M-1 ni tampoco el maximo periodo teorico para m=100000---" << endl;
    cout << "_________________________" << endl;
    cout << "e." << endl;
    if(conMixto(19,211,0,100000000, false)) cout << "---Si Cumple con el Periodo---" << endl; else cout << "---No Cumple con el Periodo de 0 hasta M-1 ni tampoco el maximo periodo teorico para m=100000000---" << endl;
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
    Para numeros entre 0 a 14, esta el M= 15 (Por ser los que componen el modulo)
    Para sacar un buen C, se ocupa que el maximo comun divisor de C,M sea 1 (coprimos) 
    15 y 4 son coprimos
    Para sacar un buen a, se ocupa (a-1)mod(factorizacion prima de M) sea 0
    (a-1)mod(3) y (a-1)mod(5), el a que cumple eso es 16 al igual que el 1
    */
}

void ejercicio7(){
    cout << "x(0): 1" << endl;
    cout << "a   : 7" << endl;
    cout << "c   : 7" << endl;
    cout << "m   : 9" << endl;
    if(conMixto(1,7,7,9, true)) cout << "---Si Cumple con el Periodo---" << endl; else cout << "---No Cumple con el Periodo---" << endl;
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
    if(conMixto(1,7,0,11, true)) cout << "---Si Cumple con el Periodo---" << endl; else cout << "---No Cumple con el Periodo de 0 hasta m-1 debido a ser multiplicativa para encontrar un buen ciclo tiene que seguir las propiedades algebraicas de un grupo multiplicativo modulo siendo todos sus elementos invertibles para lo cual el 0 no puede pertenecer y solo se encuentran los coprimos de m. Si es estrictamente necesario se puede restar 1 a cada numero dando como resultado un periodo de 0 hasta 9 de tam 10 ---" << endl;
    cout<<endl;
   //Imprimir aqui la lista numer-1
    cout<<endl;
    cout << "_________________________" << endl;
    cout << "Aditivo:" << endl;
    cout << "   x(0): 2" << endl;
    cout << "   x(1): 5" << endl;
    cout << "   m   : 11" << endl;
    revisarFib(2,5,11);
    cout<<endl;
    cout << "---No Cumple con el Periodo de 0 hasta M-1 similar al anterior pero de ser estrictamente necesario se le puede restar 1 a cada numero dando como resultado un periodo de 0 hasta 9 de tam 10 ---" << endl;
    cout<<endl;
    nrevisarFib(2,5,11);
    cout<<endl;
    cout << "_________________________" << endl;


}

int congruencial_mixto(int &x) {
    int a = 1;
    int c = 7;
    int m = 10;
    x = (a * x + c) % m;
    return x;
}


void ejercicio10(int M){
    cout << "------ a. Moneda ------" << endl;
    int m = M;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(0, 9);

    int corona = 0, escudo = 0;

    for (int i = 0; i < m; i++) {
        int r = dist(gen);   // número uniforme 0–9

        if (r <= 4) {
            corona++;
        } else {
            escudo++;
        }
    }
    cout << "\nResultados de Simulacion:\n";
    float CoroPro = (float)corona/m;
    float EscuPro = (float)escudo/m;
    cout << "   Corona: " << corona << " <---> Proporcion: " << CoroPro  << endl;
    cout << "   Escudo: " << escudo << " <---> Proporcion: " << EscuPro << endl;
    cout << "Para simular un lanzamiento de moneda legal se utiliza el generador aleatorio de numeros entre 0 y 9. \n "
    << "Los valores de 0 a 4 se asignan al evento corona y los valores de 5 a 9 al evento escudo, garantizando una probabilidad de 0.50 para cada resultado."
    << endl;

    cout << "__________________________________________________" << endl;

    cout << "------ b. a,b,c ------" << endl;
    int A=0,B=0,C=0;
    for (int i = 0; i < m; i++) {
        int r = dist(gen);   // número uniforme 0–9

        if(!r) {
            A++;
            continue;
        }
        if(r<5){
            B++;
            continue;
        }
        C++;
    }

    cout << "\nResultados de Simulacion:\n";
    float APro = (float)A/m;
    float BPro = (float)B/m;
    float CPro = (float)C/m;
    cout << "   As: " << A << " <---> Proporcion: " << APro << endl;
    cout << "   Bs: " << B << " <---> Proporcion: " << BPro << endl;
    cout << "   Cs: " << C << " <---> Proporcion: " << CPro << endl;
    cout << "Basta con distribuir los numeros de tal manera que generen la probabilidad según la proporcion.\n "
    << "Es decir: a = [0], b = [1,2,3,4], c = [5,6,7,8,9]."
    << "           1/10         4/10             5/10 "
    << endl;

    cout << "__________________________________________________" << endl;


    cout << "------ c. Lanzar un dado ------" << endl;
    int _1 = 0, _2 = 0, _3 = 0, _4 = 0, _5 = 0, _6 = 0;

    for (int i = 0; i < m; i++) {
        int cara = dist(gen); 

        switch (cara) {
            case 1: _1++; break;
            case 2: _2++; break;
            case 3: _3++; break;
            case 4: _4++; break;
            case 5: _5++; break;
            case 6: _6++; break;
            default: i--;
        }
    }

    cout << "\nResultados de Simulacion:\n";
    float _1Pro = (float)_1 / m;  float _4Pro = (float)_4 / m;
    float _2Pro = (float)_2 / m;  float _5Pro = (float)_5 / m;
    float _3Pro = (float)_3 / m;  float _6Pro = (float)_6 / m;

    cout << "   1s: " << _1 << " <---> Proporcion: " << _1Pro << endl;
    cout << "   2s: " << _2 << " <---> Proporcion: " << _2Pro << endl;
    cout << "   3s: " << _3 << " <---> Proporcion: " << _3Pro << endl;
    cout << "   4s: " << _4 << " <---> Proporcion: " << _4Pro << endl;
    cout << "   5s: " << _5 << " <---> Proporcion: " << _5Pro << endl;
    cout << "   6s: " << _6 << " <---> Proporcion: " << _6Pro << endl;


    cout << " En este caso No se puede hacer módulo, esto debido a que la probalidad sería diferente."
    << " 0%6 = 0, 1%6 = 1, 2%6 = 2, 3%6 = 3, 4%6 = 4, 5%6 = 4 , 6%6= 0, 7%6 = 1, 8%6 = 2, 9%6 = 3   <== Hay valores que se repiten\n "
    << "Lo que se realizó es que 6 numeros representarian una cara del dado, si no sale esos numeros, que la probabilidad es de 4/10, se vuelve"
    << " a lanzar el dado sin contar esos nuevos lanzamientos extra."
    << endl;

    cout << "------ d. Lanzar un dado [0,99] ------" << endl;

    uniform_int_distribution<int> dist99(0, 99);

    int d1 = 0, d2 = 0, d3 = 0, d4 = 0, d5 = 0, d6 = 0;

    for (int i = 0; i < m; i++) {
        int r = dist99(gen);             
        int cara = r / 16;      // 0–95 0–5

        switch (cara) {
            case 0: d1++; break;
            case 1: d2++; break;
            case 2: d3++; break;
            case 3: d4++; break;
            case 4: d5++; break;
            case 5: d6++; break;
            default: i--;
            }

    }

    cout << "\nResultados de Simulacion:\n";
    cout << "   1s: " << d1 << " <---> Proporcion: " << (float)d1/m << endl;
    cout << "   2s: " << d2 << " <---> Proporcion: " << (float)d2/m << endl;
    cout << "   3s: " << d3 << " <---> Proporcion: " << (float)d3/m << endl;
    cout << "   4s: " << d4 << " <---> Proporcion: " << (float)d4/m << endl;
    cout << "   5s: " << d5 << " <---> Proporcion: " << (float)d5/m << endl;
    cout << "   6s: " << d6 << " <---> Proporcion: " << (float)d6/m << endl;

    cout << " Ocurre lo mismo que la parte c, la diferencia es que en esta implementacion dividimos el numero entre 16, ya que 16*6 = 96,"
    << "esto nos deja distribuir 96 numeros en las 6 caras de forma uniforme, los 4 numeros restantes, se aplica lo del ejercicio c, se vuelven a lanzar"
    << " 0-15 = 0 | 16-31 = 1 | 32-47 = 2.....etc  se usa la parte entera de la division "
    << endl;

    cout << "Para los ejercicios a,b se puede seguir simulando de la misma manera, solo distribuir nuevamente los numeros"<<endl;

    cout << "¿Se pueden simular dados con todos los poliedros regulares?" << endl;
    cout << "Siempre que el dado se convexo, ,sí, porque todas sus caras tienen la misma probabilidad de ocurrir sin variaciones"<<endl;


    


}

void ejercicioAdi(int i){
    
    cout << "   x(0): 254102" << endl;
    cout << "   a   : 1" << endl;
    cout << "   c   : 756" << endl;
    cout << "   m   : 1000000007" << endl;
    if(i){
    if(conMixto(254102,1,756,1000000007, false)) cout << "---Si Cumple con el Periodo---" << endl; else cout << "---No Cumple con el Periodo---" << endl;}
    cout << "_________________________" << endl;
    cout << "   x(0): 254102" << endl;
    cout << "   a   : 1" << endl;
    cout << "   c   : 756" << endl;
    cout << "   m   : 1000000009" << endl;
    if(i){
    if(conMixto(254102,1,756,1000000009, false)) cout << "---Si Cumple con el Periodo---" << endl; else cout << "---No Cumple con el Periodo---" << endl;}
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
        cout << "11. Adicionales   " << endl;
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
                cout << "Lanzamiento para la simulacion de la moneda >" << endl;
                int M;
                cin >> M;
                ejercicio10(M);
                break;
                
            case 11:
                cout << "\n" << "\n" << "\n" << "\n" << endl;
                cout << "================= Ejercicio 11 =================" << endl;
                cout << "Ejercicios adicionales" << endl;
                cout << "Pueden tardar mucho tiempo en comprobarse que sean correctas." << endl;
                cout << "Ingrese 1 si quiere correr la comprobación" << endl;
                cout << "Ingrese 0 si quiere correr la comprobación" << endl;
                int adis;
                cin >> adis;
                ejercicioAdi(adis);
                break;

            case 0:
                return 0;

            default:
                cout << "Opción inválida. Intente de nuevo." << endl;
        }
    }
    return 0;
}
    
