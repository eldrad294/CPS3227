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
        void ComputeForces(std::vector<Particle> &p_bodies,std::vector<Particle> &p_localbodies, float p_gravitationalTerm, int world_rank, int world_size)
        {
            Vector2 direction, force, acceleration;
            float distance;
            unsigned balanced_split, min, max;

            // Calculating partition split, and current range of bodies to calculate for current node
            balanced_split = p_bodies.size() / world_size;
            min = balanced_split * world_rank;
            max = min + balanced_split - 1;

            // Cater for uneven partition splits
            if(world_rank == world_size-1)
            {
               max = p_bodies.size();
            }

            // Creating local vector of bodies upon which to perform particle lookup
            p_localbodies.assign(p_bodies.begin() + min, p_bodies.begin() + max);

            #pragma omp parallel for default(none) private(force, acceleration) shared(p_localbodies, p_bodies,p_gravitationalTerm)
            for (size_t j = 0; j < p_localbodies.size(); ++j)
            {
                Particle &p1 = p_localbodies[j];
            
                force = 0.f, acceleration = 0.f; 
            
                #pragma omp parallel for default(none) private(direction,distance,force) shared(p_bodies,j,p1)
                for (size_t k = 0; k < p_bodies.size(); ++k)
                {
                    if (k == j) continue;
                
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
        }

        /*
        * Update particle positions
        */
        void MoveBodies(std::vector<Particle> &p_bodies, std::vector<Particle> &p_localbodies, float p_deltaT, int world_rank, int world_size)
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
            p_localbodies.assign(p_bodies.begin() + min, p_bodies.begin() + max);

            #pragma omp parallel for default(none) shared(p_localbodies, p_bodies, p_deltaT)
            for (size_t j = 0; j < p_localbodies.size(); ++j)
            {
                p_localbodies[j].Position += p_localbodies[j].Velocity * p_deltaT;
            }
        }
};
#endif
