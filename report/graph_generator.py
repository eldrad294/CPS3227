#
# Module Imports
import pandas as pd
import matplotlib.pyplot as plt
#
# User Input Parameters
save_to_disk = True  # If set to false, will output to screen
save_to_disk_path = 'graphs/'  # Writes into a same directory folder called 'graphs'
#
# Constants
results_file_path_openmp = 'OPENMP.csv'
results_file_path_openmpi = 'OPENMPI.csv'
results_file_path_openhybrid = 'OPENHYBRID.csv'
time_axis = "Total Elapsed Time Average(seconds)"
thread_axis = "NumCPU"
node_axis = "NumNodes"
#
# File loading into memory
# df_openmp = pd.read_csv(results_file_path_openmp).dropna()
# df_openmpi = pd.read_csv(results_file_path_openmpi).dropna()
# df_openhybrid = pd.read_csv(results_file_path_openhybrid).dropna()
df_openmp = pd.read_csv(results_file_path_openmp)
df_openmpi = pd.read_csv(results_file_path_openmpi)
df_openhybrid = pd.read_csv(results_file_path_openhybrid)
#
def draw_graph(graph_x, x_title, graph_y, y_title, graph_title, to_disk):
    """
    Wrapper function to generate graph visualization
    :param graph_x:
    :param graph_y:
    :param graph_title:
    :param to_disk: When set to True, saves graph to disk
    :return:
    """
    plt.axis([1, max(graph_x), 0, max(graph_y)])
    plt.xlabel(x_title)
    plt.ylabel(y_title)
    plt.title(graph_title)
    plt.plot(graph_x, graph_y)
    plt.title(graph_title)
    if to_disk:
        plt.savefig(save_to_disk_path + graph_title)
    else:
        plt.show()
    plt.close()
#
def generate_results(dataframe, x_title, y_title, iterations, save_to_disk):
    """
    Core method used to retrieve and structure results
    :param dataframe:
    :param x_title:
    :param y_title:
    :param iterations:
    :param save_to_disk:
    :return:
    """
    graph_x, graph_y = [], []
    for index, row in dataframe.iterrows():
        #
        graph_x.append(row[x_title])
        graph_y.append(row[y_title])
        #
        if (index) % iterations:
            graph_title = row['Run Type'] + " - " + str(row['ParticleCount']) + " Particles"
            draw_graph(graph_x, x_title, graph_y, y_title, graph_title, save_to_disk)
#
# OPENMP Iterations
generate_results(dataframe=df_openmp[0:12],  x_title=thread_axis, y_title=time_axis, iterations=12, save_to_disk=save_to_disk)
generate_results(dataframe=df_openmp[12:24], x_title=thread_axis, y_title=time_axis, iterations=12, save_to_disk=save_to_disk)
generate_results(dataframe=df_openmp[24:36], x_title=thread_axis, y_title=time_axis, iterations=12, save_to_disk=save_to_disk)
generate_results(dataframe=df_openmp[36:48], x_title=thread_axis, y_title=time_axis, iterations=12, save_to_disk=save_to_disk)
#
# OPENMPI Iterations
generate_results(dataframe=df_openmpi[0:4],   x_title=node_axis, y_title=time_axis, iterations=4, save_to_disk=save_to_disk)
generate_results(dataframe=df_openmpi[4:8],   x_title=node_axis, y_title=time_axis, iterations=4, save_to_disk=save_to_disk)
generate_results(dataframe=df_openmpi[8:12],  x_title=node_axis, y_title=time_axis, iterations=4, save_to_disk=save_to_disk)
generate_results(dataframe=df_openmpi[12:16], x_title=node_axis, y_title=time_axis, iterations=4, save_to_disk=save_to_disk)
#
# OPENHYBRID Iterations (64)
generate_results(dataframe=df_openhybrid[0:12],  x_title=thread_axis, y_title=time_axis, iterations=12, save_to_disk=save_to_disk)
generate_results(dataframe=df_openhybrid[12:24], x_title=thread_axis, y_title=time_axis, iterations=12, save_to_disk=save_to_disk)
generate_results(dataframe=df_openhybrid[24:36], x_title=thread_axis, y_title=time_axis, iterations=12, save_to_disk=save_to_disk)
generate_results(dataframe=df_openhybrid[36:48], x_title=thread_axis, y_title=time_axis, iterations=12, save_to_disk=save_to_disk)
#
# OPENHYBRID Iterations (1024)
generate_results(dataframe=df_openhybrid[48:60], x_title=thread_axis, y_title=time_axis, iterations=12, save_to_disk=save_to_disk)
generate_results(dataframe=df_openhybrid[60:72], x_title=thread_axis, y_title=time_axis, iterations=12, save_to_disk=save_to_disk)
generate_results(dataframe=df_openhybrid[72:84], x_title=thread_axis, y_title=time_axis, iterations=12, save_to_disk=save_to_disk)
generate_results(dataframe=df_openhybrid[84:96], x_title=thread_axis, y_title=time_axis, iterations=12, save_to_disk=save_to_disk)
#
# OPENHYBRID Iterations (4096)
generate_results(dataframe=df_openhybrid[96:108],  x_title=thread_axis, y_title=time_axis, iterations=12, save_to_disk=save_to_disk)
generate_results(dataframe=df_openhybrid[108:120], x_title=thread_axis, y_title=time_axis, iterations=12, save_to_disk=save_to_disk)
generate_results(dataframe=df_openhybrid[120:132], x_title=thread_axis, y_title=time_axis, iterations=12, save_to_disk=save_to_disk)
generate_results(dataframe=df_openhybrid[132:144], x_title=thread_axis, y_title=time_axis, iterations=12, save_to_disk=save_to_disk)
#
# OPENHYBRID Iterations (16384)
generate_results(dataframe=df_openhybrid[144:156], x_title=thread_axis, y_title=time_axis, iterations=12, save_to_disk=save_to_disk)
generate_results(dataframe=df_openhybrid[156:168], x_title=thread_axis, y_title=time_axis, iterations=12, save_to_disk=save_to_disk)
generate_results(dataframe=df_openhybrid[168:180], x_title=thread_axis, y_title=time_axis, iterations=12, save_to_disk=save_to_disk)
generate_results(dataframe=df_openhybrid[180:192], x_title=thread_axis, y_title=time_axis, iterations=12, save_to_disk=save_to_disk)


