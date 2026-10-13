#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <string>
#include <map>
#include <limits>
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


// Prueba de Promedio
string pruebaPromedioC(string nombre);
string pruebaPromedioD(string nombre, int rango);

// Prueba de Varianza
void varianza(int rango, string nombre);

// Prueba de Corridas
string pruebaCorrida(string nombre);

// Prueba de Huecos con Dígitos
void huecos(int rango, string nombre);

// Prueba de Huecos con Números
string pruebaHuecosNumeC(string nombre);
string pruebaHuecosNumeD(string nombre, int k, int sup, int inf);

// Prueba de Poker
void poker(int rango, string nombre);
void pokerDecimal(string nombre);

// Prueba de Series
string pruebaSeriesC(string nombre);
string pruebaSeriesD(string nombre, int k);

// Función auxiliar para probabilidades de poker
void probabili(int rango, double prob[7]);

// ==================== IMPLEMENTACIONES ====================

// Función para probabilidades teóricas de poker
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

// ==================== PRUEBA DE PROMEDIO ====================

string pruebaPromedioC(string nombre){
    double resultado=0.0;
    double nume;
    double mu=0.5;
    double varianza = sqrt(1.0/12.0); 
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
    cout<<"El z0 es :"<<zO<<endl;
    if(abs(zO)<= 1.96){
        return "Si cumple con esta Prueba Promedio";
    } else {return "No cumple con esta prueba Promedio";}
}

string pruebaPromedioD(string nombre, int rango){
    double resultado=0.0;
    double nume;
    double mu=(rango+1.0)/(2.0);
    double varianza = sqrt(((rango*rango)-1.0)/12.0); 
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
    cout<<"Z Observado = "<<zO<<endl;
    if(abs(zO)<= 1.96){
        return "Si cumple con esta Prueba Promedio";
    } else {return "No cumple con esta prueba Promedio";}
}

// ==================== PRUEBA DE VARIANZA ====================

void varianza(int rango, string nombreArchivo){
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

    double varT = 0.0;
    double men = 997229.05853;
    double may = 1002772.70008;
    switch (rango)
    {
    case 10:
        
        varT = varianzas[0];
        break;
    case 4:
    
        varT = varianzas[2];
        break;

    case 6:
        varT = varianzas[1];
        break;

    case 8:
        varT = varianzas[3];
        break;

    case 20:
        varT = varianzas[4];
        break;
    }
    ifstream archivo(nombreArchivo);  

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

    cout << "Prueba de Varianza de " << rango << endl;
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

// ==================== PRUEBA DE CORRIDAS ====================

string pruebaCorrida(string nombre){
    double memo;
    double nume;
    int simbolo = 2;
    double h=1.0;
    ifstream archivo(nombre);
    if (!archivo) {
        std::cout << "No se pudo abrir el archivo\n";
        return "malo";
    }
    archivo >> nume;
    memo=nume;
    while(archivo >> nume){
        if(simbolo == 2){
            if(memo<=nume){
                simbolo=1;
            } else {
                simbolo=-1;
            }
        }
        if(simbolo == 1 && memo>nume){
            simbolo=-1;
            h++;
        }
        if(simbolo == -1 && memo<nume){
            simbolo=1;
            h++;
        }
        memo=nume;
    }
    archivo.close();
    double espe = (2.0*1000000.0 - 1.0)/3.0;
    double varianza = sqrt((16.0*1000000.0-29.0)/90.0);
    double zO = (h-espe)/varianza;
    cout << fixed << setprecision(10)<<"El z0 "<<zO<<" Esperanza "<<espe<<" Varianza "<<varianza<<endl;
    if(abs(zO)<= 1.96){
        return "Si cumple con esta Prueba Corrida";
    } else {return "No cumple con esta prueba Corrida";}
}

// ==================== PRUEBA DE HUECOS CON DIGITOS ====================

void huecos(int rango, string nombre) {

    double chi2_critico = 16.9190;
    double proba[11];

    switch (rango) {
    case 10:
        chi2_critico = 16.91898;
        proba[0]=0.1; proba[1]=0.09; proba[2]=0.081; proba[3]=0.0729;
        proba[4]=0.06561; proba[5]=0.059049; proba[6]=0.0531441;
        proba[7]=0.04782969; proba[8]=0.043046721; proba[9]=0.0387420489;
        break;

    case 4:
        chi2_critico = 7.81473;
        proba[0]=0.25; proba[1]=0.1875; proba[2]=0.140625;
        proba[3]=0.10546875; proba[4]=0.0791015625;
        proba[5]=0.0593261719; proba[6]=0.0444946289;
        proba[7]=0.0333709717; proba[8]=0.0250282288;
        proba[9]=0.0187711716;
        break;

    case 6:
        chi2_critico = 11.07050;
        proba[0]=0.1666666667; proba[1]=0.1388888889;
        proba[2]=0.1157407407; proba[3]=0.0964506173;
        proba[4]=0.0803755144; proba[5]=0.0669795953;
        proba[6]=0.0558163294; proba[7]=0.0465136079;
        proba[8]=0.0387613399; proba[9]=0.0323011166;
        break;

    case 8:
        chi2_critico = 14.06714;
        proba[0]=0.125; proba[1]=0.109375; proba[2]=0.095703125;
        proba[3]=0.0837402344; proba[4]=0.0732727051;
        proba[5]=0.0641136169; proba[6]=0.0560994148;
        proba[7]=0.0490870149; proba[8]=0.0429511391;
        proba[9]=0.0375822467;
        break;
    
    case 20: 
        chi2_critico = 16.91898;  
        
        proba[0] = 0.1;    proba[1] = 0.237253;  
        proba[2] = 0.11;    proba[3] = 0.07565; 
        proba[4] = 0.051;    proba[5] =0.040; 
        proba[6] = 0.032;    proba[7] = 0.0275;  
        proba[8] = 0.0245;    proba[9] = 0.0245;  
        proba[10] = 1;
        for(int i = 0; i<10;i++){
            proba[10] -= proba[i];
        }  
        break;
    }

    proba[10] = 1.0;
    for (int i = 0; i < 10; i++) proba[10] -= proba[i];

    ifstream archivoEntrada(nombre);
    if (!archivoEntrada) {
        cerr << "Error al abrir el archivo de entrada: " << nombre << endl;
        return;
    }

    vector<string> datos;
string linea;

while (getline(archivoEntrada, linea)) {
    linea.erase(remove_if(linea.begin(), linea.end(), ::isspace), linea.end());
    if (linea.empty()) continue;
    
    stringstream ss(linea);
    double valor;
    ss >> valor;  
    
    if (ss.fail()) {
        cerr << "Error al convertir: " << linea << endl;
        continue;
    }
    
    // Convertir de vuelta a string sin notación científica
    stringstream ss2;
    ss2 << fixed << setprecision(20) << valor;
    
    string num_str = ss2.str();
    
    // Remover el "0." inicial si existe
    if (num_str.size() >= 2 && num_str[0] == '0' && num_str[1] == '.') {
        num_str = num_str.substr(2);
    }
    
 
    size_t pos = num_str.find_last_not_of('0');
    if (pos != string::npos && num_str[pos] == '.') {
        num_str = num_str.substr(0, pos);  // Eliminar punto decimal si es el último
    } else if (pos != string::npos) {
        num_str = num_str.substr(0, pos + 1);
    }
    
    datos.push_back(num_str);
}

    archivoEntrada.close();



    const int MAX_HUECO = 11;
    double hueco[MAX_HUECO] = {0};
    int hueco_dig[MAX_HUECO][10] = {{0}};
    double n = 0.0;

    int d_inicio, d_fin;

    if (rango == 10 || rango == 20) {
        d_inicio = 0;
        d_fin = 9;
    } else {
        d_inicio = 1;
        d_fin = rango;
    }

    for (int d = d_inicio; d <= d_fin; d++) {
        bool encontrado = false;
        int contador_hueco = 0;

        for (string s : datos) {
            for (char c : s) {
                int actual = c - '0';
                if (encontrado) {
                    if (actual == d) {
                        int h = (contador_hueco < MAX_HUECO) ? contador_hueco : MAX_HUECO - 1;
                        hueco[h]++;
                        hueco_dig[h][d]++;
                        n++;
                        contador_hueco = 0;
                    } else {
                        contador_hueco++;
                    }
                } else if (actual == d) {
                    encontrado = true;
                }
            }
        }
    }
    cout << "\nHueco";
    for (int d = d_inicio; d <= d_fin; d++)
        cout << setw(12) << d;
    cout << setw(12) << "Total" << endl;
    long long total = 0;
    for (int h = 0; h < MAX_HUECO; h++) {
        cout << setw(5) << h;
        long long total_fila = 0;

        for (int d = d_inicio; d <= d_fin; d++) {
            cout << setw(12) << hueco_dig[h][d];
            total_fila += hueco_dig[h][d];
        }

        cout << setw(12) << total_fila << endl;
        total += total_fila;
    }

    cout << endl <<"=====      "<< setw(10) <<"Total de Huecos: "<< setw(10)  << total << setw(10) << "=====" << endl;

    double chi2 = 0;

    for (int i = 0; i < 11; i++) {
        double fe = n * proba[i];
        double foe = (hueco[i] - fe);
        double res = (foe * foe) / fe;

        cout << "Hueco " << i  << ":" << endl 
            << "  fo:          " << setprecision(5) << fixed << hueco[i] << endl 
            << "  pe:          " << setprecision(5) << fixed << proba[i] << endl
            << "  fe:          " << setprecision(5) << fixed << fe << endl
            << " (fo-fe):      " << setprecision(5) << fixed << foe << endl
            << " (fo-fe)^2/fe: " << setprecision(5) << fixed << res << endl << endl;

        chi2 += res;
    }

    cout << "CHI^2 observado: " << setprecision(5) << fixed << chi2 << endl;

    cout << setprecision(5) << fixed << chi2 << " <= " 
         << setprecision(5) << fixed << chi2_critico << endl;

    if (chi2 <= chi2_critico) {
        cout << "Se acepta H0, los números generados corresponden a una distribución uniforme" << endl;
    } else {
        cout << "Se rechaza H0, los números generados NO corresponden a una distribución uniforme" << endl;
    }
}

// ==================== PRUEBA DE HUECOS CON NUMEROS ====================

string pruebaHuecosNumeC(string nombre){
    double inf = 0.3;
    double sup = 0.7;
    double t = 0.4;
    bool comienzo = false;
    int contador = 0;
    int numehueco = 0;
    vector <double> huecos (5, 0.0);
    double nume;
    ifstream archivo(nombre);
    if (!archivo) {
        std::cout << "No se pudo abrir el archivo\n";
        return "malo";
    }
    while(archivo >> nume){
        if(inf <= nume && nume<=sup){
            if(comienzo){
                huecos[min(contador, 4)]++;
                numehueco++;
            }
            contador=0; 
            comienzo = true;

        } else if (comienzo){
            contador++;
        }
    }
    archivo.close();
    double chi=0.0;
    double fe=0.0;
    for(int i=0; i<5; i++){
        cout<<"Cant de huecos en "<<i<<" "<<huecos[i]<<endl;
        if (i==4) {fe = (pow(0.6,i))*numehueco;} else //Pensar si cambiar pow
        { fe = (0.4*pow(0.6,i))*numehueco;}
        double fo = huecos[i];
        chi += pow(fo-fe,2)/fe;
    }
    cout<<chi<<endl;
    if(chi<=9.48773){
        return "Se acepta";
        } else { return "Se rechaza";
            }
}

string pruebaHuecosNumeD(string nombre, int k, int sup, int inf){
    double prob = double(sup-inf+1)/k;
    int contador = 0;
    int numehueco = 0;
    bool comienzo=false;
    vector <int> huecos (5, 0);
    int nume;
    ifstream archivo(nombre);
    if (!archivo) {
        std::cout << "No se pudo abrir el archivo\n";
        return "malo";
    }
    while(archivo >> nume){
        if(inf <= nume && nume<=sup){
            if(comienzo){
                huecos[min(contador, 4)]++;
                numehueco++;
            }
            contador=0; 
            comienzo = true;

        } else if (comienzo){
            contador++;
        }
    }
    archivo.close();
    double chi=0.0;
    double fe=0.0;
    for(int i=0; i<5; i++){
        cout<<"Cant de huecos en "<<i<<" "<<huecos[i]<<endl;
        if (i==4) {fe = (pow(1-prob,i))*numehueco;} else 
        { fe = (prob*pow(1-prob,i))*numehueco;}
        double fo = huecos[i];
        chi += ((fo-fe)*(fo-fe))/fe;
    }
    cout<<"Ji = "<<chi<<endl;
    if(chi<=9.48773){
        return "Se acepta";
        } else { return "Se rechaza";
            }
}

// ==================== PRUEBA DE POKER ====================

void poker(int rango, string nombre){

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

void pokerDecimal(string nombre){
    ifstream archivo(nombre);   //datos_decimales   /libro
    if (!archivo) {
        cerr << "Error al abrir el archivo\n";
        return;
    }

    vector<double> datos;
    double numero;
    
    while (archivo >> numero) {
        datos.push_back(numero);
    }
    archivo.close();
    int clases[7] = {0};
    int total_manos = datos.size();

    for (double num : datos) {

        vector<int> digitos_precisos(5);
        stringstream ss;
        ss << fixed << setprecision(10) << num;
        string num_str = ss.str();
        
        size_t punto = num_str.find('.');
        if (punto != string::npos) {
            for (int i = 1; i <= 5 && (punto + i) < num_str.length(); i++) {
                char c = num_str[punto + i];
                if (isdigit(c)) {
                    digitos_precisos[i-1] = c - '0';
                }
            }
        }


        int freq[10] = {0};
        for (int d : digitos_precisos) {
            if (d >= 0 && d <= 9) {
                freq[d]++;
            }
        }



        // Obtener frecuencias 
        vector<int> f;
        for (int i = 0; i < 10; i++) {
            if (freq[i] > 0) {
                f.push_back(freq[i]);
            }
        }

        sort(f.begin(), f.end(), greater<int>());

        // Clasificar
        string clase_nombre;
        if (f.size() == 0) {
            clases[DIFERENTES]++;
            clase_nombre = "Diff";
            continue;
        }
        if (f[0] == 5) {
            clases[QUINTILLA]++;
            clase_nombre = "Quintilla";
            continue;
        }
        if (f[0] == 4) {
            clases[POKER]++;
            clase_nombre = "Poker";
            continue;
        }
        if (f[0] == 3 && f.size() > 1 && f[1] == 2) {
            clases[FULL]++;
            clase_nombre = "FULL";
            continue;
        }
        if (f[0] == 3) {
            clases[TERCIA]++;
            clase_nombre = "Tercia";
            continue;
        }
        if (f[0] == 2 && f.size() > 1 && f[1] == 2) {
            clases[DOS_PARES]++;
            clase_nombre = "2 pares";
            continue;
        }
        if (f[0] == 2) {
            clases[UN_PAR]++;
            clase_nombre = "par";
            continue;

        }
        
        clases[DIFERENTES]++;
        clase_nombre = "Diff";
        

    }


    const char* nombres[7] = {
        "Diferentes", "Un par", "Dos pares", "Tercia", 
        "Full", "Poker", "Quintilla"
    };
    
        // Probabilidad teórica
    double prob[7] = {
        0.3024, // diferentes
        0.5040, // un par
        0.1080, // dos pares
        0.0720, // tercia
        0.0090, // full
        0.0045, // poker
        0.0001  // quintilla
    };

    double chi2 = 0.0;


    for (int i = 0; i < 7; i++) {
        double fe = total_manos * prob[i];
        double foe = (clases[i] - fe);
        double res = (foe * foe) / fe;
        
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

// ==================== PRUEBA DE SERIES ====================

string pruebaSeriesC(string nombre){
    int matriz[25][25] = {0};
    ifstream archivo(nombre);
    double pareja2;
    double pareja1;
    double ji = 0.0;
    int x;
    int y;
    if (!archivo) {
        std::cout << "No se pudo abrir el archivo\n";
        return "malo";
    }
    archivo >> pareja2;
    pareja1=pareja2;
    while(archivo >> pareja2){
        x = pareja1/0.04;
        y = pareja2/0.04;
        matriz[x][y]++;
        pareja1=pareja2;
    }
    archivo.close();
    for(int fi=0; fi<25; fi++){
        for(int co=0; co<25; co++){
            ji+=((matriz[fi][co]-1599.9984)*(matriz[fi][co]-1599.9984))/1599.9984;
        }
    }
    cout<<ji<<endl;
    if(ji<=683.22244){
        return "Paso";}
    return "malo";
}

string pruebaSeriesD(string nombre, int k){
    int matriz[20][20] = {0};
    ifstream archivo(nombre);
    if (!archivo) {
        std::cout << "No se pudo abrir el archivo\n";
        return "malo";
    }
    int pareja1;
    int pareja2;
    archivo>>pareja2;
    pareja1=pareja2;
    while(archivo >> pareja2){
        matriz[pareja1-1][pareja2-1]++;
        pareja1=pareja2;
    }
    archivo.close();
    double ji=0.0;
    double fe = (1000000.0-1.0)/ double(k*k);
    for(int fi=0; fi<k; fi++){
        for(int co=0; co<k; co++){
            cout<<"En x= "<<fi<<" "<<co<<" "<<matriz[fi][co]<<endl;
            ji+=(((double)matriz[fi][co]-fe)*((double)matriz[fi][co]-fe))/fe;
        }
    }
    cout<<"Ji = "<<ji<<endl;
    switch (k)
    {
    case 4:
        if(ji<=24.99579)
            return "Pasa";
        break;
    
    case 6:
        if(ji<=49.80185) 
            return "Pasa";
        break;

    case 8:
        if(ji<=82.52873) 
            return "Pasa";
        break;

    case 20:
        if(ji<=446.57424)
            return "Pasa";
        break;

    default:
        break;
    }

    return "No pasa";
}

// ==================== MENÚ PRINCIPAL ====================

int main() {
    int opcionPrueba, opcionLenguaje, opcionRango;
    string archivo;
    
    do {
        cout << "\n=== MENÚ DE PRUEBAS ESTADÍSTICAS ===" << endl;
        cout << "1. Prueba de Promedio" << endl;
        cout << "2. Prueba de Varianza" << endl;
        cout << "3. Prueba de Corridas" << endl;
        cout << "4. Prueba de Huecos con Dígitos" << endl;
        cout << "5. Prueba de Huecos con Números" << endl;
        cout << "6. Prueba de Poker" << endl;
        cout << "7. Prueba de Series" << endl;
        cout << "8. Salir" << endl;
        cout << "Seleccione una prueba (1-8): ";
        cin >> opcionPrueba;
        
        if (opcionPrueba == 8) {
            break;
        }
        
        if (opcionPrueba < 1 || opcionPrueba > 8) {
            cout << "Opción no válida" << endl;
            continue;
        }
        
        cout << "\n=== LENGUAJES DISPONIBLES ===" << endl;
        cout << "1. Java ([0,1[)" << endl;
        cout << "2. Erlang ([0,1[)" << endl;
        cout << "3. Python ([0,1[ y {1,2,3,4,5,6})" << endl;
        cout << "4. C ({1,2,3,4} y {1,2,3,4,5,6,7,8})" << endl;
        cout << "5. Racket ([1,20])" << endl;
        cout << "6. Ruby ([0,1[)" << endl;
        cout << "Seleccione un lenguaje (1-6): ";
        cin >> opcionLenguaje;
        
        // Determinar archivo y rango según lenguaje
        if (opcionLenguaje == 1) { // Java
            archivo = "Eje1randomJava_0_1.txt";
            opcionRango = 10;
        } else if (opcionLenguaje == 2) { // Erlang
            archivo = "Eje1randomE_0_1.txt";
            opcionRango = 10;
        } else if (opcionLenguaje == 3) { // Python
            cout << "\nSeleccione rango para Python:" << endl;
            cout << "1. [0,1[ (rango 10)" << endl;
            cout << "2. {1,2,3,4,5,6} (rango 6)" << endl;
            cout << "Opción: ";
            int opcionPython;
            cin >> opcionPython;
            if (opcionPython == 1) {
                archivo = "Eje1randomPY_0_1.txt";
                opcionRango = 10;
            } else {
                archivo = "Eje1randomPY_1_6.txt";
                opcionRango = 6;
            }
        } else if (opcionLenguaje == 4) { // C
            cout << "\nSeleccione rango para C:" << endl;
            cout << "1. {1,2,3,4} (rango 4)" << endl;
            cout << "2. {1,2,3,4,5,6,7,8} (rango 8)" << endl;
            cout << "Opción: ";
            int opcionC;
            cin >> opcionC;
            if (opcionC == 1) {
                archivo = "Eje1numerosC1_4.txt";
                opcionRango = 4;
            } else {
                archivo = "Eje1numerosC1_8.txt";
                opcionRango = 8;
            }
        } else if (opcionLenguaje == 5) { // Racket
            archivo = "Eje1randomRacket_1_20.txt";
            opcionRango = 20;
        } else if (opcionLenguaje == 6) { // Ruby
            archivo = "Eje1randomRuby_0_1.txt";
            opcionRango = 10;
        } else {
            cout << "Lenguaje no válido" << endl;
            continue;
        }
        
        cout << "\n=== EJECUTANDO PRUEBA ===" << endl;
        cout << "Prueba: " << opcionPrueba << endl;
        cout << "Lenguaje: " << opcionLenguaje << endl;
        cout << "Archivo: " << archivo << endl;
        cout << "Rango: " << opcionRango << endl;
        cout << "=========================" << endl;
        
        // Ejecutar prueba seleccionada
        switch(opcionPrueba) {
            case 1: // Promedio
                if (opcionRango == 10) {
                    cout << pruebaPromedioC(archivo) << endl;
                } else {
                    cout << pruebaPromedioD(archivo, opcionRango) << endl;
                }
                break;
                
            case 2: // Varianza
                varianza(opcionRango, archivo);
                break;
                
            case 3: // Corridas
                cout << pruebaCorrida(archivo) << endl;
                break;
                
            case 4: // Huecos con Dígitos
                huecos(opcionRango, archivo);
                break;
                
            case 5: // Huecos con Números
                if (opcionRango == 10) {
                    cout << pruebaHuecosNumeC(archivo) << endl;
                } else if (opcionRango == 6) {
                    cout << pruebaHuecosNumeD(archivo, 6, 4, 2) << endl;
                } else if (opcionRango == 4) {
                    cout << pruebaHuecosNumeD(archivo, 4, 3, 2) << endl;
                } else if (opcionRango == 8) {
                    cout << pruebaHuecosNumeD(archivo, 8, 5, 2) << endl;
                } else if (opcionRango == 20) {
                    cout << pruebaHuecosNumeD(archivo, 20, 14, 7) << endl;
                }
                break;
                
            case 6: // Poker
                if (opcionRango == 10) {
                    pokerDecimal(archivo);
                } else {
                    poker(opcionRango, archivo);
                }
                break;
                
            case 7: // Series
                if (opcionRango == 10) {
                    cout << pruebaSeriesC(archivo) << endl;
                } else {
                    cout << pruebaSeriesD(archivo, opcionRango) << endl;
                }
                break;
        }
        
        cout << "\nPresione Enter para continuar";
        cin.ignore();
        cin.get();
        
    } while (opcionPrueba != 8);
    
    return 0;
}