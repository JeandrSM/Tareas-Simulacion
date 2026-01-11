import numpy as np
import matplotlib.pyplot as plt
from collections import Counter


def parametros(nombre):
    datos = np.loadtxt(nombre)
    print(datos.mean())
    print(datos.std())
    print(f"Rango: [{datos.min()}, {datos.max()}]")

        

def graficar_histograma(nombre_archivo, bins=50, relativa=False):

    datos = np.loadtxt(nombre_archivo)

    frecuencias, bordes = np.histogram(datos, bins=bins)

    if relativa:
        frecuencias = frecuencias / frecuencias.sum()
        ylabel = "Frecuencia relativa"
    else:
        ylabel = "Frecuencia absoluta"

    # Calcular centros y anchos
    anchos = bordes[1:] - bordes[:-1]
    centros = (bordes[:-1] + bordes[1:]) / 2

    # Graficar
    plt.bar(
        centros,
        frecuencias,
        width=anchos,
        align="center",
        edgecolor="black"
    )

    plt.xlabel("Intervalos / Clases")
    plt.ylabel(ylabel)
    plt.title(f"Histograma de la muestra: {nombre_archivo}")

    plt.show()


def graficar_discreta(nombre_archivo):
    """
    Lee datos discretos desde un archivo y genera un gráfico de barras.

    Parámetros:
    - nombre_archivo (str): archivo con la muestra
    - relativa (bool): si True, grafica frecuencia relativa
    """

    # Contar frecuencias
    frecuencia = Counter()

    with open(nombre_archivo, "r") as f:
        for linea in f:
            valor = linea.strip()
            if valor != "":
                frecuencia[valor] += 1

    valores = sorted(frecuencia.keys())
    frecuencias = [frecuencia[v] for v in valores]

    print("Valor | Frecuencia")
    for v, f in zip(valores, frecuencias):
        print(v, f)


    # Gráfico de barras
    plt.bar(valores, frecuencias, width=0.5, edgecolor="black")

    plt.xlabel("Valores")
    plt.ylabel("Frecuencia absoluta")
    plt.xticks(valores)
    plt.title(f"Distribución discreta: {nombre_archivo}")

    plt.show()

parametros("m14.txt")