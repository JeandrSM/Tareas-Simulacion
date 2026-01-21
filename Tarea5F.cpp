#include <bits/stdc++.h>
using namespace std;

double jornada = 480.00;

static vector<double> binomialPostres;
static vector<double> binomialPedidos;
static vector<double> poisson;
static vector<double> normal;
static vector<double> geometri;


double facto(double m){
    if(!m) return 1.0;
    return m * facto(m - 1.0);
}

vector<double> AcuPoisson(){
    double lambda = 3.0;
    vector<double> res;
    double acu = 0.0;
    double elambda = exp(-lambda);
    for(int i = 0; i < 15; i++){
        acu += (elambda * pow(lambda, i)) / facto(i);
        res.push_back(acu);
    }
    return res;
}

int comb(int a, int b){
    return facto(a) / (facto(b) * facto(a - b));
}

vector<double> binomial(int n, double p){
    vector<double> res;
    double acu = 0.0;
    for(int i = 0; i <= n; i++){
        acu += comb(n, i) * pow(p, i) * pow(1 - p, n - i);
        res.push_back(acu);
    }
    return res;
}

vector<double> acuGeo(){
    vector<double> res;
    double acu=0.0;
    for (int i = 1; i < 50; i++)
    {
        acu+= pow(0.9, i-1)*0.1;
        res.push_back(acu);
    }
    return res;
}
double random01(){
    static mt19937 gen(random_device{}());
    static uniform_real_distribution<double> dist(0.0, 1.0);
    return dist(gen);
}

//NORMAL FREIDORA 

double normalPDF(double x){
    double e = -0.5 * ((x - 3.0) * (x - 3.0));
    return (1.0 / sqrt(2.0 * M_PI)) * exp(e);
}

double simpson(double a, double b, int n){
    double h = (b - a) / n;
    double suma = normalPDF(a) + normalPDF(b);
    for(int i = 1; i < n; i += 2) suma += 4.0 * normalPDF(a + i * h);
    for(int i = 2; i < n; i += 2) suma += 2.0 * normalPDF(a + i * h);
    return (h / 3.0) * suma;
}

vector<double> acumNormal(){
    vector<double> res;
    double proba = 0.0;
    for(double i = -3.0; i < 9.0; i += 0.001){
        proba += simpson(i, i + 0.001, 10);
        res.push_back(proba);
    }
    return res;
}

// ESTRUCTURAS

struct Cliente{
    double llegada;
    double salidaCaja = 0.0;
    int nProductos;
    double salidaFinal = 0.0;
    bool _refrescos = false;
    bool _freidora = false;
    bool _postres = false;
    bool _pollo = false;

    bool aEstacion(string puesto){
            if(puesto == "Refrescos") return _refrescos;
            if(puesto == "Freidora") return _freidora;
            if(puesto == "Postres") return _postres;
            if(puesto == "Pollo") return _pollo;
            return false;
    }
};

struct Servidor{
    double ocupadoHasta = 0.0;
    
};

struct Estacion{
    vector<Servidor> servidores;
    string nombre;
    double tiempoOcupado = 0.0;

    Estacion(int n, string nom): nombre(nom), servidores(n) {}

    pair<double,int> procesar(double llegada, double dur){
        int idx = 0;
        for(int i = 1; i < servidores.size(); i++)
            if(servidores[i].ocupadoHasta < servidores[idx].ocupadoHasta)
                idx = i;

        double ini = max(llegada, servidores[idx].ocupadoHasta);
        if(ini>=jornada || (ini+dur)>= jornada) servidores[idx].ocupadoHasta = jornada;
        else servidores[idx].ocupadoHasta = ini + dur;

        return {servidores[idx].ocupadoHasta, idx};
    }
};

//Duraciones

double duracionCaja(){ return -2.5 * log(1 - random01()); }
double duracionRefre(){ return -0.75 * log(1 - random01()); }

double duracionFrei(const vector<double>& acuN){
    double u = random01();
    int inf = -1, sup = acuN.size();
    while(inf + 1 < sup){
        int mid = (inf + sup) / 2;
        if(acuN[mid] < u) inf = mid;
        else sup = mid;
    }
    double t = (u - acuN[inf]) / (acuN[sup] - acuN[inf]);
    double res = -3.0 + (inf + t) * 0.001;
    return max(0.0, res);
}

double duracionPost(vector<double>& acubino){
    double x = random01();
    int inf = -1, sup = acubino.size();
    while(inf + 1 < sup){
        int mid = (sup + inf) / 2;
        if(acubino[mid] < x) inf = mid;
        else sup = mid;
    }
    return sup;
}


double duracionPollo(vector<double>& acuGeos){
    double x = random01();
    int inf = -1, sup = acuGeos.size();
    while(inf + 1 < sup){
        int mid = (sup + inf) / 2;
        if(acuGeos[mid] < x) inf = mid;
        else sup = mid;
    }
    return sup;
}




double duracion(const string& puesto){
    if(puesto == "Caja") return duracionCaja();
    if(puesto == "Refrescos") return duracionRefre();
    if(puesto == "Freidora") return duracionFrei(normal);
    if(puesto == "Postres") return duracionPost(binomialPostres);
    if(puesto == "Pollo") return duracionPollo(geometri);
    return 0.0;
}

double proba(const string& puesto){
    if(puesto == "Caja") {return 1.0;}
    if(puesto == "Refrescos") {return 0.9;}
    if(puesto == "Freidora") {return 0.7;}
    if(puesto == "Postres") {return 0.25;}
    if(puesto == "Pollo") {return 0.3;}
    return 0.0;
}

int cantProductos(vector<double>& acubino){
    double x = random01();
    int inf = -1, sup = acubino.size();
    while(inf + 1 < sup){
        int mid = (sup + inf) / 2;
        if(acubino[mid] < x) inf = mid;
        else sup = mid;
    }
    return max(1, sup);
}

//Simulacion


void inicializarTablas(){
    binomialPostres = binomial(5, 0.6);
    binomialPedidos = binomial(5, 0.4);
    poisson = AcuPoisson();
    normal = acumNormal();
    geometri = acuGeo();
}


double generarTiempoEntreLlegadas(const vector<double>& acuPois){
    double x = random01();
    int inf = -1, sup = acuPois.size();
    while(inf + 1 < sup){
        int mid = (sup + inf) / 2;
        if(acuPois[mid] < x) inf = mid;
        else sup = mid;
    }
    return sup;
}



void simularCaja(Estacion& caja, vector<Cliente>& clientes){
    for(Cliente& c : clientes){
        c.nProductos = cantProductos(binomialPedidos); 
        c._refrescos = random01() <= proba("Refrescos"); 
        c._freidora = random01() <= proba("Freidora") ; 
        c._postres = random01() <= proba("Postres") ; 
        c._pollo = random01() <= proba("Pollo") ; 
        double dur = duracion("Caja");
        caja.tiempoOcupado += dur;

        auto [salida, srv] = caja.procesar(c.llegada, dur);
        c.salidaCaja = salida;
        c.salidaFinal = salida;
    }
}

void simularEstacion(Estacion& est, vector<Cliente>& clientes){
    for(Cliente& c : clientes){
        if(!c.aEstacion(est.nombre)) continue;
        for(int i = 0; i < c.nProductos; i++){
            double dur = duracion(est.nombre);
            if(c.salidaFinal >= jornada) continue;;
            
            auto [salida, srv] =
                est.procesar(c.salidaCaja, dur);
            if(salida >= jornada) continue;
            c.salidaFinal = max(c.salidaFinal, salida);

            est.tiempoOcupado += dur;
  
        } 
    } 

}

void simularCajaUNO(Estacion& caja, vector<Cliente>& clientes){ 

    ofstream file("Caja.csv");
    file << "Llegada;Duracion;Servidor;Salida;TiempoSistema\n";

    cout << "\n==================== CAJA ====================\n"; 
    cout << "Llegada\t\tDuracion\tSalida\t\tTiempo Sistema\n"; 
    cout << "------------------------------------------------\n"; 
    cout << fixed << setprecision(4); 

    for(Cliente& c : clientes){
        c.nProductos = cantProductos(binomialPedidos); 

        c._refrescos = random01() <= proba("Refrescos"); 
        c._freidora = random01() <= proba("Freidora") ; 
        c._postres = random01() <= proba("Postres") ; 
        c._pollo = random01() <= proba("Pollo") ; 

        double dur = duracion("Caja");
        caja.tiempoOcupado += dur;
        auto [salida, srv] = caja.procesar(c.llegada, dur);
        c.salidaCaja = salida;
        c.salidaFinal = salida;

        file << c.llegada << ";"
             << dur << ";"
             << srv+1 << ";"
             << salida << ";"
             << (salida - c.llegada) << "\n";

        cout << c.llegada << "\t\t" 
             << dur << "\t\t" 
             << srv+1 << "\t\t"
             << salida << "\t\t" 
             << (salida - c.llegada) << "\n"; 
    } 

    file.close();
}


void simularEstacionUNO(Estacion& est, vector<Cliente>& clientes){

    string nombreArchivo = est.nombre + ".csv";
    ofstream file(nombreArchivo);
    file << "SalidaCaja;Duracion;Servidor;Salida;TiempoSistema\n";

    cout << "\n==================== " << est.nombre << " ====================\n"; 
    cout << "Salida Caja\tDuracion\tServidor\tSalida\t\tTiempo Sistema\n"; 
    cout << "-------------------------------------------------------------\n"; 
    cout << fixed << setprecision(4); 

    for(Cliente& c : clientes){
        if(!c.aEstacion(est.nombre)) continue;
        for(int i = 0; i < c.nProductos; i++){
            double dur = duracion(est.nombre);
            if(c.salidaFinal >= jornada) continue;;
            
            auto [salida, srv] =
                est.procesar(c.salidaCaja, dur);
            if(salida >= jornada) continue;
            c.salidaFinal = max(c.salidaFinal, salida);

            est.tiempoOcupado += dur;

            file << c.salidaCaja << ";"
                 << dur << ";"
                 << srv+1 << ";"
                 << salida << ";"
                 << (salida - c.llegada) << "\n";

            cout << c.salidaCaja << "\t\t" 
                 << dur << "\t\t" 
                 << srv+1 << "\t\t"
                 << salida << "\t\t" 
                 << (salida - c.llegada) << "\n"; 
        } 
    } 

    file.close();
}


double utilizacion(const Estacion& est, double T){
    
    return est.tiempoOcupado / (T * est.servidores.size());
}



void imprimirClientes(const vector<Cliente>& clientes){
    cout << "\n==================== CLIENTES ====================\n";
    cout << "ID  Llegada   Prod  Ref   Frei  Post   Pollo  SalCaja    SalFinal  T_Sistema\n";
    cout << "--------------------------------------------------------------------\n";

    cout << fixed << setprecision(3);

    int id = 1;

    int cntRef = 0;
    int cntFrei = 0;
    int cntPost = 0;
    int cntPollo = 0;

    for(const Cliente& c : clientes){

        if(c._refrescos) {cntRef += c.nProductos; }
        if(c._freidora)  {cntFrei += c.nProductos; }
        if(c._postres)   {cntPost += c.nProductos; }
        if(c._pollo)     {cntPollo += c.nProductos; }

        cout << setw(2) << id++ << "  "
             << setw(7) << c.llegada << "  "
             << setw(4) << c.nProductos << "   "
             << setw(3) << (c._refrescos ? "Si" : "No") << "  "
             << setw(4) << (c._freidora ? "Si" : "No") << "  "
             << setw(4) << (c._postres  ? "Si" : "No") << "   "
             << setw(5) << (c._pollo    ? "Si" : "No") << "   "
             << setw(7) << c.salidaCaja << "   "
             << setw(8) << c.salidaFinal << "   "
             << setw(9) << (c.salidaFinal - c.llegada)
             << "\n";
    }

    cout << "\n==================== RESUMEN ====================\n";
    cout << "Total clientes: " << clientes.size() << "\n";
    cout << "Refrescos : " << cntRef   << "\n";
    cout << "Freidora  : " << cntFrei  << "\n";
    cout << "Postres   : " << cntPost  << "\n";
    cout << "Pollo     : " << cntPollo << "\n";
}


void hacerUno(int a, int b, int c, int d, int e){   
    const int REPETICIONES = 1;

    vector<double> mediasCorrida;
    vector<double> varianzasCorrida;

    

        vector<Cliente> clientes; 
        double t = 0.0; 

        while(t < jornada){ 
            t += generarTiempoEntreLlegadas(poisson); 
            if(t >= jornada) break; 
            Cliente c; 
            c.llegada = t; 
            clientes.push_back(c); 
        }

        Estacion caja(a, "Caja"); 
        Estacion ref(b, "Refrescos"); 
        Estacion frei(c, "Freidora"); 
        Estacion post(d, "Postres"); 
        Estacion pollo(e, "Pollo"); 

        simularCajaUNO(caja, clientes); 

        sort(clientes.begin(), clientes.end(), 
        [](const Cliente& a, const Cliente& b)
        { return a.salidaCaja < b.salidaCaja; });

        simularEstacionUNO(ref, clientes); 
        simularEstacionUNO(frei, clientes); 
        simularEstacionUNO(post, clientes); 
        simularEstacionUNO(pollo, clientes);

        double suma = 0.0;
        for(auto& c : clientes)
            suma += c.salidaFinal - c.llegada;

        double mediaCorrida = suma / clientes.size();
        mediasCorrida.push_back(mediaCorrida);

        double var = 0.0;
        for(auto& c : clientes){
            double w = c.salidaFinal - c.llegada;
            var += (w - mediaCorrida) * (w - mediaCorrida);
        }
        var /= clientes.size();
        varianzasCorrida.push_back(var);
    

    double mediaConfig = 0.0;
    for(double x : mediasCorrida)
        mediaConfig += x;
    mediaConfig /= mediasCorrida.size();

    double varianza = 0.0;
    for(double v : varianzasCorrida)
        varianza += v;
    varianza /= varianzasCorrida.size();

    cout << "Media " << mediaConfig << endl;
    cout << "Varianza " << varianza << endl;
    cout << "pi = Caja " << utilizacion(caja,jornada) << endl;
    cout << "pi = Refrescos " << utilizacion(ref,jornada) << endl;
    cout << "pi = Freidora " << utilizacion(frei,jornada) << endl;
    cout << "pi = Postres " << utilizacion(post,jornada) << endl;
    cout << "pi = Pollo " << utilizacion(pollo,jornada) << endl;
}


int main(){

    inicializarTablas();
    cout<<"Ingrese 1 para Simulacion completa"<<endl<<"Ingrese 2 para Simular una configuracion"<<endl;
    int a;
    cin>>a;
    if(a==2){
    cout<<"Ingresar la configuracion en orden Caja, Refrescos, Freidora, Postres y Pollo"<<endl;
    int p1;
    int p2;
    int p3;
    int p4;
    int p5;
    cin>>p1>>p2>>p3>>p4>>p5;
    hacerUno(p1,p2,p3,p4,p5);} else {
    const int TOTAL_SERVIDORES = 12;
    const int REPETICIONES = 1000;

    // Caja, Ref, Frei, Post, Pollo, Media, Var,
    // piCaja, piRef, piFrei, piPost, piPollo
    vector<tuple<
        int,int,int,int,int,
        double,double,
        double,double,double,double,double
    >> resultados;

    int contador = 1;

    for(int cCaja = 1; cCaja <= TOTAL_SERVIDORES - 4; cCaja++)
    for(int cRef = 1; cRef <= TOTAL_SERVIDORES - cCaja - 3; cRef++)
    for(int cFrei = 1; cFrei <= TOTAL_SERVIDORES - cCaja - cRef - 2; cFrei++)
    for(int cPost = 1; cPost <= TOTAL_SERVIDORES - cCaja - cRef - cFrei - 1; cPost++)
    {
        int cPollo = TOTAL_SERVIDORES - (cCaja + cRef + cFrei + cPost);
        if(cPollo < 1) continue;

        vector<double> mediasCorrida;
        vector<double> varianzasCorrida;

        double utilCaja = 0.0;
        double utilRef = 0.0;
        double utilFrei = 0.0;
        double utilPost = 0.0;
        double utilPollo = 0.0;

        for(int rep = 0; rep < REPETICIONES; rep++){

            vector<Cliente> clientes;
            double t = 0.0;

            while(t < jornada){
                t += generarTiempoEntreLlegadas(poisson);
                if(t >= jornada) break;

                Cliente c;
                c.llegada = t;
                c.nProductos = cantProductos(binomialPedidos);
                clientes.push_back(c);
            }

            Estacion caja(cCaja, "Caja");
            Estacion ref(cRef, "Refrescos");
            Estacion frei(cFrei, "Freidora");
            Estacion post(cPost, "Postres");
            Estacion pollo(cPollo, "Pollo");

            simularCaja(caja, clientes);

            sort(clientes.begin(), clientes.end(),
                [](const Cliente& a, const Cliente& b){
                    return a.salidaCaja < b.salidaCaja;
                });

            simularEstacion(ref, clientes);
            simularEstacion(frei, clientes);
            simularEstacion(post, clientes);
            simularEstacion(pollo, clientes);

            double suma = 0.0;
            for(auto& c : clientes)
                suma += c.salidaFinal - c.llegada;

            double mediaCorrida = suma / clientes.size();
            mediasCorrida.push_back(mediaCorrida);

            double var = 0.0;
            for(auto& c : clientes){
                double w = c.salidaFinal - c.llegada;
                var += (w - mediaCorrida) * (w - mediaCorrida);
            }
            var /= clientes.size();
            varianzasCorrida.push_back(var);

            utilCaja  += utilizacion(caja, jornada);
            utilRef   += utilizacion(ref, jornada);
            utilFrei  += utilizacion(frei, jornada);
            utilPost  += utilizacion(post, jornada);
            utilPollo += utilizacion(pollo, jornada);
        }

        double mediaConfig = 0.0;
        for(double x : mediasCorrida)
            mediaConfig += x;
        mediaConfig /= mediasCorrida.size();

        double varianza = 0.0;
        for(double v : varianzasCorrida)
            varianza += v;
        varianza /= varianzasCorrida.size();

        utilCaja  /= REPETICIONES;
        utilRef   /= REPETICIONES;
        utilFrei  /= REPETICIONES;
        utilPost  /= REPETICIONES;
        utilPollo /= REPETICIONES;

        cout << contador++ << ". "
             << "Caja " << cCaja
             << " Ref " << cRef
             << " Frei " << cFrei
             << " Post " << cPost
             << " Pollo " << cPollo << endl
             << "   => Media = " << fixed << setprecision(4) << mediaConfig << endl
             << "   => Var   = " << fixed << setprecision(4) << varianza << endl
             << "   pi: Caja =" << utilCaja << endl
             << "       Ref  =" << utilRef << endl
             << "       Frei =" << utilFrei << endl
             << "       Post =" << utilPost << endl
             << "       Pollo=" << utilPollo << endl
             << endl;

        resultados.push_back({
            cCaja, cRef, cFrei, cPost, cPollo,
            mediaConfig, varianza,
            utilCaja, utilRef, utilFrei, utilPost, utilPollo
        });
    }

    sort(resultados.begin(), resultados.end(),
        [](const auto& a, const auto& b){
            return get<5>(a) < get<5>(b);
        });

    cout << "\n===== RESUMEN =====\n";
    cout << "Caja Ref Frei Post Pollo | Media   Var    "
         << "piCaja piRef piFrei piPost piPollo\n";
    cout << "-------------------------------------------------------------\n";

    for(const auto& r : resultados){
        cout << setw(4) << get<0>(r) << " "
             << setw(4) << get<1>(r) << " "
             << setw(4) << get<2>(r) << " "
             << setw(4) << get<3>(r) << " "
             << setw(5) << get<4>(r) << " | "
             << fixed << setprecision(4)
             << setw(7) << get<5>(r) << " "
             << setw(7) << get<6>(r) << " "
             << fixed << setprecision(2) 
             << setw(6) << get<7>(r) << " "
             << setw(6) << get<8>(r) << " "
             << setw(7) << get<9>(r) << " "
             << setw(7) << get<10>(r) << " "
             << setw(7) << get<11>(r)
             << "\n";
        }
    }
    return 0;
}

