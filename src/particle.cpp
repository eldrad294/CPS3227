//Header Guardians
#ifndef _MYHEADER_H_
#define _MYHEADER_H_
// Library Imports
#include <algorithm>
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
        void ComputeForces(std::vector<Particle> &p_bodies, float p_gravitationalTerm)
        {
            Vector2 direction, force, acceleration;
            float distance;

            //#pragma omp parallel for default(none) private(force,acceleration,direction,distance) shared(p_bodies,p_gravitationalTerm)
            #pragma omp parallel for default(none) private(force, acceleration) shared(p_bodies,p_gravitationalTerm)
            for (size_t j = 0; j < p_bodies.size(); ++j)
            {
                Particle &p1 = p_bodies[j];
            
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
        void MoveBodies(std::vector<Particle> &p_bodies, float p_deltaT)
        {
            #pragma omp parallel for default(none) shared(p_bodies, p_deltaT)
            for (size_t j = 0; j < p_bodies.size(); ++j)
            {
                p_bodies[j].Position += p_bodies[j].Velocity * p_deltaT;
            }

            // #pragma omp parallel 
            // {
            //     Particle private_body;
            //     #pragma omp for nowait
            //     for (size_t j = 0; j < p_bodies.size(); ++j)
            //     {
            //         private_body.Position = p_bodies[j].Velocity * p_deltaT;
            //         #pragma omp critical
            //         p_bodies[j].Position += private_body.Position;
            //     }
            // }
        }
};
#endif