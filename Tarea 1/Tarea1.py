import random
import random
import matplotlib.pyplot as plt

#-------------------------------EJERCICIO 2-------------------------------#
def monedas(n,c):
	exitos = 0
	for _ in range(n):
		caras = 0
		lista = [random.randint(0,1) for _ in range(3)]
		for i in lista:
			if i==0:
				caras+=1
		if caras==c:
				exitos+=1
	return exitos/n

#print(monedas(10000, 0))
#print(monedas(10000, 1))
#print(monedas(10000, 2))
#print(monedas(10000, 3))

#-------------------------------EJERCICIO 3-------------------------------#
def binomial(n, p):
    exitos = 0
    for _ in range(n):
        if random.random() < p:
            exitos += 1
    return exitos


def ejercicio3():
    n = 3
    p = 0.5
    N = 1000000

    frecuencias = [0] * (n + 1)

    for _ in range(N):
        k = binomial(n, p)
        frecuencias[k] += 1

    frecuencias = [f / N for f in frecuencias]

    plt.bar(range(n + 1), frecuencias, color='blue', alpha=0.8)
    plt.xlabel("Número de éxitos")
    plt.ylabel("Probabilidad")
    plt.title("Distribución Binomial Simulada")
    plt.xticks(range(n + 1))
    plt.grid(axis='y', linestyle='--', alpha=0.7)
    plt.show()



#ejercicio3()

#-------------------------------EJERCICIO 4-------------------------------#
def cartas4(n):
	exitos = 0
	cartas = ["C"]*48 + ["A"]*4
	for _ in range(n):
		random.shuffle(cartas)
		mano = cartas[:2]
		if mano[0]=="A" and mano[1]=="A":
			exitos +=1
	return exitos/n
#-------------------------------EJERCICIO 5-------------------------------#
def cartas5(n):
	exitos = 0
	cartas = ["C"]*26 + ["X"]*26
	for _ in range(n):
		random.shuffle(cartas)
		if cartas[0]=="X":
			exitos +=1
	return exitos/n
#-------------------------------EJERCICIO 6-------------------------------#
def cartas6(n):
	exitos = 0
	cartas = ["C"]*48 + ["A"]*4
	for _ in range(n):
		random.shuffle(cartas)
		As=0
		for i in range(5):
			if cartas[i]=="A":
				As+=1
		if As==2:
			exitos+=1
	return exitos/n
#-------------------------------EJERCICIO 7-------------------------------#
def cartas7(n):
	exitos = 0
	cartas = [2]*4 + [3]*4 + [4]*4 + [5]*4 + [6]*4 + [7]*4 + [8]*4 + [9]*4 + [10]*16 + ["A"]*4
	for _ in range(n):
		random.shuffle(cartas)
		suma=0
		As=0
		for i in range(5):
			if cartas[i]=="A":
				As+=1
			else:
				suma+=cartas[i]
		while As:
			if (suma+11+As-1)<=21: #Problema, no se cuanto vale un As y no se me ocurre una toma decisiones
			#si el As vale 1 o 11 
				suma+=11
			else:
				suma+=1
			As-=1
		if suma>=17 and suma<=21:
			exitos+=1
	return exitos/n

#print(cartas7(100000))
#-------------------------------EJERCICIO 8-------------------------------#
def juego8a(n):
	exitos=0
	for _ in range(n):
		dinero = 100
		while dinero<200 and dinero>=10:
			proba = random.random()
			if proba <= 0.48:
				dinero+=10
			else:
				dinero-=10
		if dinero >= 200:
			exitos+=1
	return exitos/n

def juego8b(n):
	exitos=0
	for _ in range(n):
		dinero = 100
		apuesta = 10
		while dinero<200 and dinero>=apuesta:
			proba = random.random()
			if proba <=0.48:
				dinero+=apuesta
				apuesta=10
			else:
				dinero-=apuesta
				apuesta*=2
		if dinero >= 200:
			exitos+=1
	return exitos/n

#print(juego8b(1000000))
#-------------------------------EJERCICIO 9-------------------------------#


def ejercicio9(P_TS1, P_S1F, P_TS2, P_S2F):
    # Probabilidad de éxito por cada ruta
    P_S1 = P_TS1 * P_S1F
    P_S2 = P_TS2 * P_S2F
    # Probabilidad de que se envie el mensaje
    P_TF = P_S1  +  P_S2 - P_S1 * P_S2

    return P_TF


def simulacion9(P_TS1, P_S1F, P_TS2, P_S2F):
    N = 1000000

    exitos = 0

    for _ in range(N):
        exito = False

        if random.random() < P_TS1:
            if random.random() < P_S1F:
                exito = True

        if random.random() < P_TS2:
            if random.random() < P_S2F:
                exito = True

        if exito:
            exitos += 1

    return exitos / N


# ejercicio9a = ejercicio9(0.9, 0.8, 0.9, 0.7)
# simulacionA = simulacion9(0.9, 0.8, 0.9, 0.7)
# ejercicio9b = ejercicio9(0.9, 0.8, 0.9, 0.8)
# simulacionB = simulacion9(0.9, 0.8, 0.9, 0.8)

# print(f"a: P(T->F) = {ejercicio9a}")
# print(f" Simulacion a = {simulacionA}")
# print(f"b: P(T->F) = {ejercicio9b}")
# print(f" Simulacion b = {simulacionB}")
