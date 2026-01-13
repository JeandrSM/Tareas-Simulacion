import numpy as np
import math
import matplotlib.pyplot as plt

# -------------------------
# FUNCIONES DE FRECUENCIAS ESPERADAS
# -------------------------
def binomial(fo, n):
    N = len(fo) - 1
    # calcular p
    eX = 0
    for i in range(len(fo)):
        eX += i * (fo[i]/n)
    p = eX / N
    print(f"p = {round(p,4)}")

    fe = []
    for i in range(N+1):
        prob = math.comb(N,i) * pow(p,i) * pow(1-p,N-i)
        fe.append(prob*n)

    return fe

def poisson(fo, n):
    lam = 0
    for i in range(len(fo)):
        lam += i * (fo[i]/n)
    lam = round(lam,4)
    print(f"lambda = {lam}")

    fe = []
    for i in range(len(fo)):
        prob = math.exp(-lam) * pow(lam,i) / math.factorial(i)
        fe.append(prob * n)

    return fe

def uniforme(fo, n):
    k = len(fo)
    fe = []
    for i in range(k):
        fe.append(n/k)
    return fe

def geometrica(fo, n):
    eX = 0
    for i in range(len(fo)):
        eX += i*(fo[i]/n)
    p = round(1/(eX+1),4)
    print(f"p = {p}")

    fe = []
    for i in range(len(fo)):
        prob = pow(1-p,i)*p
        fe.append(prob*n)
    return fe

def calcular_media_varianza(fo):
    n = sum(fo)
    k = len(fo)
    media = sum(i * fo[i] for i in range(k)) / n
    varianza = sum(fo[i] * (i - media)**2 for i in range(k)) / n
    return media, varianza


# -------------------------
# CHI CUADRADO Y TABLA K-S
# -------------------------
def ChiCuadrado(fe, fo, critico):
    Chi2 = 0
    print("\n{:>3} {:>5} {:>8} {:>10}".format("i","FO","FE","(FO-FE)^2/FE"))
    print("-"*40)
    for i in range(len(fo)):
        diff = fo[i] - fe[i]
        chi = diff*diff/fe[i]
        Chi2 += chi
        print("{:>3} {:>5} {:>8.2f} {:>10.4f}".format(i, fo[i], fe[i], chi))
    print("-"*40)
    print(f"Chi² total = {Chi2:.4f}")
    if (Chi2 <= critico): 
        print(f"El valor Chi2 <= {critico:.4f}, se acepta la hipotesis de H0 como verdadera.") 
    else: 
        print(f"El valor Chi2 > {critico:.4f}, se rechaza la hipotesis de H0.") 
    return Chi2

def tabla_ks(fe, fo):
    n = sum(fo)
    fo_acum = []
    fe_acum = []
    suma_fo = 0
    suma_fe = 0
    for i in range(len(fo)):
        suma_fo += fo[i]
        suma_fe += fe[i]
        fo_acum.append(suma_fo)
        fe_acum.append(suma_fe)

    poa = []
    pea = []
    for i in range(len(fo)):
        poa.append(fo_acum[i]/n)
        pea.append(fe_acum[i]/n)

    D_max = 0
    print("\n{:>3} {:>4} {:>5} {:>8} {:>8} {:>8} {:>10}".format(
        "x","FO","FOA","POA","FE","FEA","|POA-PEA|"))
    print("-"*70)
    for i in range(len(fo)):
        diff = abs(poa[i]-pea[i])
        if diff > D_max:
            D_max = diff
        print("{:>3} {:>4} {:>5} {:>8.4f} {:>8.2f} {:>8.2f} {:>10.4f}".format(
            i, fo[i], fo_acum[i], poa[i], fe[i], fe_acum[i], diff
        ))
    print("-"*70)
    print(f"D máximo = {D_max:.4f}")
    D_critico = 1.36/math.sqrt(n)
    if (D_max <= D_critico): print(f"El valor de d <= {D_critico:4f} se acepta la hipotesis de H0 como verdadera.") 
    else: print(f"El valor de d > {D_critico:4f} se rechaza la hipotesis de H0.")

# -------------------------
# HISTOGRAMA
# -------------------------
def grafico_barras(fo, fe, titulo):
    """
    Grafica frecuencias observadas y esperadas para números discretos del 0 al 9.
    
    fo: lista o array de frecuencias observadas (longitud 10)
    fe: lista o array de frecuencias esperadas (longitud 10)
    titulo: título del gráfico
    """
    k = len(fo)
    x = np.arange(k)  # Valores discretos 0,1,...,9
    etiquetas = [str(i) for i in range(k)]  # Etiquetas del eje x: 0-9

    plt.figure(figsize=(10, 6))
    
    # Barras para frecuencia observada
    plt.bar(x , fo, width=1, alpha=0.8, label="Observada",
            color='steelblue', edgecolor='black')
    
    # Barras para frecuencia esperada
    plt.bar(x , fe, width=1, alpha=0.3, label="Esperada",
            color='coral', edgecolor='black', linestyle='--')
    
    # Línea de frecuencia esperada
    plt.plot(x, fe, '--', color='coral', linewidth=2.5,
             marker='o', markersize=5, label="Frecuencia esperada")
    
    plt.xticks(x, etiquetas)
    plt.xlabel("Valores discretos")
    plt.ylabel("Frecuencia absoluta")
    plt.title(titulo)
    plt.legend()
    plt.grid(axis='y', alpha=0.3, linestyle='--')
    plt.tight_layout()
    plt.show()


# -------------------------
# FUNCION PRINCIPAL
# -------------------------
def frecuancia(nombre_archivo):
    datos = np.loadtxt(nombre_archivo, dtype=int)
    n = len(datos)
    fo = np.bincount(datos) 
    media, varianza = calcular_media_varianza(fo)
    print(f"\nMedia = {media:.4f}, Varianza = {varianza:.4f}")

    

    # ---------------- BINOMIAL ----------------
    print("\nPrueba Binomial")
    fe = binomial(fo, n)
    ChiCuadrado(fe, fo, 15.50731) # 8 grados de libertad
    tabla_ks(fe, fo)
    grafico_barras(fo, fe, "Prueba Binomial")

    # ---------------- POISSON ----------------
    print("\nPrueba Poisson")
    fe = poisson(fo, n)
    ChiCuadrado(fe, fo, 15.50731) # 8 grados de libertad
    tabla_ks(fe, fo)
    grafico_barras(fo, fe, "Prueba Poisson")

    # ---------------- UNIFORME ----------------
    print("\nPrueba Uniforme")
    fe = uniforme(fo, n)
    ChiCuadrado(fe, fo, 16.91898)
    tabla_ks(fe, fo)
    grafico_barras(fo, fe, "Prueba Uniforme")  # 9 grados de libertad

    # ---------------- GEOMETRICA ----------------
    print("\nPrueba Geometrica")
    fe = geometrica(fo, n)
    ChiCuadrado(fe, fo, 15.50731) # 8 grados de libertad
    tabla_ks(fe, fo)
    grafico_barras(fo, fe, "Prueba Geometrica")

    # ---------------- TABLA DE PROBABILIDAD PREDEFINIDA ----------------
    print("\n================ TABLA DE PROBABILIDAD PREDEFINIDA =================")
    FO_tabla = [13738, 107, 110, 98, 101, 10048, 97, 2057, 19935, 53709]
    FE_tabla = [13500, 100, 100, 100, 100, 10000, 100, 2000, 20000, 54000]

    print("Chi² y K-S sobre tabla predefinida")
    ChiCuadrado(FE_tabla, FO_tabla, 16.91898)
    tabla_ks(FE_tabla, FO_tabla)
    grafico_barras(FO_tabla, FE_tabla, "Tabla de Probabilidad")

# -------------------------
# EJECUCION
# -------------------------
frecuancia("m1.txt")
