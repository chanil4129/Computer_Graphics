#include <glut.h>
#include <GLU.h>
#include <GL.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

// ȸ�� �� �� ����
GLfloat rotationX = 0.0f;
GLfloat rotationY = 0.0f;
GLfloat zoom = 1.0f;

// ���콺 ��ġ �� �巡�� ���¸� �����ϴ� ����
int mouseX = 0, mouseY = 0;
bool isDragging = false;

std::vector<GLfloat> vertices;
std::vector<GLuint> indices;

void loadObjFile(const std::string& filename)
{
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string prefix;
        iss >> prefix;

        if (prefix == "v")
        {
            GLfloat x, y, z;
            iss >> x >> y >> z;
            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(z);
        }
        else if (prefix == "f")
        {
            GLuint i1, i2, i3;
            iss >> i1 >> i2 >> i3;
            // Obj file indices are 1-based, so subtract 1
            indices.push_back(i1 - 1);
            indices.push_back(i2 - 1);
            indices.push_back(i3 - 1);
        }
    }
}

void drawMesh()
{
    glBegin(GL_TRIANGLES);
    for (GLuint index : indices)
    {
        glVertex3f(vertices[3 * index], vertices[3 * index + 1], vertices[3 * index + 2]);
    }
    glEnd();
}

void display()
{
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
    loadObjFile("mesh.obj");

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

