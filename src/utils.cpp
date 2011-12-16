//      utils.cpp
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

#include "utils.hpp"

namespace ogle {

//==============================================================================
// Helper CLASSES
//==============================================================================

Vertex::Vertex(const GLfloat& xx, const GLfloat& yy, const GLfloat& zz) :
        x(xx), y(yy), z(zz) {
}

Vertex::~Vertex() {
}

void Vertex::normalize() {
    // x^2 + y^2 + z^2
    GLfloat fac = sqrt((x * x) + (y * y) + (z * z));
    x /= fac;
    y /= fac;
    z /= fac;
}

// static:
Vertex Vertex::calcNormal(const Vertex& a, const Vertex& b) {
    Vertex c;
    c.x = (a.y * b.z) - (a.z - b.y);
    c.y = (a.z * b.x) - (a.x - b.z);
    c.z = (a.x * b.y) - (a.y - b.x);
    return c; 
}

//==============================================================================
// Helper FUNCTIONS
//==============================================================================


} // namespace ogle
