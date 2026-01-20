#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;
static mt19937 generator;
#include <string> 

double MEDIA_CAJA = 0.0;
double MEDIA_REFRE = 0.0;
double MEDIA_FREI = 0.0;
double MEDIA_POST = 0.0;
double MEDIA_POLL = 0.0;

double random01() {
    static random_device rd;
    static mt19937 generador(rd());
    static uniform_real_distribution<double> distribucion(0.0, 1.0);
    return distribucion(generador);
}

double generarTiempoEntreLlegadas(double lambda = 3.0) {
    unsigned seed = high_resolution_clock::now().time_since_epoch().count();
    mt19937 gen(seed);
    poisson_distribution <int> quaso(3);
    return quaso(gen);
}

vector<double> generarLlegadas(double tiempoTotal, double lambda = 3.0) {
    vector<double> llegadas;
    double tiempoActual = 0;
    
    while (tiempoActual < tiempoTotal) {
        double tiempoEntre = generarTiempoEntreLlegadas(lambda);
        tiempoActual += tiempoEntre;
        
        if (tiempoActual < tiempoTotal) {
            llegadas.push_back(tiempoActual);
        }
    }
    
    return llegadas;
}

double duracionCaja(){
    static std::mt19937 generador(std::time(nullptr));
    static std::exponential_distribution<double> distribucion(0.4); 
    
    return distribucion(generador);
}

double duracionRefre(){
    static std::mt19937 generador(std::time(nullptr));
    static std::exponential_distribution<double> distribucion(1.33333333); // λ = 1/0.75
    return distribucion(generador);
}


double duracionFrei() {
    static std::mt19937 generador(std::time(nullptr));
    static std::normal_distribution<double> normal(3.0, 1.0);
    
    // Generar valor normal
    double valor = normal(generador);
    
    // Discretizar a múltiplos de 0.5 minutos
    double discreto = std::round(valor * 2.0) / 2.0;
    
    // Limitar rango razonable
    discreto = std::max(0.5, std::min(discreto, 10.0));
    
    return discreto;
}

double duracionPost() {
    unsigned seed = high_resolution_clock::now().time_since_epoch().count();
    mt19937 gen(seed);
    binomial_distribution <int> bino(5, 2.0/5.0);
    return bino(gen);
} 

double duracionPollo(double p = 0.1) {
    static std::mt19937 generador(std::time(nullptr));
    static std::geometric_distribution<int> geometrica(0.1);  // p = 0.1
    
    // La geométrica da k fracasos antes del primer éxito
    // Para tiempo en minutos: x = k + 1 (al menos 1 minuto)
    int minutos = geometrica(generador);
    
    return static_cast<double>(minutos);
}

int cantProductos(){
    unsigned seed = high_resolution_clock::now().time_since_epoch().count();
    mt19937 gen(seed);
    binomial_distribution <int> bino(5, 2.0/5.0);
    return bino(gen);
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
        // Encontrar el servidor que estará libre más pronto
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
        return  0.3;
    }
    return 0.0;
    
}

vector<double> simulacion(Estacion &puesto, vector<double> llegadas){
    /*cout << "=================================" << puesto.nombre << "===================================" << endl;
    cout << "Número de servidores: " << puesto.servidores.size() << endl;
    cout << "====================================================================" << endl;
    cout << "Llegada\t\tDuracion\tServidor\tSalida\t\tTiempo en Sistema" << endl;
    cout << "====================================================================" << endl;*/
    double mediaEspera = 0.0;
    
    vector<double> salidas;
    
    for(int i = 0; i < llegadas.size(); i++) {
        double llegada = llegadas[i];
        double p = proba(puesto.nombre);
        double tiro = random01();
        if(tiro >= p) {/*cout << "No come, p = " << tiro << endl;*/ continue;}
        int n = 1;
        if(puesto.nombre != "Caja"){
            n = cantProductos();
            //cout << "Pidió " << n << " productos" << endl;
        }

        for(int j = 0; j<n; j++){

            double duracionC = duracion(puesto.nombre);

            pair<double, int> resultado = puesto.procesarCliente(llegada, duracionC);

            double salidaPuesto = resultado.first;
            int serv = resultado.second;

            salidas.push_back(salidaPuesto);
            
            double tiempoSistema = salidaPuesto - llegada;
            mediaEspera += tiempoSistema;

            /*cout << fixed << setprecision(4);
            cout << llegada << "\t\t"
                << duracionC << "\t\t"
                << serv+1 << "\t\t"
                << salidaPuesto << "\t\t"
                << tiempoSistema << endl;*/}
    }
    
    //cout << "====================================================================" << endl;

    if(puesto.nombre == "Caja") MEDIA_CAJA = mediaEspera;
    if(puesto.nombre == "Refrescos") MEDIA_REFRE = mediaEspera;
    if(puesto.nombre == "Freidora") MEDIA_FREI = mediaEspera;
    if(puesto.nombre == "Postres") MEDIA_POST = mediaEspera;
    if(puesto.nombre == "Pollo") MEDIA_POLL = mediaEspera;
    return salidas;

}



int main(){



    int total = 12;
    int estaciones = 5;
    
    // Restamos el mínimo 1 por estación
    int restante = total - estaciones; // 7
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
                           
                        vector<double> salidasRefrescos;
                        vector<double> salidasFreidora;
                        vector<double> salidasPostres;
                        vector<double> salidasPollo;
                        vector<double> llegadas = generarLlegadas(480);
                        vector<double> salidasCaja = simulacion(caja, llegadas);
                        sort(salidasCaja.begin(), salidasCaja.end());

                        
                        salidasRefrescos = simulacion(refrescos, salidasCaja);
                        
                        salidasFreidora = simulacion(freidora, salidasCaja);
                        
                        salidasPostres = simulacion(postres, salidasCaja);
                        
                        salidasPollo = simulacion(pollo, salidasCaja);


                        double sumaTotalEspera =
                                MEDIA_CAJA +
                                MEDIA_REFRE +
                                MEDIA_FREI +
                                MEDIA_POST +
                                MEDIA_POLL
                                ;

                        int totalClientes =
                                salidasCaja.size() +
                                salidasRefrescos.size() +
                                salidasFreidora.size() +
                                salidasPostres.size() +
                                salidasPollo.size();

                        double MEDIA_TOTAL = sumaTotalEspera / totalClientes;
                        mediaConfiguracion += MEDIA_TOTAL;

                    }
                    cont++;
                    mediaConfiguracion /= 1000.0;
                    cout << "Media TOTAL configuracion = "
                        << mediaConfiguracion << endl << endl;
                    mediaMin = min(mediaMin, mediaConfiguracion);

                }
            }
        }
    }

    cout << "Minimo : " mediaMin << " minutos de espera de Media" << endl;
    return 0;
    /*
    Estacion caja(3, "Caja");
    Estacion refrescos(1, "Refrescos");
    Estacion freidora(3, "Freidora");
    Estacion postres(1, "Postres");
    Estacion pollo(4, "Pollo");
    vector<double> salidasRefrescos;
    vector<double> salidasFreidora;
    vector<double> salidasPostres;
    vector<double> salidasPollo;
    vector<double> llegadas = generarLlegadas(480);
    vector<double> salidasCaja = simulacion(caja, llegadas);
    sort(salidasCaja.begin(), salidasCaja.end());


    
    salidasRefrescos = simulacion(refrescos, salidasCaja);
    
    salidasFreidora = simulacion(freidora, salidasCaja);
    
    salidasPostres = simulacion(postres, salidasCaja);
    
    salidasPollo = simulacion(pollo, salidasCaja);


    cout << "Analisis: " << endl;
    cout << "   Caja: " << endl;
    cout << "       Cantidad: " << salidasCaja.size() << endl;
    cout << "       Media de Espera: " << MEDIA_CAJA << endl;

    cout << endl;

    cout << "   Refrescos: " << endl;
    cout << "       Cantidad: " << salidasRefrescos.size() << endl;
    cout << "       Media de Espera: " << MEDIA_REFRE << endl;

    cout << endl;

    cout << "   Freidora: " << endl;
    cout << "       Cantidad: " << salidasFreidora.size() << endl;
    cout << "       Media de Espera: " << MEDIA_FREI << endl;

    cout << endl;

    cout << "   Postres: " << endl;
    cout << "       Cantidad: " << salidasPostres.size() << endl;
    cout << "       Media de Espera: " << MEDIA_POST << endl;
    cout << endl;

    cout << "   Pollo: " << endl;
    cout << "       Cantidad: " << salidasPollo.size() << endl;
    cout << "       Media de Espera: " << MEDIA_POLL << endl;
    

    

    return 0;*/
}
