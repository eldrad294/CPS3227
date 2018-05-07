#
# Module Imports
import pandas as pd
import matplotlib.pyplot as plt
#
# User Input Parameters
save_to_disk = True # If set to false, will output to screen
#
# Constants
results_file_path_openmp = 'OPENMP.csv'
results_file_path_openmpi = 'OPENMPI.csv'
results_file_path_openhybrid = 'OPENHYBRID.csv'
save_to_disk_path = 'graphs/'
#
# File loading into memory
df_openmp = pd.read_csv(results_file_path_openmp)
df_openmpi = pd.read_csv(results_file_path_openmpi)
df_openhybrid = pd.read_csv(results_file_path_openhybrid)
#
def draw_graph(graph_x, graph_y, graph_title, to_disk):
    """
    Wrapper function to generate graph visualization
    :param graph_x:
    :param graph_y:
    :param graph_title:
    :param to_disk: When set to True, saves graph to disk
    :return:
    """
    plt.axis([0, max(graph_x), 0, max(graph_y)])
    plt.title(graph_title)
    plt.plot(graph_x, graph_y)
    plt.title(graph_title)
    if to_disk:
        plt.savefig(save_to_disk_path + graph_title)
    else:
        plt.show()
#
def generate_results(dataframe, iterations, save_to_disk):
    graph_x, graph_y = [], []
    for index, row in dataframe.iterrows():
        #
        graph_x.append(row['NumCPU'])
        graph_y.append(row['Total Elapsed Average(s)'])
        graph_title = row['Run Type'] + " (" + str(row['NumNodes']) + ") - " + str(row['ParticleCount']) + " Particles"
        #
        if ((index + 1) % iterations) == 0:
            draw_graph(graph_x, graph_y, graph_title, save_to_disk)
#
# OPENMP Iterations
generate_results(dataframe=df_openmp, iterations=12, save_to_disk=save_to_disk)


