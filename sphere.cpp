#include <glut.h>
#include <GLU.h>
#include <GL.h>
#include <iostream>
#include <cmath>
#include <GLAUX.h>


// ȸ�� �� �� ����
GLfloat rotationX = 0.0f;
GLfloat rotationY = 0.0f;
GLfloat zoom = 1.0f;

// ���콺 ��ġ �� �巡�� ���¸� �����ϴ� ����
int mouseX = 0, mouseY = 0;
bool isDragging = false;

AUX_RGBImageRec* LoadBMPFile(char* Filename);
GLuint texture[10];                          // �ؽ�ó �������


// texure load 1
AUX_RGBImageRec* LoadBMPFile(char* Filename)
{
    FILE* File = NULL;                            // ���� �ڵ�
    if (!Filename)                                // �����̸��� ���޵Ǿ����� Ȯ��
    {
        return NULL;                            // �׷��� �ʴٸ� NULL�� ��ȯ
    }

    File = fopen(Filename, "r");                        // ������ �����ϴ��� Ȯ��
    if (File)                                // ������ �����ϴ°�?
    {
        fclose(File);                            // �ڵ��� ����
        return auxDIBImageLoad(Filename);                // ��Ʈ���� �о���̰� �����͸� ��ȯ
    }

    return NULL;
}


void drawSphere(float radius, int slices, int stacks) {
    glColor3f(0.0f, 0.0f, 1.0f); // �Ķ������� ����
    glutSolidSphere(radius, slices, stacks);
}

// texure load 2
int LoadGLTextures(char* filename, int num)
{
    int Status = FALSE;                            // ���� ǥ�ñ�
    AUX_RGBImageRec* TextureImage[1];                    // �ؽ�ó�� ��������� ����
    memset(TextureImage, 0, sizeof(void*) * 1);                // �����͸� NULL�� ����

    //printf("%s\n",filename);
    if (TextureImage[0] = LoadBMPFile(filename))
    {
        Status = TRUE;                            // Status�� TRUE�� ����
        glGenTextures(1, &texture[num]);                    // �ؽ�ó�� ����

        // ��Ʈ�����κ��� ������ �����͸� ����� �Ϲ����� �ؽ�ó ����
        glBindTexture(GL_TEXTURE_2D, texture[num]);
        // �ؽ�ó�� �����
        glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);    // ���� ���͸�
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);    // ���� ���͸�
    }

    if (TextureImage[0])                            // �ؽ�ó�� �����ϴ��� Ȯ��
    {
        if (TextureImage[0]->data)                    // �ؽ�ó �̹����� �����ϴ��� Ȯ��
        {
            free(TextureImage[0]->data);                // �ؽ�ó �̹��� �޸𸮸� ����
        }

        free(TextureImage[0]);                        // �̹��� ����ü�� ����
    }

    return Status;                                // Status�� ��ȯ
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
    drawSphere(1.0f, 36, 18);  // �������� 1.0, ���� ���� ���� 36, ���� ���� ���� 18�� �� �׸���

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
