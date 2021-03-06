//Header Guardians
#ifndef _MYHEADER_H_
#define _MYHEADER_H_
// Library Imports
#include <algorithm>
#include <vector>
#include "vector2.h"

class Particle
{        
    public:
        Vector2 Position;
        Vector2 Velocity;
        float	Mass;

        Particle(){}

        Particle(float p_Mass, float p_X, float p_Y, float p_Z, float p_V) 
        { 
            Position = Vector2(p_X, p_Y);
            Velocity = Vector2(p_Z, p_V); 
            Mass = p_Mass;
        }

        /*
        * Compute forces of particles exerted on one another
        */
        void ComputeForces(int body_count, float *p_mass, float *p_velocity_0, float *p_velocity_1, float *p_position_0, float *p_position_1, float *p_local_velocity_0, float *p_local_velocity_1, float p_gravitationalTerm, int world_rank, int world_size)
        {
            Vector2 direction, force, acceleration;
            float distance = .0;
            short balanced_split = 0;
            short min = 0;
            short max = 0;

            // Calculating partition split, and current range of bodies to calculate for current node
            balanced_split = body_count / world_size;
            min = balanced_split * world_rank;
            max = min + balanced_split - 1;

            // Cater for uneven partition splits
            if(world_rank == world_size-1)
            {
               max = body_count;
            }
            
            #pragma omp parallel for default(none) firstprivate(min,max,p_mass,body_count,p_gravitationalTerm,force, acceleration, distance, direction, p_local_velocity_0,p_local_velocity_1,p_position_0,p_position_1,p_velocity_0,p_velocity_1)
            for (int j = min; j <= max; ++j)
            {
                Particle p1(p_mass[j], p_position_0[j], p_position_1[j], p_velocity_0[j], p_velocity_1[j]);
            
                force = 0.f, acceleration = 0.f; 
            
                #pragma omp parallel for default(none) shared(distance, force, direction,p_velocity_0,p_velocity_1,p_position_0,p_position_1) firstprivate(min,p_mass,body_count,p1)
                for (int k = 0; k < body_count; ++k)
                {
                    if (k == min) continue;

                    Particle p2(p_mass[k], p_position_0[k], p_position_1[k], p_velocity_0[k], p_velocity_1[k]);
                    
                    // Compute direction vector
                    direction = p2.Position - p1.Position;
                    
                    // Limit distance term to avoid singularities
                    distance = std::max<float>( 0.5f * (p2.Mass + p1.Mass), fabs(direction.Length()) );

                    // Accumulate force
                    force += direction / (distance * distance * distance) * p2.Mass; 
                }
                        
                // Compute acceleration for body 
                acceleration = force * p_gravitationalTerm;
                
                // Integrate velocity (m/s)
                p1.Velocity += acceleration;
                
                // Update Velocities
                p_local_velocity_0[j-min] = p1.Velocity[0];
                p_local_velocity_1[j-min] = p1.Velocity[1];
            }
            // std::cout << "p_local_velocity_0: " << p_local_velocity_0[30] << " p_local_velocity_1: " << p_local_velocity_1[30] << " WorldRank: " << world_rank << "\n";
        }

        /*
        * Update particle positions
        */
        void MoveBodies(int body_count, float *p_velocity_0, float *p_velocity_1, float *p_position_0, float *p_position_1, float *p_local_position_0, float *p_local_position_1, float p_deltaT, int world_rank, int world_size)
        {
            short balanced_split = 0; 
            short min = 0; 
            short max = 0;

            // Calculating partition split, and current range of bodies to calculate for current node
            balanced_split = body_count / world_size;
            min = balanced_split * world_rank;
            max = min + balanced_split - 1;

            // Cater for uneven partition splits
            if(world_rank == world_size-1)
            {
               max = body_count;
            }

            #pragma omp parallel for default(none) shared(p_local_position_0, p_local_position_1, p_velocity_0,p_velocity_1,p_position_0,p_position_1) firstprivate(p_deltaT,min,max)
            for (int j = min; j <= max; ++j)
            {
                p_local_position_0[j-min] = p_position_0[j] + (p_velocity_0[j] * p_deltaT);
                p_local_position_1[j-min] = p_position_1[j] + (p_velocity_1[j] * p_deltaT);
            }
        }
};
#endif
