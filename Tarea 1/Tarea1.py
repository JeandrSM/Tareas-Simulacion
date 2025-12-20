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

#2f La distribucion que sigue este experimento es una binomial 
#   siendo un ensayo de Bernoulli, los eventos son independientes y se tiene un numero de ensayos fijos  

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

#4a. La probabilidad de que ambos sean ases es de 4/52 * 3/51, esto debido a que el experimento no tiene reposicion de cartas 
#    cada mazo cuenta con 52 cartas (4 ases) 

#-------------------------------EJERCICIO 5-------------------------------#
def cartas5(n):
	exitos = 0
	cartas = ["C"]*26 + ["X"]*26
	for _ in range(n):
		random.shuffle(cartas)
		if cartas[0]=="X":
			exitos +=1
	return exitos/n

#5a. Cada palo del mazo cuenta con 13 cartas (52 en total), se pide la probabilidad de sacar treboles o espadas 
#    siendo un total de 26 cartas, por lo tanto tiene una probabilidad de 13/52 + 13/52 = 0.5

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
		if As>=2:
			exitos+=1
	return exitos/n

#6a. Se utiliza una distribucion geometrica debido a ser un evento sin reposiciones, 
#    se utiliza un grupo reducido de la poblacion total y hay una cantidad de exitos en la poblacion (2 > ases)
#    Siendo la probabilidad de x=2 hasta 4 Σ(4Cx)*((52-4)C(5-x)) = 2257/54145 = 0.04168436605
#                                                  (52C5)

#-------------------------------EJERCICIO 7-------------------------------#
def cartas7(n):
	exitos = 0
	cartas = [2]*4 + [3]*4 + [4]*4 + [5]*4 + [6]*4 + [7]*4 + [8]*4 + [9]*4 + [10]*4+ [11]*4 + [12]*4 + [13]*4 + ["A"]*4
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
			if (suma+14+As-1)<=21:
				suma+=14
			else:
				suma+=1
			As-=1
		if suma>=17 and suma<=21:
			exitos+=1
	return exitos/n

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

#-------------------------------EJERCICIO 9-------------------------------#


def ejercicio9(Tok_S1, S1_Flor, Tok_S2, S2_Flor):
    #Éxito por cada ruta
    P_S1 = Tok_S1 * S1_Flor
    P_S2 = Tok_S2 * S2_Flor
    #Éxito general
    P_TF = P_S1  +  P_S2 - P_S1 * P_S2

    return P_TF

def ejercicio9_c(Tok_S1, S1_Flor, Tok_S2, S2_Flor, S1_S2):

    #Probabilidad de llegar a Florida dado que se llegó a S1
    Flor_S1 = S1_Flor + (1 - S1_Flor) * S1_S2 * S2_Flor

    #Probabilidad de llegar a Florida dado que se llegó a S2
    Flor_S2 = S2_Flor + (1 - S2_Flor) * S1_S2 * S1_Flor

    #Probabilidad total
    P_TF = 1 - (1 - Tok_S1 * Flor_S1) * (1 - Tok_S2 * Flor_S2)

    return P_TF


def simulacion9(Tok_S1, S1_Flor, Tok_S2, S2_Flor):
    N = 1000000

    exitos = 0

    for _ in range(N):
        exito = False
        
        #Desde S1
        if random.random() < Tok_S1:
            if random.random() < S1_Flor:
                exito = True
        #Desde S2
        if random.random() < Tok_S2 and not exito:
            if random.random() < S2_Flor:
                exito = True

        if exito:
            exitos += 1

    return exitos / N



def simulacion9c(Tok_S1, S1_Flor, Tok_S2, S2_Flor, S1_S2):
    N = 1000000
    exitos = 0

    for _ in range(N):
        exito = False

        # Desde S1
        if random.random() < Tok_S1:
            if random.random() < S1_Flor:
                exito = True
            else:
                if random.random() < S1_S2:
                    if random.random() < S2_Flor:
                        exito = True

        # Desde S2
        if random.random() < Tok_S2 and not exito:
            if random.random() < S2_Flor:
                exito = True
            else:
                if random.random() < S1_S2:
                    if random.random() < S1_Flor:
                        exito = True

        if exito:
            exitos += 1

    return exitos / N



# ejercicio9a = ejercicio9(0.9, 0.8, 0.9, 0.7)
# simulacionA = simulacion9(0.9, 0.8, 0.9, 0.7)

# ejercicio9b = ejercicio9(0.9, 0.8, 0.9, 0.8)
# simulacionB = simulacion9(0.9, 0.8, 0.9, 0.8)

# ejercicio9c = ejercicio9_c(0.9, 0.8, 0.9, 0.7, 0.8)
# simulacionC = simulacion9c(0.9, 0.8, 0.9, 0.7, 0.8)

# print(f"a: P(T->F) = {ejercicio9a}")
# print(f" Simulacion a = {simulacionA}")
# print(f"b: P(T->F) = {ejercicio9b}")
# print(f" Simulacion b = {simulacionB}")
# print(f"c: P(T->F) = {ejercicio9c}")
# print(f" Simulacion c = {simulacionC}")



def menu():
    while True:
        print("\n========== MENÚ DE EJERCICIOS ==========")
        print("1. Ejercicio 2")
        print("2. Ejercicio 3")
        print("3. Ejercicio 4")
        print("4. Ejercicio 5")
        print("5. Ejercicio 6")
        print("6. Ejercicio 7")
        print("7. Ejercicio 8a")
        print("8. Ejercicio 8b")
        print("9. Ejercicio 9")
        print("0. Salir")

        opcion = input("Seleccione una opción: ")

        if opcion == "1":
            n = int(input("Número de simulaciones: "))
            print("\nProbabilidades según número de caras:")
            for c in range(4):
                print(f"Caras = {c} = {monedas(n, c)}")

        elif opcion == "2":
            print("Mostrando gráfica...")
            ejercicio3()

        elif opcion == "3":
            n = int(input("Número de simulaciones: "))
            print("Probabilidad:", cartas4(n))

        elif opcion == "4":
            n = int(input("Número de simulaciones: "))
            print("Probabilidad:", cartas5(n))

        elif opcion == "5":
            n = int(input("Número de simulaciones: "))
            print("Probabilidad:", cartas6(n))

        elif opcion == "6":
            n = int(input("Número de simulaciones: "))
            print("Probabilidad:", cartas7(n))

        elif opcion == "7":
            n = int(input("Número de simulaciones: "))
            print("Probabilidad de éxito:", juego8a(n))

        elif opcion == "8":
            n = int(input("Número de simulaciones: "))
            print("Probabilidad de éxito:", juego8b(n))

        elif opcion == "9":
            print("\n--- EJERCICIO 9 ---")
            print("a) Red original")
            print("b) Mejora en S2")
            print("c) Comunicación entre S1 S2")

            sub = input("Seleccione el caso (a/b/c): ").lower()

            if sub == "a":
                print("\nCaso (a)")
                P_TS1 = float(input("P(T→S1): "))
                P_S1F = float(input("P(S1→F): "))
                P_TS2 = float(input("P(T→S2): "))
                P_S2F = float(input("P(S2→F): "))

                teorico = ejercicio9(P_TS1, P_S1F, P_TS2, P_S2F)
                sim = simulacion9(P_TS1, P_S1F, P_TS2, P_S2F)

            elif sub == "b":
                print("\nCaso (b)")
                P_TS1 = float(input("P(T→S1): "))
                P_S1F = float(input("P(S1→F): "))
                P_TS2 = float(input("P(T→S2): "))
                P_S2F = float(input("P(S2→F): "))

                teorico = ejercicio9(P_TS1, P_S1F, P_TS2, P_S2F)
                sim = simulacion9(P_TS1, P_S1F, P_TS2, P_S2F)

            elif sub == "c":
                print("\nCaso (c)")
                P_TS1 = float(input("P(T→S1): "))
                P_S1F = float(input("P(S1→F): "))
                P_TS2 = float(input("P(T→S2): "))
                P_S2F = float(input("P(S2→F): "))
                P_S1S2 = float(input("P(S1↔S2): "))

                teorico = ejercicio9_c(P_TS1, P_S1F, P_TS2, P_S2F, P_S1S2)
                sim = simulacion9c(P_TS1, P_S1F, P_TS2, P_S2F, P_S1S2)

            else:
                print("Opción inválida.")
                continue

            print("\nResultados:")
            print(f" Probabilidad calculada", teorico)
            print(f" Probabilidad simulada", sim)


        elif opcion == "0":
            print("Saliendo del programa...")
            break

        else:
            print("Opción inválida. Intente de nuevo.")


        menu()



