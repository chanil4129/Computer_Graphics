#include <glut.h>

void myDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);
    glShadeModel(GL_SMOOTH);
    glColor3f(1.0, 0.0, 0.0); // »¡°£»ö ¼±ºÐ

    glBegin(GL_TRIANGLE_STRIP);
    glVertex3f(0.0, 0.5, 0.0);
    glVertex3f(-0.5, -0.5, 0.0);
    glVertex3f(0.5, -0.5, 0.0);

    glVertex3f(0.5, 0.5, 0.0);
    glVertex3f(-0.5, 0.5, 0.0);
    glVertex3f(0.0, -0.5, 0.0);
    glEnd();



    glFlush();
}

void main(int argc, char** argv) {
	glutCreateWindow("triangles");
	glutDisplayFunc(myDisplay);
	glutMainLoop();
}