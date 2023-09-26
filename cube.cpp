#include <glut.h>
#include <GLU.h>
#include <GL.h>
#include <iostream>

// ȸ�� �� �� ����
GLfloat rotationX = 0.0f;
GLfloat rotationY = 0.0f;
GLfloat zoom = 1.0f;

// ���콺 ��ġ �� �巡�� ���¸� �����ϴ� ����
int mouseX = 0, mouseY = 0;
bool isDragging = false;

void drawMesh()
{
    //���� ��ǥ ������
    GLfloat vertices[] = {
        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, 0.5f, -0.5f,
        -0.5f, 0.5f, -0.5f,
        -0.5f, -0.5f, 0.5f,
        0.5f, -0.5f, 0.5f,
        0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f, 0.5f
    };

    //���� �����ϴ� ���� �ε���
    GLuint indices[] = {
        0, 1, 2, 
        2, 3, 0,
        1, 5, 6, 
        6, 2, 1,
        7, 6, 5, 
        5, 4, 7,
        4, 0, 3, 
        3, 7, 4,
        4, 5, 1, 
        1, 0, 4,
        3, 2, 6, 
        6, 7, 3
    };

    // �޽� ���� �ڵ� (OpenGL�� ���)
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < sizeof(indices) / sizeof(indices[0]); i++)
    {
        // ���� ����
        if (i % 6 == 0)  // �ﰢ������ ���� ����
        {
            float r = ((i / 6) % 2) ? 1.0f : 0.0f;
            float g = ((i / 6) % 3) ? 1.0f : 0.0f;
            float b = ((i / 6) % 5) ? 1.0f : 0.0f;
            glColor3f(r, g, b);
        }

        int index = indices[i];
        glVertex3f(vertices[3 * index], vertices[3 * index + 1], vertices[3 * index + 2]);
    }
    glEnd();
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

    drawMesh();

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

