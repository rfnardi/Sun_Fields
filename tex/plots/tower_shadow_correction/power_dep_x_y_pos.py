import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
# from mpl_toolkits import mplot3d

# Este código mostra como a contribuição de cada heliostato 
# varia ao longo de uma região quadrada ao meio-dia. 
# Para efeitos de escala a região sob a sombra da torre central 
# foi interpolada com os pontos vizinhos mas sua contribuição é nula.

colunas_desejadas = ['x','y','power']
dados = pd.read_csv('../../../data/tower_shadow_correction/square_grid.dat',usecols=colunas_desejadas)

x_data = dados['x']
y_data = dados['y']
z_data = dados['power']

#figura e um eixo 3D
fig = plt.figure()
ax = plt.axes(projection='3d')

#rótulos dos eixos
ax.set_xlabel('x-leste-oeste')
ax.set_ylabel('y-sul-norte')
ax.set_zlabel('Potência (W)')

# ax.scatter(x_data, y_data, z_data) #não admite cmap

ax.plot_trisurf(x_data, y_data, z_data, cmap='jet')
ax.view_init(azim=61, elev=12)

plt.show()

