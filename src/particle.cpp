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

        Particle(float p_Mass, float p_X, float p_Y) 
        { 
            Position = Vector2(p_X, p_Y);
            Velocity = Vector2(0.f, 0.f); // Initialize particle with velocity vector of 0
            Mass = p_Mass;
        }

        /*
        * Compute forces of particles exerted on one another
        */
        std::vector<Particle> ComputeForces(std::vector<Particle> &p_bodies, float p_gravitationalTerm, int world_rank, int world_size)
        {
            Vector2 direction, force, acceleration;
            float distance;
            unsigned balanced_split, min, max;

            // Calculating partition split, and current range of bodies to calculate for current node
            balanced_split = p_bodies.size() / world_size;
            min = balanced_split * world_rank;
            max = min + balanced_split + 1;

            // Cater for uneven partition splits
            if(world_rank == world_size-1)
            {
               max = p_bodies.size();
            }

            // Creating local vector of bodies upon which to perform particle lookup
            std::vector<Particle> local_bodies(&p_bodies[min], &p_bodies[max]);

            //#pragma omp parallel for default(none) private(force, acceleration) shared(p_bodies,p_gravitationalTerm)
            for (size_t j = 0; j < local_bodies.size(); ++j)
            {
                min++;
                Particle &p1 = p_bodies[min];
            
                force = 0.f, acceleration = 0.f;
                
            
                #pragma omp parallel for default(none) private(direction,distance,force) shared(local_bodies, p_bodies,j,min,p1)
                for (size_t k = 0; k < p_bodies.size(); ++k)
                {
                    if (k == min) continue;
                
                    Particle &p2 = p_bodies[k];
                    
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
            }
            return local_bodies;
        }

        /*
        * Update particle positions
        */
        std::vector<Particle> MoveBodies(std::vector<Particle> &p_bodies, float p_deltaT, int world_rank, int world_size)
        //void MoveBodies(std::vector<Particle> p_bodies, float p_deltaT)
        {
            unsigned balanced_split, min, max;

            // Calculating balanced split, and current range of bodies to calculate for current node
            balanced_split = p_bodies.size() / world_size;
            min = balanced_split * world_rank;
            max = min + balanced_split + 1;

            // Cater for uneven partition splits
            if(world_rank == world_size-1)
            {
               max = p_bodies.size();
            }

            // Creating local vector of bodies upon which to perform particle lookup
            std::vector<Particle> local_bodies(&p_bodies[min], &p_bodies[max]);

            #pragma omp parallel for default(none) shared(local_bodies, p_bodies, p_deltaT)
            for (size_t j = 0; j < local_bodies.size(); ++j)
            {
                local_bodies[j].Position += local_bodies[j].Velocity * p_deltaT;
            }
 
            return local_bodies;
            // // Parallel Method
            // std::vector<Particle> temp_list;
            // #pragma omp parallel default(none) shared(p_bodies, p_deltaT) private(temp_list)
            // {
            //     #pragma omp for schedule(static)
            //     for (size_t j = 0; j < p_bodies.size(); ++j)
            //     {
            //         temp_list.push_back(p_bodies[j]);
            //         temp_list[j].Position += p_bodies[j].Velocity * p_deltaT;
            //     }
            //     p_bodies.clear();
            //     #pragma omp for schedule(static) ordered //Barrier
            //     for(int i=0; i < omp_get_num_threads(); i++)
            //     {
            //         #pragma omp ordered // Ensures that vectors are concatenated in correct order
            //         p_bodies.insert(p_bodies.end(),temp_list.begin(),temp_list.end());
            //     }
            // }
        }
};
#endif
