#include <glut.h>

void myDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 0.0);
	glutSolidTeapot(0.5);
	glColor3f(1.0, 0.0, 0.0);
	glutWireTeapot(0.5);

	glFlush();
}

void main(int argc, char** argv) {
	glutCreateWindow("Example 2");
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glutDisplayFunc(myDisplay);
	glutMainLoop();
}