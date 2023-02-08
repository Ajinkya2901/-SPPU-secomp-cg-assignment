#define GLUT_DISABLE_ATEXIT_HACK
#include <iostream>
#include <GL/glut.h>
#include <GL/gl.h>
#include <windows.h>
#include <cmath>
using namespace std;

float y_inc = 0.0f ;
float color_inc = 0.0f ;
bool flag_position = 0 ; // UP
bool flag_color = 0 ;

/*
Step 2A
Create the `init` function that defines an orthographic projection for 2D graphics
OpenGL works with 3D coordinates, we only need a 2D plane, so we define an ortho projection
GO TO Step 2B
*/
void init() {
    glClearColor( 0.0 , 0.0 , 0.0 , 1.0 ) ;   // Clears the color buffers and sets display color to black
                                              // The first three zeros ( 0 , 0 , 0 ) indicate values for 
                                              // r, g and b and the last 1 indicates alpha ( transparency )
                                              // channel
    glMatrixMode( GL_PROJECTION ) ;           // Select the matrix on which we'll perform further operations
                                              // We'll be working on the projection ( projection space )
                                              // and not in the model space
    gluOrtho2D( 0.0 , 500.0 , 0.0 , 500.0 ) ; // Creates a projection matrix,
                                              // which maps 0 to the left border of the viewport, 
                                              // 500 to the right, 
                                              // 500 to the bottom and 0 to the top.
                                              // The values for left, right, bottom, top, near and far define a box.
                                              // All the geometry which is inside the volume of the box is "visible" on 
                                              // the viewport. ( from StackOverflow )
}

void draw_circle(float x, float y, float radius) {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glTranslatef(x, y, 0.0f);
    int circle_points = 100;
    float angle = 2.0f * 3.1416f / circle_points;
    glBegin(GL_POLYGON);
    double angle1 = 0.0 ;
    glVertex2d(radius * cos(0.0) , radius * sin(0.0));
    for ( int i=0; i<circle_points; i++) {
        glVertex2d(
            radius * cos(angle1),
            radius *sin(angle1));
        angle1 += angle;
    }
    glEnd();
    glPopMatrix();
}

/*
Step 2B

*/
void display() {
    glClear( GL_COLOR_BUFFER_BIT ) ;  // 

    glColor3f( 
        1.0f - (color_inc/200) ,      // 
        0.64f + (color_inc/500) ,     // 
        0.0f + (color_inc/102) ) ;    // 
    glBegin( GL_QUADS ) ;
    glVertex2i( 0 , 0 ) ;
    glVertex2i( 0 , 500 ) ;
    glVertex2i( 500 , 500 ) ;
    glVertex2i( 500 , 0 ) ;
    glEnd() ;


    glColor3f( 1.0 , 1.0 , 0.0 ) ;
    draw_circle( 250.0f  , 0.0f + y_inc , 60.0f ) ;


    glFlush() ;
}

void idle() {
    glutPostRedisplay() ;

    if( flag_position == 0 ) {
        y_inc += 0.020f ;
    }
    else {
        y_inc -= 0.020f ;
    }

    if( y_inc >= 250.0f || y_inc <= 0.0f ) {
        flag_position = !flag_position ;
    }

    if( flag_color == 0 ) {
        color_inc += 0.008 ;
    }
    else {
        color_inc -= 0.008 ;
    }

    if( color_inc >= 100.0f || color_inc <= 0.0f ) {
        flag_color = !flag_color ;
    }

}

/*
Step 1
Create the main function that initializes a window for OpenGL and
set the display function and idle function ( required only for animation )

GO TO Step 2A
*/
int main( int argc, char **argv ) {
    glutInit( &argc , argv ) ;
    glutInitWindowSize( 500 , 500 );           // Initialize Window size and its position
    glutInitWindowPosition( 0 , 0 ) ;          // Set window position
    glutCreateWindow( "Sunrise and Sunset" );  // Add Window Title
    glutDisplayFunc( display ) ;               // Set a display function
    glutIdleFunc( idle ) ;                     // Set an idle function
    init() ;                                   // Initializes Orthographic projection for 2D graphics
    glutMainLoop() ;                           // Starts the OpenGL program
    return 0;
}
