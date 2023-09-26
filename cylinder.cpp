#include <glut.h>
#include <GLU.h>
#include <GL.h>
#include <iostream>
#include <cmath>

// ȸ�� �� �� ����
GLfloat rotationX = 0.0f;
GLfloat rotationY = 0.0f;
GLfloat zoom = 1.0f;

// ���콺 ��ġ �� �巡�� ���¸� �����ϴ� ����
int mouseX = 0, mouseY = 0;
bool isDragging = false;

//���� �׸��� �Լ�
void drawCircle(float radius, int numSides) {
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.0f, 0.0f);
    for (int i = 0; i < numSides; i++) {
        float angle = (2.0f * 3.1415926f * float(i)) / float(numSides); // calculate angle
        float x = radius * cosf(angle);
        float y = radius * sinf(angle);
        glVertex3f(x, y, 0.0f);
    }
    glEnd();
}

// ������� �׸��� �Լ�
void drawCylinder(float baseRadius, float topRadius, float height, int numSides) {
    // ������� �ٴ� �׸���
    glPushMatrix();
    drawCircle(baseRadius, numSides);
    glPopMatrix();

    // ������� �ٴڰ� ����⸦ �����ϴ� �� �׸���
    glBegin(GL_QUAD_STRIP);
    glColor3f(0.0f, 1.0f, 0.0f);
    for (int i = 0; i <= numSides; i++) {
        float angle = (2.0f * 3.1415926f * float(i)) / float(numSides); // calculate angle
        float x = cosf(angle);
        float y = sinf(angle);
        glVertex3f(baseRadius * x, baseRadius * y, 0.0f);
        glVertex3f(topRadius * x, topRadius * y, height);
    }
    glEnd();

    // ������� ����� �׸���
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, height);
    drawCircle(topRadius, numSides);
    glPopMatrix();
}

void display()
{
    //glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // ��� ������� ����
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);  // ��� ȸ������ ����
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // ī�޶� ���� �� �߰� �۾� ���� ����

    // 3D �𵨸� �޽� �׸���
    glTranslatef(0.0f, 0.0f, -5.0f);
    glRotatef(rotationX, 1.0f, 0.0f, 0.0f);
    glRotatef(rotationY, 0.0f, 1.0f, 0.0f);
    glScalef(zoom, zoom, zoom);

    drawCylinder(0.5f, 0.5f, 1.0f, 30);

    glFlush();
    glutSwapBuffers();
}

void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON)
    {
        if (state == GLUT_DOWN)
        {
            // ���콺 �巡�� ����
            isDragging = true;
            mouseX = x;
            mouseY = y;
        }
        else
        {
            // ���콺 �巡�� ����
            isDragging = false;
        }
    }
}

void mouseMotion(int x, int y)
{
    if (isDragging)
    {
        // ���콺 �巡�� ���� �� ȸ��
        rotationX += (GLfloat)(y - mouseY) * 0.2f;
        rotationY += (GLfloat)(x - mouseX) * 0.2f;
        mouseX = x;
        mouseY = y;
        glutPostRedisplay();
    }
}

void keyboard(unsigned char key, int x, int y)
{
    // Ű���� �Է� �̺�Ʈ ó��
    if (key == 'a')
    {
        zoom += 0.1f;
        glutPostRedisplay();
    }
    else if (key == 'z')
    {
        zoom -= 0.1f;
        if (zoom < 0.1f)
            zoom = 0.1f;
        glutPostRedisplay();
    }
}

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (GLfloat)w / (GLfloat)h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Mesh");

    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMotionFunc(mouseMotion);  // �߰���
    glutKeyboardFunc(keyboard);

    glutMainLoop();

    return 0;
}
