import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# Carrega os dados (exemplo de arquivo CSV com três colunas: x, y, z)
# Use np.loadtxt, mas ajuste o delimitador se for necessário
data = np.loadtxt('./shuffled_points.txt', delimiter=' ')

# Divide as colunas em coordenadas x, y, z
x = data[:, 0]
y = data[:, 1]
z = data[:, 2]

# Cria uma figura e um eixo 3D
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

# Plota os pontos 3D
ax.scatter(x, y, z, c='b', marker='o')

# Adiciona rótulos aos eixos
ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')

# Exibe o gráfico
plt.show()


