//      core.hpp
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

#ifndef CORE_HPP
#define CORE_HPP

#include <SFML/Window.hpp>

#include <iostream>
#include <math.h>
#include <algorithm>
#include <vector>

#include <GL/gl.h>

namespace ogle {

/**
 * Color class.
 */
class Color {
private:
    /// Red component, clamped to [0.0f, 1.0f]
    GLclampf m_r;
    
    /// Green component, clamped to [0.0f, 1.0f]
    GLclampf m_g;
    
    /// Blue component, clamped to [0.0f, 1.0f]
    GLclampf m_b;
    
    /// Alpha component, clamped to [0.0f, 1.0f]
    GLclampf m_a;
    
public:
    /**
     * Creates a color instance.
     * 
     * @param r The red component (clamped). Default value is 0.0f.
     * @param g The green component (clamped). Default value is 0.0f.
     * @param b The blue component (clamped). Default value is 0.0f.
     * @param a The alpha component (clamped). Default value is 1.0f (fully opaque).
     */
    Color(const GLclampf& r = 0.0f, const GLclampf& g = 0.0f, const GLclampf& b = 0.0f, const GLclampf& a = 1.0f);
    ~Color();
    
    /**
     * Sets the red component.
     * 
     * @param r The red component (clamped).
     */
    void setR(const GLclampf& r);

    /**
     * Sets the green component.
     * 
     * @param r The green component (clamped).
     */
    void setG(const GLclampf& g);

    /**
     * Sets the blue component.
     * 
     * @param r The blue component (clamped).
     */
    void setB(const GLclampf& b);
    
    /**
     * Sets the alpha component.
     * 
     * @param r The alpha component (clamped).
     */
    void setA(const GLclampf& a);
    
    /**
     * Gets the red component.
     * 
     * @return The red component, clamped.
     */
    GLclampf getR() const;

    /**
     * Gets the red component.
     * 
     * @return The red component, clamped.
     */
    GLclampf getG() const;

    /**
     * Gets the red component.
     * 
     * @return The red component, clamped.
     */
    GLclampf getB() const;

    /**
     * Gets the red component.
     * 
     * @return The red component, clamped.
     */
    GLclampf getA() const;
    
    // Predefined colors:
    
    /// Color black.
    static const Color BLACK;
    
    /// Color red.
    static const Color RED;
    
    /// Color green.
    static const Color GREEN;
    
    /// Color blue.
    static const Color BLUE;
    
    /// Color orange.
    static const Color ORANGE;
    
    /// Color yellow.
    static const Color YELLOW;

};

//==============================================================================

/**
 * Rectangle class, which represents a quad in two-dimensional space. It's built
 * up using four numbers: (x, y) - (w, h).
 */
class Rect {
public:

    /**
     * Creates this rect.
     */
    Rect(const GLfloat& x = 0.0f, const GLfloat& y = 0.0f, const GLfloat& w = 0.0f, const GLfloat& h = 0.0f);
    
    /**
     * KKND.
     */
    ~Rect();
    
    /// First x coordinate, ideally something like bottom-left.
    GLfloat x;
    
    /// First y coordinate, ideally something like bottom-left.
    GLfloat y;
    
    /// Width of the rectangle.
    GLfloat w;
    
    /// Height of the rectangle.
    GLfloat h;
    
    /**
     * This function checks if the current rectangle is intersecting another
     * rectangle, i.e. if it's colliding.
     * 
     * @param other The other rectangle to test with. Returns true if they 
     * intersect - or collide -, and returns false if they do not.
     */
    bool intersects(const Rect& other) const;
};

//==============================================================================

/**
 * Base object for anything (2D) renderable in Ogle.
 */
class Object {
protected:
    /// The x coordinate of this object.
    GLfloat m_x;
    
    /// The y coordinate of this object.
    GLfloat m_y;
    
    /// The z coordinate of this object.
    GLfloat m_z;
    
    /// Width of this object.
    GLfloat m_width;
    
    /// Height of this object.
    GLfloat m_height;
    
    /// Whether this object should react on collisions or not.
    bool m_collisionEligible;
    
    /// The object's boundary box.
    Rect m_boundaryBox;
    
public:
    /**
     * Constructs a brand new Object, with the specified coordinates.
     * 
     * @param x The x coordinate, or 0.0f when not specified.
     * @param y The y coordinate, or 0.0f when not specified.
     * @param z The z coordinate, or 0.0f when not specified.
     */
    Object(const GLfloat& x = 0.0f, const GLfloat& y = 0.0f, const GLfloat& z = 0.0f);
    
    /**
     * Destroys this object.
     */
    virtual ~Object();

    /**
     * Sets the position using a single call.
     * 
     * @param x The x coordinate, or 0.0f when not specified.
     * @param y The y coordinate, or 0.0f when not specified.
     * @param z The z coordinate, or 0.0f when not specified.
     */
    void setPosition(const GLfloat& x = 0.0f, const GLfloat& y = 0.0f, const GLfloat& z = 0.0f);
    
    /**
     * Sets the x position of this object.
     * 
     * @param x the x position.
     */
    void setX(const GLfloat& x);

    /**
     * Sets the y position of this object.
     * 
     * @param y the y position.
     */    
    void setY(const GLfloat& y);
    
    /**
     * Sets the z position of this object.
     * 
     * @param z the z position.
     */
    void setZ(const GLfloat& z);
    
    /**
     * Sets the width. May or may not be applicable, depending on the subclass.
     * 
     * @param w The width.
     */
    void setWidth(const GLfloat& w);
    
    /**
     * Sets the width. May or may not be applicable, depending on the subclass.
     * 
     * @param h The height.
     */
    void setHeight(const GLfloat& h);
    
    /**
     * Sets whether this object is eligible for collision detection.
     * @param eligible True when this object is suitable for collision detection,
     *  or false if not.
     */
    void setCollisionEligible(bool eligible);
    
    const GLfloat& getX() const;
    
    const GLfloat& getY() const;
    
    const GLfloat& getZ() const;
    
    const GLfloat& getWidth() const;
    
    const GLfloat& getHeight() const;
    
    bool isCollisionEligible() const;
    
    /**
     * Gets the boundary of this object as a rectangle. This can be used for
     * simple boundary box collision detection. The boundary of this object
     * is 'calculated' each time this function is called. The object reference
     * remains the same, so only the properties of the returned Rect are changed,
     * not the Rect object itself.
     * 
     * @return The boundary of this single object as a Rect object. 
     */
    virtual const Rect& getBoundary();
    
    /**
     * Pure abstract method to render an object. This must be overridden by a
     * subclass.
     */
    virtual void render() = 0;
};

//==============================================================================

/**
 * Class to draw a simple boxed object, like a cube, or 'rectangular' boxed 
 * object.
 */
class Box : public Object {
private:
    /// Box depth (over the z axis).
    GLfloat m_depth;
public:
    Box();
    ~Box();
    
    virtual void render();
};

//==============================================================================

/**
 * Displays a simple axis for rendering help.
 */
class Axis : public Object {
private:
    /// Distance to draw this axis.
    GLfloat m_max;

public:
    /**
     * Ctor.
     */
    Axis(const GLfloat& max = 100);
    
    /**
     * Dtor.
     */
    ~Axis();
    
    /**
     * Renders this axis.
     */
    void render();
};

//==============================================================================

/**
 * Default reference implementation of a Particle. This class can be subclassed
 * and extended with custom properties. The render() method can be, so custom 
 * particle rendering can be done. It's not needed though, for a particle generator
 * can render a particle solely based on the Particle's properties.
 */
class Particle : public Object {
private:
    static const GLfloat SIZE = 1.0f;
    
    /// Whether this particle is active (should be rendered) or not.
    bool m_active;
    
    /// Lifetime this particle. If <= 0, should not be rendered.
    GLfloat m_life;
    
    /// Velocity on the x-axis. Negative = left, positive = right.
    GLfloat m_xv;
    
    /// Velocity on the y-axis. Negative = down, positive = up.
    GLfloat m_yv;
    
    /// Velocity on the z-axis. Negative = away?, positive = towards?.
    GLfloat m_zv;
    
    /// Color of the particle.
    Color m_color;
    
    /// Particle gravity.
    GLfloat m_gravity;
    
    /// Speed of 'fading', i.e. decrementing of the TTL.
    GLfloat m_fadespeed;
    
public:

    /**
     * Creates a particle object.
     */
    Particle();
    
    /**
     * Destroys this particle.
     */
    virtual ~Particle();

    // Setters

    /**
     * Sets this particle to active (rendered) or not (not rendered). The 'life'
     * is unaffected after using this setter.
     * 
     * @param active true when active or false if otherwise.
     */
    void setActive(bool active);

    /**
     * Sets the life of this particle to a certain value. Ideally, when it 
     * reached <= 0.0f, the particle shouldn't be alive anymore.
     * 
     * @param life The life of this particle.
     */
    void setLife(const GLfloat& life);
    
    /**
     * Sets the velocity of this particle on the x-axis. Negative will go left, 
     * positive will go right, and 0.0f will let the particle remain stationary.
     * 
     * @param xv The velocity of this particle on the x-axis.
     */
    void setXv(const GLfloat& xv);
    
    /**
     * Sets the velocity of this particle on the y-axis. Negative will go down, 
     * positive will go up, and 0.0f will let the particle remain stationary.
     * 
     * @param yv The velocity of this particle on the y-axis.
     */
    void setYv(const GLfloat& yv);
    
    /**
     * Sets the velocity of this particle on the z-axis. Negative will go to the back, 
     * positive will go to the front, and 0.0f will let the particle remain stationary.
     * 
     * @param zv The velocity of this particle on the z-axis.
     */
    void setZv(const GLfloat& zv);
    
    /**
     * Sets the color of this particle.
     * 
     * @param color The color.
     */
    void setColor(const Color& color);
    
    /**
     * Sets the gravity factor of this particle. The gravity has an influence on 
     * the particle's velocity: every iteration, this gravity number is added to
     * the current velocity, mimicking gravity. Negative gravity will allow the
     * particle to fall, while positive gravity will allow the particle to rise.
     * 
     * @param gravity The gravity. 
     */
    void setGravity(const GLfloat& gravity);
    
    /**
     * Sets the fade speed of this particle, i.e. the amount of life decremented.
     * 
     * @param fadeSpeed the speed of fading.
     */
    void setFadeSpeed(const GLfloat& fadeSpeed);
        
    // Getters
        
    /**
     * Queries whether this particle is alive or not.
     * 
     * @return true if active, false if not.
     */
    bool isActive() const;
    
    /**
     * Gets the current life of the particle.
     * 
     * @return The life.
     */
    GLfloat getLife() const;
    
    /**
     * Gets the X velocity for this particle.
     * 
     * @return The x velocity.
     */
    GLfloat getXv() const;

    /**
     * Gets the Y velocity for this particle.
     * 
     * @return The y velocity.
     */    
    GLfloat getYv() const;
    
    /**
     * Gets the Z velocity for this particle.
     * 
     * @return The z velocity.
     */
    GLfloat getZv() const;
    
    /**
     * Gets the current color of the particle.
     * 
     * @return the current color.
     */
    Color getColor() const;
    
    /**
     * Gets the current gravity factor.
     * 
     * @return The gravity factor.
     */
    GLfloat getGravity() const;
    
    /**
     * Gets the current fadespeed of this particle. The time to live can be 
     * subtracted with this number to let a particle 'die'.
     * 
     * @return the fading speed of this particle.
     */
    GLfloat getFadeSpeed() const;
            
    /**
     * Renders this particle. It is not relaly necessary to override this method
     * in any subclasses to render a particle. It can however be good to separate
     * it, but your mileage may vary.
     */
    virtual void render();
};

//==============================================================================

/**
 * This is a default 'reference' implementation of a ParticleGenerator. It can
 * be used as a base class for other types of ParticleGenerators, with different
 * implementation specifics. Just override the render() method (and others), and 
 * draw your particles using OpenGL like you want.
 * 
 * This ParticleGenerator only generates a finite amount of particles (until the
 * maximum specified is reached).
 */
class ParticleGenerator : public Object {
private:

    /// Array with fluffy particles.
    Particle* m_particles;

    /// Maximum amount of particles.
    GLuint m_max;
    
    /// Original particle life. Used to determine a percentage of lifetime of a particle.
    GLfloat m_particleLife;
    
    /// The (randomized) spread of the particles to generate on the x axis. The higher, the bigger the spread.
    GLfloat m_spread_x[2];
    
    /// The (randomized) spread of the particles to generate on the y axis. The higher, the bigger the spread.
    GLfloat m_spread_y[2];
    
    /// The (randomized) spread of the particles to generate on the z axis. The higher, the bigger the spread.
    GLfloat m_spread_z[2];
    
    /// The (randomized) spread of the gravity.
    GLfloat m_spread_gravity[2];
    
    /// The spread of fadespeed, i.e. decreasement of lifetime per particle.
    GLfloat m_spread_fade[2];

public:

    /**
     * Constructor.
     * 
     * @param x The x coordinate origin of this generator.
     * @param y The y coordinate origin of this generator.
     */
    ParticleGenerator(const GLfloat& x = 0.0f, const GLfloat& y = 0.0f);
    
    /**
     * Destroys this particle generator, by deleting the particles.
     */
    virtual ~ParticleGenerator();
       
    /**
     * Initializes the particle generator and its particles. Always call this
     * after you've set properties using the setter functions. This will iterate
     * over the particle array, and call initParticle for each single particle
     * instance.
     */
    virtual void initialize();
    
    /**
     * Initializes a single particle to the defaults for this generator.
     * 
     * @param p The particle reference to initialize.
     */
    virtual void initParticle(Particle& p);
    
    /**
     * Sets the maximum amount of particles this generator should create.
     * 
     * @param max The maximum amount of particles to make.
     */ 
    void setMaxParticles(const GLuint& max);
    
    void setSpreadX(const GLfloat& min, const GLfloat& max);
    
    void setSpreadY(const GLfloat& min, const GLfloat& max);
    
    void setSpreadZ(const GLfloat& min, const GLfloat& max);
    
    void setSpreadGravity(const GLfloat& min, const GLfloat& max);
    
    void setSpreadFade(const GLfloat& min, const GLfloat& max);
    
    void setParticleLife(const GLfloat& particleLife);
    
    const GLfloat& getParticleLife() const;
    
    /**
     * Returns the maximum amount of particles to be generated by this generator.
     * 
     * @return The max particles.
     */
    const GLuint& getMaxParticles() const;
    
    /**
     * Gets the particle array. The pointer cannot be changed, the values in it
     * can be changed however. getMaxParticles() can be used to iterate over the
     * array.
     * 
     * @return The current array of particles.
     */
    Particle* const getParticles() const;

    /**
     * Renders this particle generator and subsequently all its particles. Can
     * be overridden by subclasses to provide their own rendering.
     */
    virtual void render();
};

}


#endif // CORE_HPP
