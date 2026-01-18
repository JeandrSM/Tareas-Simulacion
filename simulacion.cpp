#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;

double facto(double m){
    if (!m) return 1.0;
    return m*facto(m-1.0);
}

vector<double> AcuPoisson (){
    double lambda=3.0;
    vector<double> res;
    double acu=0.0;
    double elambda =exp(-lambda);
    for(double i=0.0; i<15.0; i++){
        acu+=(elambda*pow(lambda,i))/facto(i);
        res.push_back(acu);
    }
    return res;
}

int comb(int a, int b){
    return facto(a)/(facto(b)*facto(a-b));
}

vector<double> binomial(int n, double p){
    double acu=0.0;
    vector<double> res;
    for (int i = 0; i <= n; i++)
    {
        acu+=comb(n,i)*pow(p,i)*pow(1-p,n-i);
        res.push_back(acu);
    }
    return res;
    
}


double random01(){
    unsigned seed = high_resolution_clock::now().time_since_epoch().count();
    mt19937 gen(seed);
    uniform_real_distribution<double> numero(0.0, 1.0);
    return numero(gen);
}

//Cliente

int cliente(const vector<double>& acuPois){
    /*
    unsigned seed = high_resolution_clock::now().time_since_epoch().count();
    mt19937 gen(seed);
    poisson_distribution <int> quaso(3);
    return quaso(gen);*/
    double x = random01();
    int inf = -1;
    int sup = 15;
    while(inf+1<sup){
        int mid=(sup+inf)/2;
        if(acuPois[mid]<x){
            inf=mid;
        } else {
            sup=mid;
        }
    }
    return sup;
}

int cantServ(vector<double>& acubino){/*
    unsigned seed = high_resolution_clock::now().time_since_epoch().count();
    mt19937 gen(seed);
    binomial_distribution <int> bino(5, 2.0/5.0);
    return bino(gen);*/
    double x = random01();
    int inf = -1;
    int sup = acubino.size();
    while(inf+1<sup){
        int mid=(sup+inf)/2;
        if(acubino[mid]<x){
            inf=mid;
        } else {
            sup=mid;
        }
    }
    return sup;
}

bool menu (double proba){
    if ((1-proba)<random01())
    {
        return true;
    }
    return false;
}

//Servicios
double cajas (){ //Aqui hay de dos, podemos usar la exponential_distribution o hacerlo como aqui, no se cual sea la buena
    return -2.5*log(1-random01());
}

double refrescos(){
    return -0.75*log(1-random01());
}


//Falta la de freidora (normal Simpsons/tabla)


double pollo(double p){
    double x = random01();
    return log(1.0-x)/log(1.0-p);
}

int postres(vector<double>& acubino){/* Recordar poner bien la proba
    unsigned seed = high_resolution_clock::now().time_since_epoch().count();
    mt19937 gen(seed);
    binomial_distribution <int> bino(5, 2.0/5.0);
    return bino(gen);*/
    double x = random01();
    int inf = -1;
    int sup = acubino.size();
    while(inf+1<sup){
        int mid=(sup+inf)/2;
        if(acubino[mid]<x){
            inf=mid;
        } else {
            sup=mid;
        }
    }
    return sup;
}


int main(){
    vector<double> acuP = binomial(5,0.6);
    for (int i = 0; i < 40; i++)
    {
        }
    
    return 0;
}
