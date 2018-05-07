#
# Module Imports
import pandas as pd
import matplotlib.pyplot as plt
#
# Constants
results_file_path_openmp = 'OPENMP.csv'
results_file_path_openmpi = 'OPENMPI.csv'
results_file_path_openhybrid = 'OPENHYBRID.csv'
#
# File loading into memory
df_openmp = pd.read_csv(results_file_path_openmp)
df_openmpi = pd.read_csv(results_file_path_openmpi)
df_openhybrid = pd.read_csv(results_file_path_openhybrid)
#
# OPENMP Iterations
graph_x, graph_y = [], []
iterations = 12
for index, row in df_openmp.iterrows():
    #
    graph_x.append(row['NumCPU'])
    graph_y.append(row['Total Elapsed Average(s)'])
    #
    if index % iterations == 0:
        graph_title = row['Run Type'] + " (" + str(row['NumNodes']) + ") - " + str(row['ParticleCount']) + " Particles"
        plt.axis([0, max(graph_x), 0, max(graph_y)])
        plt.plot(graph_x, graph_y)
        plt.title(graph_title)
        plt.show()
        graph_x, graph_y = [], []
