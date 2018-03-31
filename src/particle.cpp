// Library Imports
#include <algorithm>
#include "vector2.h"

class Particle
{
    private:
        Vector2 Position;
        Vector2 Velocity;
        float	Mass;
    public:
        Particle(float p_Mass, float p_X, float p_Y) 
        { 
            Position = Vector2(p_X, p_Y);
            Velocity = Vector2(0.f, 0.f); // Initialize particle with velocity vector of 0
            Mass = p_Mass;
        }

        Vector2 getPosition()
        {
            return Position;
        }

        Vector2 getVelocity()
        {
            return Velocity;
        }

        float getMass()
        {
            return Mass;
        }
};