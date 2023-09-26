#include <glut.h>
#include <GLU.h>
#include <GL.h>
#include <iostream>
#include <FreeImage.h>

// 회전 및 줌 변수
GLfloat rotationX = 0.0f;
GLfloat rotationY = 0.0f;
GLfloat zoom = 1.0f;

// 마우스 위치 및 드래그 상태를 저장하는 변수
int mouseX = 0, mouseY = 0;
bool isDragging = false;

GLuint texture;




void loadTexture(const char* filename) {
    FREE_IMAGE_FORMAT format = FreeImage_GetFileType(filename, 0);
    FIBITMAP* image = FreeImage_Load(format, filename);
    FIBITMAP* image32bits = FreeImage_ConvertTo32Bits(image);

    //FreeImage로 이미지를 불러오고 RGB 포맷으로 변환하는 과정
    FIBITMAP* temp = image;
    image = FreeImage_ConvertTo24Bits(temp);
    FreeImage_Unload(temp);

    // Generate an OpenGL texture ID for this texture
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    //
    RGBQUAD color;
    for (int i = 0; i < FreeImage_GetWidth(image); i++) {
        for (int j = 0; j < FreeImage_GetHeight(image); j++) {
            FreeImage_GetPixelColor(image, i, j, &color);
            BYTE temp = color.rgbRed;
            color.rgbRed = color.rgbBlue;
            color.rgbBlue = temp;
            FreeImage_SetPixelColor(image, i, j, &color);
        }
    }

    // Upload the texture -
    // The first zero is the mipmap level (level 0, since there's only 1)
    // All the other zeros are border and offset stuff. The final is format it was loaded in.
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, FreeImage_GetWidth(image), FreeImage_GetHeight(image), 0, GL_RGB, GL_UNSIGNED_BYTE, FreeImage_GetBits(image));


    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Unload the 32-bit colour bitmap
    FreeImage_Unload(image32bits);

    // Unload the original bitmap
    FreeImage_Unload(image);
}



void display()
{
    //glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // 배경 흰색으로 설정
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);  // 배경 회색으로 설정
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // 카메라 설정 등 추가 작업 수행 가능

    // 3D 모델링 메쉬 그리기
    glTranslatef(0.0f, 0.0f, -5.0f);
    glRotatef(rotationX, 1.0f, 0.0f, 0.0f);
    glRotatef(rotationY, 0.0f, 1.0f, 0.0f);
    glScalef(zoom, zoom, zoom);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);

    // Draw a cube with texture
    glBegin(GL_QUADS);
    // front face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
    glEnd();

    glDisable(GL_TEXTURE_2D);

    //glColor3f(1.0f, 0.89453125f, 0.796875f); // 살색으로 설정
    //glutSolidCube(1.0);

    // Draw the cone on top of the cube
    glPushMatrix(); // Save the transformations performed so far
    glTranslatef(0.0f, 0.5f, 0.0f); // Move up to the top of the cube
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f); // Rotate the cone -90 degrees around the x-axis
    glColor3f(0.0f, 0.0f, 1.0f); // Change the color to blue
    glutSolidCone(0.5, 1.0, 20, 20); // Draw a cone with base radius 0.5 and height 1.0
    glPopMatrix(); // Reset the transformations to before the cone was drawn

    glFlush();
    glutSwapBuffers();
}

void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON)
    {
        if (state == GLUT_DOWN)
        {
            // 마우스 드래그 시작
            isDragging = true;
            mouseX = x;
            mouseY = y;
        }
        else
        {
            // 마우스 드래그 종료
            isDragging = false;
        }
    }
}

void mouseMotion(int x, int y)
{
    if (isDragging)
    {
        // 마우스 드래그 중일 때 회전
        rotationX += (GLfloat)(y - mouseY) * 0.2f;
        rotationY += (GLfloat)(x - mouseX) * 0.2f;
        mouseX = x;
        mouseY = y;
        glutPostRedisplay();
    }
}

void keyboard(unsigned char key, int x, int y)
{
    // 키보드 입력 이벤트 처리
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
    glEnable(GL_TEXTURE_2D);

    loadTexture("red_circle.bmp"); // Load the texture

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMotionFunc(mouseMotion);
    glutKeyboardFunc(keyboard);

    glutMainLoop();

    return 0;
}

