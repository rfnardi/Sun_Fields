import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
# from mpl_toolkits import mplot3d

# Este código mostra como a contribuição de cada heliostato 
# varia ao longo de uma região quadrada às 8:00 e ao meio-dia e a média ao longo do dia.

colunas_desejadas = ['x','y','power']

# full_data = pd.read_csv('../../../data/tower_shadow_correction/square_grid_along_day.dat',usecols=colunas_desejadas)
# full_data = pd.read_csv('../../../data/tower_shadow_correction/dados.dat',usecols=colunas_desejadas)

full_data = pd.read_csv('../../../data/tower_shadow_correction/square_grid_8am.dat',usecols=colunas_desejadas)

# full_data = pd.read_csv('../../../data/tower_shadow_correction/square_grid_12am.dat',usecols=colunas_desejadas)

max_power = full_data['power'].max()

dados = full_data[ full_data['power'] > 0.95*max_power]
# dados = full_data[ full_data['power'] < 100]
# dados = full_data
min_power = dados['power'].min()

x_data = dados['x']
y_data = dados['y']
z_data = dados['power']

#figura e um eixo 3D
fig = plt.figure()
ax = plt.axes(projection='3d')

plt.title('Potência média refletida ao longo do dia')
# plt.title('Potência refletida às 8:00')
# plt.title('Potência refletida às 12:00')

#rótulos dos eixos
ax.set_xlabel('x-leste-oeste')
ax.set_ylabel('y-sul-norte')
ax.set_zlabel('Potência (W)')


ax.plot_trisurf(x_data, y_data, z_data, cmap='jet')
ax.view_init(azim=61, elev=12)

# plt.savefig('square_grid_along_day', dpi=300)
# plt.savefig('square_grid_12am', dpi=300)
# plt.savefig('square_grid_8am', dpi=300)

print("Max: ", max_power)
print("Min: ", min_power)
print("Quantidade de pontos selecionados: ", dados['x'].count())
# print("Quantidade total de pontos: ", full_data['x'].count())
print("Potência total recolhida nos heliostatos selecionados: ", dados['power'].sum())

plt.show()

