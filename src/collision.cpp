//      collision.cpp
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

#include "collision.hpp"

namespace ogle {

CollisionBehavior::CollisionBehavior() {
}

CollisionBehavior::~CollisionBehavior() {
}

void CollisionBehavior::particlesCollided(Particle* const one, Particle* const two) {

}

void CollisionBehavior::boundsCollided(Particle* const particle, const Rect& bounds) {
    if(particle->getX() <= bounds.x || particle->getX() >= bounds.w) {
        // invert x
        particle->setXv(-particle->getXv());
        particle->setGravity(particle->getGravity() - 0.005f);
    } else if (particle->getY() <= bounds.y) {
        particle->setY(0.0f);
        particle->setYv(0.0f);
        particle->setXv(0.0f);
    } else if (particle->getY() >= bounds.h) {
        particle->setYv(0.0f);
        particle->setXv(0.0f);
    }
}

//==============================================================================

CollisionDetector::CollisionDetector(const Rect& bounds) :
        m_bounds(bounds) {
}

CollisionDetector::~CollisionDetector() {
}

void CollisionDetector::fireBoundsCollided(Particle* const one, const Rect& rect) {
    std::vector<CollisionBehavior*>::iterator it;
    for(it = m_behaviors.begin(); it < m_behaviors.end(); it++) {
        CollisionBehavior* cb = *it;
        cb->boundsCollided(one, rect);
    }
}

void CollisionDetector::fireParticlesCollided(Particle* const one, Particle* const two) {
    std::vector<CollisionBehavior*>::iterator it;
    for(it = m_behaviors.begin(); it < m_behaviors.end(); it++) {
        CollisionBehavior* cb = *it;
        cb->particlesCollided(one, two);
    }
}

void CollisionDetector::addBehavior(CollisionBehavior* const behavior) {
    m_behaviors.push_back(behavior);
}


void CollisionDetector::checkCollisions(std::vector<Particle*> particles) {
    /* 
     * This function will iterate over a one dimensional vector (duh), and it will
     * compare all the Particles with each other. This comparison will be done only
     * once per set: suppose we have the particles A B C and D. The check will be
     * done like:
     * 
     * A - B, A - C, A - D (first loop)
     * B - C, B - D (second loop)
     * C - D (third loop)
     * 
     * That means B - A will never happen, or C - A etc; what would be the point
     * to compare them twice?
     */
    std::vector<Particle*>::iterator it1;
    for(it1 = particles.begin(); it1 < particles.end(); it1++) {
        // first particle in iteration.
        Particle* p1 = *it1; 
        
        // only check for collisions when this particle is enabled to
        if(!p1->isCollisionEligible()) {
            continue;
        }
        
        // check first for 'out of bounds' collisions:
        if (p1->getX() <= m_bounds.x || 
            p1->getX() >= m_bounds.w ||
            p1->getY() <= m_bounds.y ||
            p1->getY() >= m_bounds.h) {
            
            fireBoundsCollided(p1, m_bounds);
            // no need really to check for particle collision?
            // XXX: evaluate this!
            continue;
        }
        
        std::vector<Particle*>::iterator it2;
        for(it2 = (it1 + 1); it2 < particles.end(); it2++) {
            // particle to check the first one with.
            Particle* p2 = *it2;
            
            // do they intersect?
            if(p1->getBoundary().intersects(p2->getBoundary())) {
                fireParticlesCollided(p1, p2);
            }
        }
    }
}

} // namespace ogle
