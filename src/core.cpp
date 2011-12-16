//      core.cpp
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

#include "core.hpp"
#include "utils.hpp"

namespace ogle {

// Initialization of default colors:
const Color Color::BLACK;
const Color Color::RED    (1.0f);
const Color Color::GREEN  (0.0f, 1.0f);
const Color Color::BLUE   (0.0f, 0.0f, 1.0f);
const Color Color::ORANGE (1.0f, 0.5f, 0.5f);
const Color Color::YELLOW (1.0f, 1.0f, 0.0f);

Color::Color(const GLclampf& r, const GLclampf& g, const GLclampf& b, const GLclampf& a) :
        m_r(r), m_g(g), m_b(b), m_a(a) {
    
}

Color::~Color() {
}

void Color::setR(const GLclampf& r) {
    m_r = r;
}

void Color::setG(const GLclampf& g) {
    m_g = g;
}

void Color::setB(const GLclampf& b) {
    m_b = b;
}

void Color::setA(const GLclampf& a) {
    m_a = a;
}

GLclampf Color::getR() const {
    return m_r;
}

GLclampf Color::getG() const {
    return m_g;
}

GLclampf Color::getB() const {
    return m_b;
}

GLclampf Color::getA() const {
    return m_a;
}

//==============================================================================

Rect::Rect(const GLfloat& x, const GLfloat& y, const GLfloat& w, const GLfloat& h) {
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
}

Rect::~Rect() {
}

bool Rect::intersects(const Rect& rect) const {
    const GLfloat& x2  = rect.x;
    const GLfloat& y2  = rect.y;
    const GLfloat  x2w = rect.x + rect.w;
    const GLfloat  y2h = rect.y + rect.h;
    
    bool collide_left   = (x + w) >= x2;
    bool collide_right  = x <= x2w;
    bool collide_top    = y <= y2h;
    bool collide_bottom = (y + h) >= y2;
    
    return collide_left && collide_right && collide_top && collide_bottom;
}

//==============================================================================

Object::Object(const GLfloat& x, const GLfloat& y, const GLfloat& z) :
        m_x(x), 
        m_y(y), 
        m_z(z), 
        m_width(1.0f), 
        m_height(1.0f),
        m_collisionEligible(true) {
}

Object::~Object() {
}

void Object::setPosition(const GLfloat& x, const GLfloat& y, const GLfloat& z) {
    m_x = x;
    m_y = y;
    m_z = z;
}

void Object::setX(const GLfloat& x) {
    m_x = x;
}

void Object::setY(const GLfloat& y) {
    m_y = y;
}

void Object::setZ(const GLfloat& z) {
    m_z = z;
}

void Object::setWidth(const GLfloat& w) {
    m_width = w;
}

void Object::setHeight(const GLfloat& h) {
    m_height = h;
}

void Object::setCollisionEligible(bool eligible) {
    m_collisionEligible = eligible;
}

const GLfloat& Object::getX() const {
    return m_x;
}

const GLfloat& Object::getY() const {
    return m_y;
}

const GLfloat& Object::getZ() const {
    return m_z;
}

const GLfloat& Object::getWidth() const {
    return m_width;
}

const GLfloat& Object::getHeight() const {
    return m_height;
}

const Rect& Object::getBoundary() {
    m_boundaryBox.x = m_x;
    m_boundaryBox.y = m_y;
    m_boundaryBox.w = m_width;
    m_boundaryBox.h = m_height;
    return m_boundaryBox;   
}

bool Object::isCollisionEligible() const {
    return m_collisionEligible;
}

//==============================================================================

Axis::Axis(const GLfloat& max) :
        m_max(max) {
}

Axis::~Axis() {
}

void Axis::render() {
    // this axis does not have a material, nor does lighting have an effect on
    // the appearance of this axis.
    glDisable(GL_LIGHTING);
    glBegin(GL_LINES);
        // draw the main axis here in green
        glColor4f(0.0f, 1.0f, 0.0f, 1.0f); 
        glVertex3f(-m_max, 0.0f, 0.0f); glVertex3f(m_max, 0.0f, 0.0f); // x-axis, green
        glColor4f(1.0f, 1.0f, 0.0f, 1.0f); 
        glVertex3f(0.0f, -m_max, 0.0f); glVertex3f(0.0f, m_max, 0.0f); // y-axis, yellow
        glColor4f(1.0f, 0.0f, 1.0f, 1.0f); 
        glVertex3f(0.0f, 0.0f, -m_max); glVertex3f(0.0f, 0.0f, m_max); // z-axis, cyan
    glEnd();
    glEnable(GL_LIGHTING);
}

//==============================================================================

Box::Box() :
        Object(0.0f, 0.0f, 0.0f),
        m_depth(1.0f) {
}

Box::~Box() {
}

void Box::render() {
    // faces are rendered counter clockwise, starting 'top-right'.
    float mcolor[] = { 1.0f, 0.0f, 0.0f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mcolor);
    // front faces are counter-clockwise
    glFrontFace(GL_CCW);
    glBegin(GL_QUADS);
        // 'front' face
        Vertex a(getX() + getWidth(), getY() + getHeight(), getZ());
        Vertex b(getX(), getY() + getHeight(), getZ());

        Vertex n1 = Vertex::calcNormal(a,b);
        n1.normalize();
        glNormal3f(n1.x, n1.y, n1.z);
        
        glVertex3f(getX() + getWidth(), getY() + getHeight(), getZ());
        glVertex3f(getX(), getY() + getHeight(), getZ());
        glVertex3f(getX(), getY(), getZ());
        glVertex3f(getX() + getWidth(), getY(), getZ());
        // 'back' face
        glNormal3f(0.0f, 0.0f, -1.0f);
        glVertex3f(getX() + getWidth(), getY() + getHeight(), getZ() + m_depth);
        glVertex3f(getX(), getY() + getHeight(), getZ() + m_depth);
        glVertex3f(getX(), getY(), getZ() + m_depth);
        glVertex3f(getX() + getWidth(), getY(), getZ() + m_depth);
        // 'top' face
        glNormal3f(0.0f, 1.0f, 0.0f);
        glVertex3f(getX() + getWidth(), getY() + getHeight(), getZ() + m_depth);
        glVertex3f(getX(), getY() + getHeight(), getZ() + m_depth);
        glVertex3f(getX(), getY() + getHeight(), getZ());
        glVertex3f(getX() + getWidth(), getY() + getHeight(), getZ());
        // 'bottom' face
        glNormal3f(0.0f, -1.0f, 0.0f);
        glVertex3f(getX() + getWidth(), getY(), getZ() + m_depth);
        glVertex3f(getX(), getY(), getZ() + m_depth);
        glVertex3f(getX(), getY(), getZ());
        glVertex3f(getX() + getWidth(), getY(), getZ());
        // 'left' face
        glNormal3f(-1.0f, 0.0f, 0.0f);
        glVertex3f(getX(), getY(), getZ());
        glVertex3f(getX(), getY() + getHeight(), getZ());
        glVertex3f(getX(), getY() + getHeight(), getZ() + m_depth);
        glVertex3f(getX(), getY(), getZ() + m_depth);
        // 'right' face
        glNormal3f(1.0f, 0.0f, 0.0f);
        glVertex3f(getX() + getWidth(), getY(), getZ());
        glVertex3f(getX() + getWidth(), getY() + getHeight(), getZ());
        glVertex3f(getX() + getWidth(), getY() + getHeight(), getZ() + m_depth);
        glVertex3f(getX() + getWidth(), getY(), getZ() + m_depth);
        
    glEnd();
}

//==============================================================================

Particle::Particle() : 
        Object(0.0f, 0.0f, 0.0f), 
        m_active(true), 
        m_life(10.0f),
        m_xv(0.0f), 
        m_yv(0.0f), 
        m_zv(0.0f),
        m_gravity(-0.015f), 
        m_fadespeed(0.15f) {
}

Particle::~Particle() {
}

void Particle::setActive(bool active) {
    m_active = active;
}

void Particle::setLife(const GLfloat& life) {
    // only set a life when it's bigger than 0. No need to get an immense negative
    // number, so if m_life is already smaller than 0, stop subtracting.
    m_life = std::max(0.0f, life);
}

void Particle::setXv(const GLfloat& xv) {
    m_xv = xv;
}

void Particle::setYv(const GLfloat& yv) {
    m_yv = yv;
}

void Particle::setZv(const GLfloat& zv) {
    m_zv = zv;
}

void Particle::setColor(const Color& color) {
    m_color = color;
}

void Particle::setGravity(const GLfloat& gravity) {
    m_gravity = gravity;
}

void Particle::setFadeSpeed(const GLfloat& fs) {
    m_fadespeed = fs;
}

bool Particle::isActive() const {
    return m_active;
}

GLfloat Particle::getLife() const {
    return m_life;
}

GLfloat Particle::getXv() const {
    return m_xv;
}

GLfloat Particle::getYv() const {
    return m_yv;
}

GLfloat Particle::getZv() const {
    return m_zv;
}

Color Particle::getColor() const {
    return m_color;
}

GLfloat Particle::getGravity() const {
    return m_gravity;
}

GLfloat Particle::getFadeSpeed() const {
    return m_fadespeed;
}

void Particle::render() {
    if (m_life > 0.0f && m_active) {
        glColor4f(m_color.getR(), m_color.getG(), m_color.getB(), m_color.getA());
        glVertex3f(m_x, m_y, m_z);
        glVertex3f(m_x, m_y + m_height, m_z);
        glVertex3f(m_x + m_width, m_y + m_height, m_z);
        glVertex3f(m_x + m_width, m_y, m_z);
    }
}

//==============================================================================

ParticleGenerator::ParticleGenerator(const GLfloat& x, const GLfloat& y) :
        Object(x, y), 
        m_particles(NULL),
        m_max(100), 
        m_particleLife(100.0f) {
            
    // init default spreads:
    m_spread_x[0]       = -1.0f;
    m_spread_x[1]       =  1.0f;
    m_spread_y[0]       = -1.0f;
    m_spread_y[1]       =  1.0f;
    m_spread_z[0]       =  0.0f;
    m_spread_z[1]       =  0.0f;
    m_spread_gravity[0] = -0.03f;
    m_spread_gravity[1] = -0.01f;
    m_spread_fade[0]    = -1.5f;
    m_spread_fade[1]    = -0.1f;
    
    initialize();
}

ParticleGenerator::~ParticleGenerator() {
    // Remove our particles (deallocate array)
    delete[] m_particles;
}

void ParticleGenerator::initialize() {
    // start initializing all the particles in the array, only if NULL.
    if(m_particles == NULL) {
        m_particles = new Particle[m_max];
    }
    for(GLuint i = 0; i < m_max; i++) {
        initParticle(m_particles[i]);
    }
}

void ParticleGenerator::initParticle(Particle& p) {
    // initialize some random numbers here.
    float dx = sf::Randomizer::Random(m_spread_x[0],        m_spread_x[1]);
    float dy = sf::Randomizer::Random(m_spread_y[0],        m_spread_y[1]);
    float dz = sf::Randomizer::Random(m_spread_z[0],        m_spread_z[1]);
    float gv = sf::Randomizer::Random(m_spread_gravity[0],  m_spread_gravity[1]);
    float fs = sf::Randomizer::Random(m_spread_fade[0],     m_spread_fade[1]);
    
    Color c(1.0f);
    
    // starting colors:
    p.setColor(c);
    // init all particles at the origin of this generator, adding some randomness.
    p.setPosition(m_x + dx, m_y + dy);
    // set time to live of all the particles to a value:
    p.setLife(m_particleLife);
    // set directions of each individual particle to a random value:
    p.setXv(dx);
    p.setYv(dy);
    p.setZv(dz);
    // set default gravity
    p.setGravity(gv);
    // fade speed
    p.setFadeSpeed(fs);
    // re-enable collision
    p.setCollisionEligible(true);
    // set activity
    p.setActive(true);
}

void ParticleGenerator::setMaxParticles(const GLuint& max) {
    m_max = max;
}

void ParticleGenerator::setSpreadX(const GLfloat& min, const GLfloat& max) {
    m_spread_x[0] = min;
    m_spread_x[1] = max;
}

void ParticleGenerator::setSpreadY(const GLfloat& min, const GLfloat& max) {
    m_spread_y[0] = min;
    m_spread_y[1] = max;
}

void ParticleGenerator::setSpreadZ(const GLfloat& min, const GLfloat& max) {
    m_spread_z[0] = min;
    m_spread_z[1] = max;
}

void ParticleGenerator::setSpreadGravity(const GLfloat& min, const GLfloat& max) {
    m_spread_gravity[0] = min;
    m_spread_gravity[1] = max;
}

void ParticleGenerator::setSpreadFade(const GLfloat& min, const GLfloat& max) {
    m_spread_fade[0] = min;
    m_spread_fade[1] = max;
}

void ParticleGenerator::setParticleLife(const GLfloat& particleLife) {
    m_particleLife = particleLife;
}

const GLfloat& ParticleGenerator::getParticleLife() const {
    return m_particleLife;
}

const GLuint& ParticleGenerator::getMaxParticles() const {
    return m_max;
}

Particle* const ParticleGenerator::getParticles() const {
    return m_particles;
}

void ParticleGenerator::render() {   
    glBegin(GL_QUADS);
        for(GLuint i = 0; i < m_max; i++) {   
            Particle& p = m_particles[i];
            if(p.getLife() > 0.0f && p.isActive()) {
                p.setX(p.getX() + p.getXv());
                p.setY(p.getY() + p.getYv());
                p.setZ(p.getZ() + p.getZv());
                
                p.setYv(p.getYv() + p.getGravity());
                
                p.setLife(p.getLife() + p.getFadeSpeed());
                
                // determine color:
                GLfloat percentage = (p.getLife() / m_particleLife) * 100.0f;
                Color c;
                if(percentage >= 70.0f) {
                    c = Color::RED;
                } else if (percentage >= 50.0f && percentage < 70.0f) {
                    c = Color::ORANGE;
                } else if (percentage >= 0.0f && percentage < 50.0f) {
                    c = Color::YELLOW;
                }
                // set alpha value based on percentage of life. Lesser life, 
                // lesser alpha, it will dissapear eventually.
                c.setA(p.getLife() / m_particleLife);
                p.setColor(c);
                
                // last but not least, render the individual particle.
                p.render();
            } else {
                initParticle(p);
            }
        }
    glEnd();
}


} // namespace ogle
