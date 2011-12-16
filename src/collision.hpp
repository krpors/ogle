//      collision.hpp
//      
//      Copyright 2010 Kevin Pors <krpors@users.sf.net>
//      
//      This program is free software; you can redistribute it and/or modify
//      it under the terms of the GNU General Public License as published by
//      the Free Software Foundation; either version 2 of the License, or
//      (at your option) any later version.
//      
//      This program is distributed in the hope that it will be useful,
//      but WITHOUT ANY WARRANTY; without even the implied warranty of
//      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//      GNU General Public License for more details.
//      
//      You should have received a copy of the GNU General Public License
//      along with this program; if not, write to the Free Software
//      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
//      MA 02110-1301, USA.

#ifndef COLLISION_HPP
#define COLLISION_HPP

#include "core.hpp"

#include <GL/gl.h>
#include <iostream>
#include <vector>
#include <algorithm>

namespace ogle {

/**
 * Class to describe behavior of particles after collision happened. This is a
 * base class which can be extended for other types of behavior.
 */
class CollisionBehavior {
public:
    CollisionBehavior();
    
    virtual ~CollisionBehavior();
    
    void particlesCollided(Particle* const one, Particle* const two);
    
    void boundsCollided(Particle* const particle, const Rect& bounds);
};

//==============================================================================

/**
 * The collision detecter checks whether collisions have occurred within the 
 * bounds of the current viewport, or against other particles.
 */
class CollisionDetector {
private:

    /// The viewing plane bounds. 
    Rect m_bounds;
    
    /// Vector with behaviors.
    std::vector<CollisionBehavior*> m_behaviors;
    
    void fireParticlesCollided(Particle* const one, Particle* const two);
    
    void fireBoundsCollided(Particle* const particle, const Rect& rect);
    
public:
    /**
     * Creates the CollisionDetector with the specified bounds.
     * 
     * @param The bounds of the plane.
     */
    CollisionDetector(const Rect& bounds);
    
    /**
     * Destroys the collision detector.
     */
    ~CollisionDetector();
    
    /**
     * Adds a type of collision behavior to this CollisionDetector.
     * 
     * @param behavior The behavior.
     */
    void addBehavior(CollisionBehavior* const behavior);
    
    /**
     * Checks for collisions in the given particle vector. Since it's a one
     * dimensional array of Particle* objects, this will do internal comparisons.
     * This will run in a complexity of <code>O(n - 1)</code>.
     */
    void checkCollisions(std::vector<Particle*> particles);
};

} // namespace ogle


#endif // COLLISION_HPP
