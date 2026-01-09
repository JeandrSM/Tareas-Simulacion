#include <bits/stdc++.h>
using namespace std;


//Pruebas de promedio Continuas y discretas

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
    cout<<"Z Oberservado = "<<zO<<endl;
    if(abs(zO)<= 1.96){
        return "Si cumple con esta PruebaPromedio";
    } else {return "No cumple con esta pruebaPromedio";}
}

//Prueba de Corridas

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
    cout << fixed << setprecision(10)<<"El z0 "<<zO<<" Esperanza"<<espe<<" Varianza"<<varianza<<endl;
    if(abs(zO)<= 1.96){
        return "Si cumple con esta Prueba Corrida";
    } else {return "No cumple con esta prueba Corrida";}
}




//Prueba de Huecos Numeros

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
int main (){
    /*
    //Promedio
    cout<<"Java"<<endl;
    cout<<pruebaPromedioC("Eje1randomJava_0_1.txt")<<endl;
    cout<<"Erlang"<<endl;
    cout<<pruebaPromedioC("Eje1randomE_0_1.txt")<<endl;
    cout<<"Ruby"<<endl;
    cout<<pruebaPromedioC("Eje1randomRuby_0_1.txt")<<endl;
    cout<<"python"<<endl;
    cout<<pruebaPromedioC("Eje1randomPy_0_1.txt")<<endl;
    cout<<"python 1 a 6"<<endl;
    cout<<pruebaPromedioD("Eje1randomPy_1_6.txt",6)<<endl;
    cout<<"C Discreta 1 a 4"<<endl;
    cout<<pruebaPromedioD("Eje1numerosC1_4.txt",4)<<endl;
    cout<<"C Discreta 1 a 8"<<endl;
    cout<<pruebaPromedioD("Eje1numerosC1_8.txt",8)<<endl;
    cout<<"Racket 1 a 20"<<endl;
    cout<<pruebaPromedioD("Eje1randomRacket_1_20.txt",20)<<endl;

    //Corrida
    cout<<"Java"<<endl;
    cout<<pruebaCorrida("Eje1randomJava_0_1.txt")<<endl;
    cout<<"Erlang"<<endl;
    cout<<pruebaCorrida("Eje1randomE_0_1.txt")<<endl;
    cout<<"Ruby"<<endl;
    cout<<pruebaCorrida("Eje1randomRuby_0_1.txt")<<endl;
    cout<<"python"<<endl;
    cout<<pruebaCorrida("Eje1randomPy_0_1.txt")<<endl;
    cout<<"python 1 a 6"<<endl;
    cout<<pruebaCorrida("Eje1randomPy_1_6.txt")<<endl;
    cout<<"C Discreta 1 a 4"<<endl;
    cout<<pruebaCorrida("Eje1numerosC1_4.txt")<<endl;
    cout<<"C Discreta 1 a 8"<<endl;
    cout<<pruebaCorrida("Eje1numerosC1_8.txt")<<endl;
    cout<<"Racket 1 a 20"<<endl;
    cout<<pruebaCorrida("Eje1randomRacket_1_20.txt")<<endl;

    //huecos numeros
    cout<<"Java"<<endl;
    cout<<pruebaHuecosNumeC("Eje1randomJava_0_1.txt")<<endl;
    cout<<"Erlang"<<endl;
    cout<<pruebaHuecosNumeC("Eje1randomE_0_1.txt")<<endl;
    cout<<"Ruby"<<endl;
    cout<<pruebaHuecosNumeC("Eje1randomRuby_0_1.txt")<<endl;
    cout<<"python"<<endl;
    cout<<pruebaHuecosNumeC("Eje1randomPy_0_1.txt")<<endl;
    cout<<"python 1 a 6"<<endl;
    cout<<pruebaHuecosNumeD("Eje1randomPy_1_6.txt", 6, 4, 2)<<endl;
    cout<<"C Discreta 1 a 4"<<endl;
    cout<<pruebaHuecosNumeD("Eje1numerosC1_4.txt", 4, 3, 2)<<endl;
    cout<<"C Discreta 1 a 8"<<endl;
    cout<<pruebaHuecosNumeD("Eje1numerosC1_8.txt", 8, 5, 2)<<endl;
    cout<<"Racket 1 a 20"<<endl;
    cout<<pruebaHuecosNumeD("Eje1randomRacket_1_20.txt", 20, 14, 7)<<endl;
*/
    //Series
    cout<<"Java"<<endl;
    cout<<pruebaSeriesC("Eje1randomJava_0_1.txt")<<endl;
    cout<<"Erlang"<<endl;
    cout<<pruebaSeriesC("Eje1randomE_0_1.txt")<<endl;
    cout<<"Ruby"<<endl;
    cout<<pruebaSeriesC("Eje1randomRuby_0_1.txt")<<endl;
    cout<<"python"<<endl;
    cout<<pruebaSeriesC("Eje1randomPy_0_1.txt")<<endl;
    cout<<"python 1 a 6"<<endl;
    cout<<pruebaSeriesD("Eje1randomPy_1_6.txt", 6)<<endl;
    cout<<"C Discreta 1 a 4"<<endl;
    cout<<pruebaSeriesD("Eje1numerosC1_4.txt", 4)<<endl;
    cout<<"C Discreta 1 a 8"<<endl;
    cout<<pruebaSeriesD("Eje1numerosC1_8.txt", 8)<<endl;
    cout<<"Racket 1 a 20"<<endl;
    cout<<pruebaSeriesD("Eje1randomRacket_1_20.txt", 20)<<endl;

    }
