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

long long int congruMixto(long long int n, long long int a, long long int c, long long int m){
    __int128 temp = (__int128)n * a + c; //Chat dice que se hace así pero se ve diabolico eso
    return (long long)(temp % m);
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


int main() {
    /*
    int n = 6; // 0110, Si realiza todo el recorrido
    for (int i = 0; i <= 7; i++) {
        cout << n << endl;
        n = congruBin(n,3);
    }
    int n = 15; // 1111 No realiza todo el recorrido
    for (int i = 0; i <= 16; i++) {
        cout << n << endl;
        n = congruBin(n,4);
    }

    int n = 17; // Cosas muy raras de polinomios primitivos, pero al ser 2**5 -1 = 31 primo
    //sirve bien con el 0 y 1
    for (int i = 0; i <= 31; i++) {
        cout << n << endl;
        n = congruBin(n,5);
    }

    
    long long int x=3567345;
    for(int i=0; i<=50;i++){
    	cout<<i<<": "<<x<<endl;
    	x=cuadraMedi(x);
    }
    
    long long int x=1234500012;
    for(int i=0; i<=50;i++){
    	cout<<i<<": "<<x<<endl;
    	x=cuadraMedi(x);
    }
    
    long long int x=4567234902;
    for(int i=0; i<=50;i++){
    	cout<<i<<": "<<x<<endl;
    	x=cuadraMedi(x);
    }
    */
    
    /*
    if(revisarM(7, 5, 24, 32)){
        cout<<"Todo bien"<<endl;
    } else {cout<<"Todo mal"<<endl;}
    */
    
    /*
    if(revisarM(8, 9, 13, 32)){
        cout<<"Todo bien"<<endl;
    } else {cout<<"Todo mal"<<endl;}
    */
    
    /*
    if(revisarM(13, 50, 17, 64)){
        cout<<"Todo bien"<<endl;
    } else {cout<<"Todo mal"<<endl;}
    */
    
     /*
    if(revisarM(15, 8, 16, 100)){
        cout<<"Todo bien"<<endl;
    } else {cout<<"Todo mal"<<endl;}
    */
    
    /*
    if(revisarM(3, 5, 21, 100)){
        cout<<"Todo bien"<<endl;
    } else {cout<<"Todo mal"<<endl;}
    */
    
    /*
    if(revisarM(7, 5, 0, 64)){
        cout<<"Todo bien"<<endl;
    } else {cout<<"Todo mal"<<endl;}
    */
    
    /*
    if(revisarM(9, 11, 0, 128)){
        cout<<"Todo bien"<<endl;
    } else {cout<<"Todo mal"<<endl;}
    */
    
    /*
    if(revisarM(3, 221, 0, 1000)){
        cout<<"Todo bien"<<endl;
    } else {cout<<"Todo mal"<<endl;}
    */
    /*
    if(revisarM(17, 203, 0, 100000)){
        cout<<"Todo bien"<<endl;
    } else {cout<<"Todo mal"<<endl;}
    */
    /*
    if(revisarM(19, 211, 0, 100000000)){
        cout<<"Todo bien"<<endl;
    } else {cout<<"Todo mal"<<endl;}
    */
    /*
    if(revisarM(1, 16, 4, 15)){
        cout<<"Todo bien"<<endl;
    } else {cout<<"Todo mal"<<endl;}
    Este funciona por esto:
    Para numeros entre 0 a 14, solo esta el M= 15 (Por ser los que componen el modulo)
    Para sacar un buen C, se ocupa que el maximo comun divisor de C,M sea 1 (coprimos) 
    15 y 4 son coprimos
    Para sacar un buen a, se ocupa (a-1)mod(factorizacion prima de M) sea 0
    (a-1)mod(3) y (a-1)mod(5), el a que cumple eso es 16
    */
    /*
    if(revisarM(1, 13, 2, 9)){
        cout<<"Todo bien"<<endl;
    } else {cout<<"Todo mal"<<endl;}
    */
    
    /*
    if(revisarM(1, 20, 5, 19)){
        cout<<"Todo bien"<<endl;
    } else {cout<<"Todo mal"<<endl;}
    */
    return 0;
}
