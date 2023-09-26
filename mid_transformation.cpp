#include <glut.h>
#include <GLU.h>
#include <GL.h>

void MYDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);
    glViewport(0, 0, 300, 300);
    glMatrixMode(GL_MODELVIEW);
    //빨간 사각형
    glColor3f(1.0, 0.0, 0.0);
    glLoadIdentity();
    glutSolidCube(0.3);
    //녹색 사각형
    glColor3f(0.0, 1.0, 0.0);
    glLoadIdentity();
    glRotatef(45.0, 0.0, 0.0, 1.0);
    glTranslatef(0.6, 0.0, 0.0);
    glutSolidCube(0.3);
    //파란 사각형
    glColor3f(0.0, 0.0, 1.0);
    glLoadIdentity();
    glTranslatef(0.6, 0.0, 0.0);
    glRotatef(45.0, 0.0, 0.0, 1.0);
    glutSolidCube(0.3);
    glFlush();
}

void main(int argc, char** argv) {
    glutInitDisplayMode(GLUT_RGBA);
    glutInitWindowSize(300, 300);
    glutCreateWindow("Draw");
    glClearColor (1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    glutDisplayFunc(MYDisplay);
    
    glutMainLoop();
}