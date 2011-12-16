//      ogle.cpp
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

#include "ogle.hpp"
#include "core.hpp"
#include "collision.hpp"

#include <iostream>


GLfloat ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
GLfloat diffuseLight[] = { 0.8f, 0.8f, 0.8, 1.0f };
GLfloat specularLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat position[] = { -1.5f, 1.0f, -4.0f, 1.0f };


void glInit() {
    // Set color and depth clear value
    glClearColor(0.f, 0.f, 0.0f, 0.f);
    glClearDepth(1.0f);
    // Enable Z-buffer read and write
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glDepthMask(GL_TRUE);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);   
   
    glEnable(GL_LIGHTING);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glEnable(GL_LIGHT0);
   
    glViewport(0, 0, 800, 600);
   
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, static_cast<GLfloat>(ogle::SCREEN_WIDTH) / static_cast<GLfloat>(ogle::SCREEN_HEIGHT), 1.0f, 500.0f);   
}

int main(int argc, char* argv[]) {
    sf::WindowSettings settings;
    settings.DepthBits         = 24; // Request a 24 bits depth buffer
    settings.StencilBits       = 8;  // Request a 8 bits stencil buffer
    settings.AntialiasingLevel = 2;  // Request 2 levels of antialiasing
    
    // Create the main window
    sf::Window App(sf::VideoMode(ogle::SCREEN_WIDTH, ogle::SCREEN_HEIGHT, 32), "ArkanOGLE", sf::Style::Close, settings);

    // Create a clock for measuring time elapsed
    sf::Clock Clock;

    glInit();

    GLfloat xrot = 0.0f;
    GLfloat yrot = 0.0f;
    
    ogle::Axis axis(10.0f);
    ogle::Box box;
    box.setWidth(1.0f);
    
    ogle::Box box2;
    box2.setWidth(1.0f);
    box2.setPosition(1.0f, 1.0f, -1.0f);
    
    ogle::Box box3;
    box3.setPosition(2.0f, 1.0f, -1.0f);

    // Start game loop
    while (App.IsOpened()) {
        // Process events
        sf::Event Event;
        while (App.GetEvent(Event)) {
            // Close window : exit
            if (Event.Type == sf::Event::Closed) {
                App.Close();
            }

            // Escape key : exit
            if (Event.Type == sf::Event::KeyPressed) {
                switch (Event.Key.Code) {
                    case sf::Key::Escape:
                        App.Close();
                        break;
                    case sf::Key::Left:
                        xrot += 1.0f;
                        break;
                    case sf::Key::Right:
                        xrot -= 1.0f;
                        break;
                    case sf::Key::Up:
                        yrot -= 1.0f;
                        break;
                    case sf::Key::Down:
                        yrot += 1.0f;
                        break;
                    case sf::Key::A:
                        break;
                    case sf::Key::S:
                        break;
                    case sf::Key::K:
                        break;
                    case sf::Key::L:
                        break;
                    case sf::Key::Tab:
                        break;
                    default:
                        break;
                }
            }

            // Resize event : adjust viewport
            if (Event.Type == sf::Event::Resized) {
                std::cout << "Resizing viewport" << std::endl;
                glViewport(0, 0, Event.Size.Width, Event.Size.Height);
            }
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
     
        // Reset current matrix (model view)
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        
        glTranslatef(-4, -3.5, -10.0f);
        glRotatef(xrot, 0.0f, 1.0f, 0.0f);
        glRotatef(yrot, 1.0f, 0.0f, 0.0f);
        axis.render();
        box.render();
        box2.render();
        box3.render();
        
        // finally, display rendered frame on screen
        App.Display();
                
        sf::Sleep(0.01f);
    }

    return EXIT_SUCCESS;
}
