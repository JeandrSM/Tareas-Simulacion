import numpy as np
import math
import matplotlib.pyplot as plt
from scipy.stats import gamma, beta, norm

# -------------------------
# FUNCIONES AUXILIARES
# -------------------------
def separar_datos(datos):
    menores = []
    mayores = []
    for valor in datos:
        if valor < 1:
            menores.append(valor)
        elif valor >= 1.5:
            mayores.append(valor)
    return np.array(menores), np.array(mayores)

def frecuencias(datos, bins):
    min_val = min(datos)
    max_val = max(datos)
    ancho = (max_val - min_val) / bins

    fo = [0] * bins
    limites = []

    for i in range(bins):
        a = min_val + i * ancho
        b = min_val + (i + 1) * ancho
        limites.append((a, b))

    for x in datos:
        idx = int((x - min_val) / ancho)
        if idx == bins:
            idx = bins - 1
        fo[idx] += 1

    return fo, limites

# -------------------------
# CHI CUADRADO
# -------------------------
def ChiCuadrado(fe, fo, limites, critico):
    Chi2 = 0
    print("\n{:>5} {:>15} {:>8} {:>12} {:>12}".format(
        "i", "Intervalo", "FO", "FE", "(FO-FE)^2/FE"
    ))
    print("-"*65)
    for i in range(len(fo)):
        chi = (fo[i] - fe[i])**2 / fe[i]
        Chi2 += chi
        print("{:>5} [{:6.3f}, {:6.3f}) {:8d} {:12.2f} {:12.4f}".format(
            i, limites[i][0], limites[i][1], fo[i], fe[i], chi
        ))
    print("-"*65)
    print(f"Chi² total = {Chi2:.4f}\n")
    if (Chi2 <= critico): 
        print(f"El valor Chi2 <= {critico:.4f}, se acepta la hipotesis de H0 como verdadera.") 
    else: 
        print(f"El valor Chi2 > {critico:.4f}, se rechaza la hipotesis de H0.") 
    return round(Chi2, 4)

def grafico_barras(fo, fe, limites, titulo):
    k = len(fo)
    x = np.arange(k)
    etiquetas = []
    for i in range(k):
        a, b = limites[i]
        etiquetas.append(f"[{round(a,3)}, {round(b,3)}[")

    plt.figure(figsize=(10, 6))
    
    # Crear gráfico de barras para frecuencia observada
    plt.bar(x, fo, width=1, alpha=0.8, label="Muestra", 
            color='steelblue', edgecolor='black')
    
    # Crear gráfico de barras para frecuencia esperada (transparente)
    plt.bar(x, fe, width=1, alpha=0.5, label="Uniforme teórica", 
            color='coral', edgecolor='black', linestyle='--')
    
    plt.plot(x, fe, '--', color='coral', linewidth=2.5, 
             marker='o', markersize=5, label="Frecuencia esperada")
    
    plt.xticks(x, etiquetas, rotation=45)
    plt.xlabel("Intervalos / Clases")
    plt.ylabel("Frecuencia absoluta")
    plt.title(titulo)
    plt.legend()
    plt.grid(axis='y', alpha=0.3, linestyle='--')
    plt.tight_layout()
    plt.show()

# -------------------------
# TABLA KOLMOGOROV-SMIRNOV
# -------------------------
def tabla_ks(datos, fe, limites):
    n = len(datos)
    fo, _ = frecuencias(datos, len(limites))
    fo_acum = np.cumsum(fo)
    fe_acum = np.cumsum(fe)
    poa = []
    pea = []
    for i in range(len(fo_acum)):
        poa.append(fo_acum[i] / n)
        pea.append(fe_acum[i] / n)

    print("\n" + "-"*70)
    print("{:>3} {:>4} {:>5} {:>8} {:>8} {:>8} {:>10}".format(
        "x","FO","FOA","POA","FE","FEA","|POA-PEA|"
    ))
    print("-"*70)
    D_max = 0
    for i in range(len(fo)):
        diff = abs(poa[i]-pea[i])
        if diff > D_max:
            D_max = diff
        print("{:>3} {:>4} {:>5} {:>8.4f} {:>8.4f} {:>8.4f} {:>10.4f}".format(
            i, fo[i], fo_acum[i], poa[i], fe[i], fe_acum[i], diff
        ))
    print("-"*70)
    print(f"D máximo = {D_max:.4f}")
    print("-"*70)
    D_critico = 1.36/math.sqrt(n)
    if (D_max <= D_critico): print(f"El valor de d <= {D_critico:4f} se acepta la hipotesis de H0 como verdadera.") 
    else: print(f"El valor de d > {D_critico:4f} se rechaza la hipotesis de H0.")

# -------------------------
# PRUEBAS UNIFORME, NORMAL, GAMMA, BETA
# -------------------------
def prueba_uniforme(datos, bins):
    print("\n================ PRUEBA UNIFORME ================")
    fo, limites = frecuencias(datos, bins)
    n = len(datos)
    fe = []
    for i in range(bins):
        fe.append(n/bins)

    # Chi-cuadrado
    grado_l = bins - 1
    print(f"gl: {grado_l}")
    ChiCuadrado(fe, fo, limites, 9.48773)
    grafico_barras(fo, fe, limites, "Histograma – Ajuste Uniforme")

    # K-S
    print("\nTabla K-S Uniforme:")
    tabla_ks(datos, fe, limites)

def prueba_normal(datos, bins):
    print("\n================ PRUEBA NORMAL ================")
    fo, limites = frecuencias(datos, bins)
    n = len(datos)

    # calcular xi (puntos medios)
    xi = []
    for i in range(len(limites)):
        li, ls = limites[i]
        xi.append((li + ls) / 2)

    # media y varianza
    suma = 0
    for i in range(len(fo)):
        suma += fo[i] * xi[i]
    media = suma / n
    print(f"Media: {media}")

    suma_var = 0
    for i in range(len(fo)):
        suma_var += fo[i] * (xi[i] - media)**2
    var = suma_var / n
    print(f"Varianza: {var}")
    desv = math.sqrt(var)


    # frecuencias esperadas
    fe = []
    for i in range(len(limites)):
        li, ls = limites[i]
        fe.append(n*(norm.cdf(ls, media, desv)-norm.cdf(li, media, desv)))

    # Chi y gráfico
    grado_l = bins - 3
    print(f"gl: {grado_l}")
    ChiCuadrado(fe, fo, limites, 11.0705)
    grafico_barras(fo, fe, limites, "Histograma – Ajuste Normal")

    # K-S
    print("\nTabla K-S Normal:")
    tabla_ks(datos, fe, limites)

def prueba_gamma(datos, bins):
    print("\n================ PRUEBA GAMMA ================")
    fo, limites = frecuencias(datos, bins)
    n = len(datos)

    media = 0
    for x in datos:
        media += x
    media = media / n
    print(f"Media: {media}")

    var = 0
    for x in datos:
        var += (x - media)**2
    var = var / n
    print(f"Varianza: {var}")

    alpha = media**2 / var
    beta_p = var / media

    print(f"alpha: {alpha}")
    print(f"beta: {beta_p}")

    fe = []
    for i in range(len(limites)):
        li, ls = limites[i]
        fe.append(n*(gamma.cdf(ls, alpha, scale=beta_p)-gamma.cdf(li, alpha, scale=beta_p)))

    # Chi y gráfico
    grado_l = bins - 3
    print(f"gl: {grado_l}")
    ChiCuadrado(fe, fo, limites, 11.0705)
    grafico_barras(fo, fe, limites, "Histograma – Ajuste Gamma")

    # K-S
    print("\nTabla K-S Gamma:")
    tabla_ks(datos, fe, limites)

def prueba_beta(datos, bins):
    print("\n================ PRUEBA BETA ================")
    fo, limites = frecuencias(datos, bins)
    n = len(datos)
    a = min(datos)
    b = max(datos)

    # calcular xi (puntos medios)
    xi = []
    for i in range(len(limites)):
        li, ls = limites[i]
        xi.append((li + ls)/2)

    # normalizar xi a [0,1] => yi
    yi = []
    for i in range(len(xi)):
        yi.append((xi[i]-a)/(b-a))

    # calcular media y varianza de yi
    suma = 0
    for i in range(len(fo)):
        suma += fo[i]*yi[i]
    media = suma / n
    print(f"Media: {media}")

    suma_var = 0
    for i in range(len(fo)):
        suma_var += fo[i]*(yi[i]-media)**2
    var = suma_var / n
    print(f"Varianza: {var}")

    t = media*(1-media)/var - 1
    alpha = media * t
    beta_p = (1 - media) * t
    print(f"alpha: {alpha}")
    print(f"beta: {beta_p}")

    # frecuencias esperadas
    fe = []
    for i in range(len(limites)):
        li, ls = limites[i]
        fe.append(n*(beta.cdf((ls-a)/(b-a), alpha, beta_p) - beta.cdf((li-a)/(b-a), alpha, beta_p)))

    # Chi y gráfico
    grado_l = bins - 3
    print(f"gl: {grado_l}")
    ChiCuadrado(fe, fo, limites, 11.0705)
    grafico_barras(fo, fe, limites, "Histograma – Ajuste Beta")

    # K-S
    print("\nTabla K-S Beta:")
    tabla_ks(datos, fe, limites)

# -------------------------
# FUNCION PRINCIPAL
# -------------------------
def analizar_muestra(archivo):
    datos = np.loadtxt(archivo)
    menores, mayores = separar_datos(datos)

    rangoMax = max(menores)
    rangoMin = min(menores)
    print(f"Rango : [{round(rangoMin)}, {round(rangoMax)}[")
    prueba_uniforme(menores, 5)
    

    rangoMax = max(mayores)
    rangoMin = min(mayores)
    print(f"Rango : [{rangoMin:.3f}, {rangoMax:.3f}[")
    prueba_normal(mayores, 8)
    prueba_gamma(mayores, 8)
    prueba_beta(mayores, 8)

# -------------------------
# EJECUCION
# -------------------------
archivo = "m15.txt"
analizar_muestra(archivo)
