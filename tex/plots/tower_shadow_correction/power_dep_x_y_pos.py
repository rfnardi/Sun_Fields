import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
# from mpl_toolkits import mplot3d

# Este código mostra como a contribuição de cada heliostato 
# varia ao longo de uma região quadrada às 8:00 e ao meio-dia e a média ao longo do dia.

def set_plot(file_choice, data_filename_ending):
    datapath = '../../../data/tower_shadow_correction/'
    data_file = datapath + 'average_tower_' + data_filename_ending[file_choice] + '.dat'
    colunas_desejadas = ['x','y','power']
    full_data = pd.read_csv(data_file, usecols=colunas_desejadas)
    max_power = full_data['power'].max()

    # full_data = pd.read_csv('../../../data/tower_shadow_correction/square_grid_8am.dat',usecols=colunas_desejadas)
    # full_data = pd.read_csv('../../../data/tower_shadow_correction/square_grid_12am.dat',usecols=colunas_desejadas)

    which_data = int(input('Selecionar heliostatos 5% mais potentes? 1=sim, 0=não '))
    if which_data:
        dados = full_data[ full_data['power'] > 0.95*max_power]
        title_top_power = 'Potência média diária - top 5%. Altura da torre: ' + data_filename_ending[file_choice]
    else:
        dados = full_data
        title_top_power = 'Potência média diária em todo o campo. Altura da torre: ' + data_filename_ending[file_choice]

    # dados = full_data[ full_data['power'] < 100]
    min_power = dados['power'].min()

    fig = plt.figure()
    ax = plt.axes(projection='3d')

    plt.title(title_top_power)
    # plt.title('Potência refletida às 8:00')
    # plt.title('Potência refletida às 12:00')

    ax.set_xlabel('x-leste-oeste')
    ax.set_ylabel('y-sul-norte')
    ax.set_zlabel('Potência (W)')

    ax.plot_trisurf(dados['x'], dados['y'], dados['power'], cmap='jet')
    ax.view_init(azim=61, elev=12)

    return max_power, min_power, dados['x'].count(), dados['power'].sum(), which_data


#-----------------------------------------



data_filename_ending = ['20m','40m','60m','70m','80m']
select_one_single_file = int(input('Exibição interativa de um gráfico (1) ou geração de arquivos (0)? '))


if select_one_single_file:
    print('Altura da torre , Opção')
    for i in range(0,5):
        print(data_filename_ending[i], ' , ', i)
    file_choice = int(input('Altura da torre: '))

    Max, Min, Qtd_Heliost, Total_Power, which_data = set_plot(file_choice, data_filename_ending)

    print("Max: ", Max)
    print("Min: ", Min)
    print("Quantidade de heliostatos selecionados: ", Qtd_Heliost)
    print("Potência total recolhida nos heliostatos selecionados: ", Total_Power)

    plt.show()
else:
    for i in range(0,5):
        print('Trabalhando com dados para torre de ', data_filename_ending[i])
        do_work = int(input('Proceder com criação do gráfico referente a este arquivo? 1=sim, 0=não: '))
        if do_work:
            Max, Min, Qtd_Heliost, Total_Power, which_data = set_plot(i, data_filename_ending)
            if which_data:
                plt.savefig('square_grid_along_day_'+data_filename_ending[i]+'top_5_most_powerfull', dpi=300)
            else: 
                plt.savefig('square_grid_along_day_'+data_filename_ending[i]+'full_grid', dpi=300)

    # plt.savefig('square_grid_12am', dpi=300)
    # plt.savefig('square_grid_8am', dpi=300)


