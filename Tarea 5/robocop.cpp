#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;

double MEDIA_CAJA = 0.0;
double MEDIA_REFRE = 0.0;
double MEDIA_FREI = 0.0;
double MEDIA_POST = 0.0;
double MEDIA_POLL = 0.0;

// ============ FUNCIONES DE SIMULACION.CPP ============

double facto(double m){
    if (!m) return 1.0;
    return m*facto(m-1.0);
}

vector<double> AcuPoisson(){
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
    for (int i = 0; i <= n; i++){
        acu+=comb(n,i)*pow(p,i)*pow(1-p,n-i);
        res.push_back(acu);
    }
    return res;
}

double random01(){
    static mt19937 gen(random_device{}());
    static uniform_real_distribution<double> dist(0.0,1.0);
    return dist(gen);
}

double normalPDF(double x){
    double exponente = -0.5 * ((x-3.0)*(x-3.0));
    return (1.0/(sqrt(2.0*M_PI)))*exp(exponente);
}

double simpson(double a, double b, int n){
    double h = (b-a)/n;
    double suma = normalPDF(a)+normalPDF(b);
    for(int i = 1; i<n; i+=2){
        suma += 4.0 * normalPDF(a+i*h);
    }
    for (int i = 2; i < n ; i+=2){
        suma += 2.0 * normalPDF(a+i*h);
    }
    return (h/3.0)*suma;
}

vector<double> acumNormal(){
    vector<double> res;
    double proba=0.0;
    for (double i = -3.0; i < 9.0; i+=0.001){
        proba += simpson(i, i+0.001, 10);
        res.push_back(proba);
    }
    return res;
}

double freidora(const vector<double>& acuN) {
    double u = random01();
    int inf = -1;
    int sup = acuN.size();

    while (inf + 1 < sup) {
        int mid = (inf + sup) / 2;
        if (acuN[mid] < u) {
            inf = mid;
        } else {
            sup = mid;
        }
    }

    if (inf < 0) {
        return 0.0;
    }

    double probInf = acuN[inf];
    double probSup = acuN[sup];
    double t = (u - probInf)/(probSup - probInf);

    return -3.0+(inf+t)*0.001;
}

int cliente(const vector<double>& acuPois){
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

int cantServ(const vector<double>& acubino){
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

double cajas(){
    return -2.5*log(1-random01());
}

double refrescos(){
    return -0.75*log(1-random01());
}

double pollo(double p){
    double x = random01();
    return log(1.0-x)/log(1.0-p);
}

int postres(const vector<double>& acubino){
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

// ============ FIN FUNCIONES DE SIMULACION.CPP ============

// Variables globales para las distribuciones acumuladas
vector<double> acuPoisson_global;
vector<double> acuNormal_global;
vector<double> acuBinomial_productos_global;
vector<double> acuBinomial_postres_global;

int generarTiempoEntreLlegadas() {
    return cliente(acuPoisson_global);
}

vector<double> generarLlegadas(double tiempoTotal) {
    vector<double> llegadas;
    double tiempoActual = 0;
    
    while (tiempoActual < tiempoTotal) {
        double tiempoEntre = generarTiempoEntreLlegadas();
        tiempoActual += tiempoEntre;
        
        if (tiempoActual < tiempoTotal) {
            llegadas.push_back(tiempoActual);
        }
    }
    
    return llegadas;
}

double duracionCaja(){
    return cajas();
}

double duracionRefre(){
    return refrescos();
}

double duracionFrei() {
    return freidora(acuNormal_global);
}

double duracionPost() {
    return postres(acuBinomial_postres_global);
} 

double duracionPollo(double p = 0.1) {
    return pollo(p);
}

int cantProductos(){
    return cantServ(acuBinomial_productos_global);
}

struct Servidor {
    double tiempoOcupadoHasta; 
    int id;                     
    
    Servidor(int i) : tiempoOcupadoHasta(0.0), id(i) {}
    
    bool estaLibre(double tiempoActual) const {
        return tiempoOcupadoHasta <= tiempoActual;
    }
};

struct Estacion {
    vector<Servidor> servidores; 
    string nombre;
    
    Estacion(int n, string nom) : nombre(nom) {
        for(int i = 0; i < n; i++) {
            servidores.push_back(Servidor(i));
        }
    }
    
    pair<double,int> procesarCliente(double llegada, double duracion) {
        int idx_mas_pronto = 0;
        for(int i = 1; i < servidores.size(); i++) {
            if(servidores[i].tiempoOcupadoHasta < servidores[idx_mas_pronto].tiempoOcupadoHasta) {
                idx_mas_pronto = i;
            }
        }
        
        Servidor& servidor = servidores[idx_mas_pronto];
        double inicio_servicio = max(llegada, servidor.tiempoOcupadoHasta);
        double fin = inicio_servicio + duracion;
        
        servidor.tiempoOcupadoHasta = fin;
        
        return {fin, servidor.id};
    }
};

double duracion(const string& puesto) {
    if (puesto == "Caja") {
        return duracionCaja();
    } 
    if (puesto == "Refrescos") {
        return duracionRefre();
    }
    if (puesto == "Freidora") {
        return duracionFrei();
    }
    if (puesto == "Postres") {
        return duracionPost();
    }
    if (puesto == "Pollo") {
        return duracionPollo();
    }
    return 0.0;
}

double proba(const string& puesto) {
    if (puesto == "Caja") {
        return 1.00;
    } 
    if (puesto == "Refrescos") {
        return 0.9;
    }
    if (puesto == "Freidora") {
        return 0.7;
    }
    if (puesto == "Postres") {
        return 0.25;
    }
    if (puesto == "Pollo") {
        return 0.3;
    }
    return 0.0;
}

vector<double> simulacion(Estacion &puesto, vector<double> llegadas){
    double mediaEspera = 0.0;
    vector<double> salidas;
    
    for(int i = 0; i < llegadas.size(); i++) {
        double llegada = llegadas[i];
        double p = proba(puesto.nombre);
        double tiro = random01();
        if(tiro >= p) continue;
        
        int n = 1;
        if(puesto.nombre != "Caja"){
            n = cantProductos();
        }

        for(int j = 0; j<n; j++){
            double duracionC = duracion(puesto.nombre);
            pair<double, int> resultado = puesto.procesarCliente(llegada, duracionC);
            double salidaPuesto = resultado.first;
            int serv = resultado.second;

            salidas.push_back(salidaPuesto);
            double tiempoSistema = salidaPuesto - llegada;
            mediaEspera += tiempoSistema;
        }
    }

    if(puesto.nombre == "Caja") MEDIA_CAJA = mediaEspera;
    if(puesto.nombre == "Refrescos") MEDIA_REFRE = mediaEspera;
    if(puesto.nombre == "Freidora") MEDIA_FREI = mediaEspera;
    if(puesto.nombre == "Postres") MEDIA_POST = mediaEspera;
    if(puesto.nombre == "Pollo") MEDIA_POLL = mediaEspera;
    
    return salidas;
}

int main(){
    // Inicializar distribuciones acumuladas globales
    acuPoisson_global = AcuPoisson();
    acuNormal_global = acumNormal();
    acuBinomial_productos_global = binomial(5, 0.4); // 2/5 = 0.4
    acuBinomial_postres_global = binomial(5, 0.4);

    int total = 12;
    int estaciones = 5;
    int restante = total - estaciones;
    double mediaMin = 99;
    int cont = 1;
    
    for (int cajaC = 0; cajaC <= restante; cajaC++) {
        for (int refrescosC = 0; refrescosC <= restante - cajaC; refrescosC++) {
            for (int freidoraC = 0; freidoraC <= restante - cajaC - refrescosC; freidoraC++) {
                for (int postresC = 0; postresC <= restante - cajaC - refrescosC - freidoraC; postresC++) {
    
                    int polloC = restante - cajaC - refrescosC - freidoraC - postresC;
                    cout << cont << ". " <<
                        "Caja: " << (cajaC + 1) <<
                        ", Refrescos: " << (refrescosC + 1) <<
                        ", Freidora: " << (freidoraC + 1) <<
                        ", Postres: " << (postresC + 1) <<
                        ", Pollo: " << (polloC + 1)
                     << endl;

                    double mediaConfiguracion = 0.0;
                    for(int i = 0; i<1000; i++){
                        Estacion caja(cajaC+1, "Caja");
                        Estacion refrescos(refrescosC+1, "Refrescos");
                        Estacion freidora(freidoraC+1, "Freidora");
                        Estacion postres(postresC+1, "Postres");
                        Estacion pollo(polloC+1, "Pollo");
                           
                        vector<double> llegadas = generarLlegadas(480);
                        vector<double> salidasCaja = simulacion(caja, llegadas);
                        sort(salidasCaja.begin(), salidasCaja.end());

                        vector<double> salidasRefrescos = simulacion(refrescos, salidasCaja);
                        vector<double> salidasFreidora = simulacion(freidora, salidasCaja);
                        vector<double> salidasPostres = simulacion(postres, salidasCaja);
                        vector<double> salidasPollo = simulacion(pollo, salidasCaja);

                        double sumaTotalEspera = MEDIA_CAJA + MEDIA_REFRE + MEDIA_FREI + MEDIA_POST + MEDIA_POLL;
                        int totalClientes = salidasCaja.size() + salidasRefrescos.size() + 
                                          salidasFreidora.size() + salidasPostres.size() + salidasPollo.size();

                        double MEDIA_TOTAL = sumaTotalEspera / totalClientes;
                        mediaConfiguracion += MEDIA_TOTAL;
                    }
                    
                    cont++;
                    mediaConfiguracion /= 1000.0;
                    cout << "Media TOTAL configuracion = " << mediaConfiguracion << endl << endl;
                    mediaMin = min(mediaMin, mediaConfiguracion);
                }
            }
        }
    }

    cout << "Minimo : " << mediaMin << " minutos de espera de Media" << endl;
    return 0;
}
