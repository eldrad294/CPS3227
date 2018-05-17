*********************************************************************************************************
******************************************      README         ******************************************
****************************************** CPS3227 Assignment  ******************************************
****************************************** INSTRUCTIONS BELOW! ******************************************
*********************************************************************************************************


DIRECTORY LAYOUT
*********************************************************************************************************
.
|- build                                 #
  |- main                                # Final Build
|- docs                                  # 
  |- assign_2018.pdf                     # Assignment Specification
  |- FinalReport.docx                    # Submitted Report Documentation
  |- Plagiarism_Declaration_Form.pdf     # Signed Plagiarism Form
|- input                                 #       
  |- input_64.txt                        # Input File (64 Particles)
  |- input_1024.txt                      # Input File (1024 Particles)
  |- input_4096.txt                      # Input File (4096 Particles)
  |- input_16384.txt                     # Input File (16384 Particles)
|- output                                #
  |- OPENHYBRID_64                       # OpenMP + MPI 64 particle output iterations
  |- OPENHYBRID_1024                     # OpenMP + MPI 1024 particle output iterations
  |- OPENHYBRID_4096                     # OpenMP + MPI 4096 particle output iterations
  |- OPENHYBRID_16384                    # OpenMP + MPI 16384 particle output iterations
  |- OPENMP_64                           # OpenMP 64 particle output iterations
  |- OPENMP_1024                         # OpenMP 1024 particle output iterations
  |- OPENMP_4096                         # OpenMP 4096 particle output iterations
  |- OPENMP_16384                        # OpenMP 16384 particle output iterations
  |- OPENMPI_64                          # Open MPI 64 particle output iterations  
  |- OPENMPI_1024                        # Open MPI 1024 particle output iterations
  |- OPENMPI_4096                        # Open MPI 4096 particle output iterations
  |- OPENMPI_16384                       # Open MPI 16384 particle output iterations
|- report                                #
  |- graphs                              # Contains timing plots/graphs
  |- hybrid_run                          # Contains raw results for hybrid runs (Open MP = Open MPI)
  |- openmp_run                          # Contains raw results for Open MP runs
  |- openmpi_run                         # Contains raw results for Open MPI runs
  |- graph_generator.py                  # Python script used to generate graphs from csv files
  |- OPENHYBRID.csv                      # Result sheet for Open HYBRID timings
  |- OPENHYBRID_Highlighted.xlsx         # Result sheet for Open HYBRID timings, with some higlighted anamolies
  |- OPENMP.csv                          # Result sheet for Open MP timings
  |- OPENMPI.csv                         # Result sheet for Open MPI timings
|- shellscripts                          #
  |- runner_hybrid_1                     # Shell script for 1 node hybrid run
  |- runner_hybrid_2                     # Shell script for 2 node hybrid run
  |- runner_hybrid_3                     # Shell script for 3 node hybrid run
  |- runner_hybrid_4                     # Shell script for 4 node hybrid run
  |- runner_mpi_1                        # Shell script for 1 node MPI run
  |- runner_mpi_2                        # Shell script for 2 node MPI run
  |- runner_mpi_3                        # Shell script for 3 node MPI run
  |- runner_mpi_4                        # Shell script for 4 node MPI run
  |- runner_openmp                       # Shell script for OpenMP run (1-12 threads)
  |- test_run                            # Test shell script
|- src                                   #
  |- filehandler.cpp                     # C++ class for file handling interactions
  |- main.cpp                            # C++ main module
  |- particle.cpp                        # C++ class for particle interactions
  |- vector2.h                           # C++ Provided C methods for defining particle structure
|- compiler_hybrid.sh                    # Script to compile hybrid code
|- compiler_mpi.sh                       # Script to compile MPI code alone
|- compiler_openmp.sh                    # Script to compile Open MP code alone
|- README.txt                            # The file you are reading
*********************************************************************************************************


INSTRUCTIONS - RUNNING THE FINAL BUILD
*********************************************************************************************************
1) Upload respective shell scripts on Albert
2) Upload final build on Albert
3) Upload input files on Albert
4) Run shell script 
*********************************************************************************************************