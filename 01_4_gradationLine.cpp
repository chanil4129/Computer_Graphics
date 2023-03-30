#include <glut.h>

void myDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_LINES);
	glLineWidth(5.0);
		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(1.0, 0.0, 0.0);
		glColor3f(0.0, 0.0, 0.0);
		glVertex3f(-1.0, 0.0, 0.0);
	glEnd();
	glFlush();
}

void main(int argc, char** argv) {
	glutCreateWindow("Example 4");
	glutDisplayFunc(myDisplay);
	glutMainLoop();
}