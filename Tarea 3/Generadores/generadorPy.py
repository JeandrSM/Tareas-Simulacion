import random

CANTIDAD = 1_000_000

# Archivo 1: números reales en [0,1[
with open("randomPY_0_1.txt", "w") as f:
    for _ in range(CANTIDAD):
        f.write(f"{random.random()}\n")

# Archivo 2: números enteros en {1,2,3,4,5,6}
with open("randomPY_1_6.txt", "w") as f:
    for _ in range(CANTIDAD):
        f.write(f"{random.randint(1, 6)}\n")

print("Archivos generados correctamente.")
