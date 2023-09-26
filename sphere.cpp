#include <glut.h>
#include <GLU.h>
#include <GL.h>
#include <iostream>
#include <cmath>
#include <GLAUX.h>


// 회전 및 줌 변수
GLfloat rotationX = 0.0f;
GLfloat rotationY = 0.0f;
GLfloat zoom = 1.0f;

// 마우스 위치 및 드래그 상태를 저장하는 변수
int mouseX = 0, mouseY = 0;
bool isDragging = false;

AUX_RGBImageRec* LoadBMPFile(char* Filename);
GLuint texture[10];                          // 텍스처 저장공간


// texure load 1
AUX_RGBImageRec* LoadBMPFile(char* Filename)
{
    FILE* File = NULL;                            // 파일 핸들
    if (!Filename)                                // 파일이름이 전달되었는지 확인
    {
        return NULL;                            // 그렇지 않다면 NULL을 반환
    }

    File = fopen(Filename, "r");                        // 파일이 존재하는지 확인
    if (File)                                // 파일이 존재하는가?
    {
        fclose(File);                            // 핸들을 닫음
        return auxDIBImageLoad(Filename);                // 비트맵을 읽어들이고 포인터를 반환
    }

    return NULL;
}


void drawSphere(float radius, int slices, int stacks) {
    glColor3f(0.0f, 0.0f, 1.0f); // 파란색으로 설정
    glutSolidSphere(radius, slices, stacks);
}

// texure load 2
int LoadGLTextures(char* filename, int num)
{
    int Status = FALSE;                            // 상태 표시기
    AUX_RGBImageRec* TextureImage[1];                    // 텍스처용 저장공간을 만듬
    memset(TextureImage, 0, sizeof(void*) * 1);                // 포인터를 NULL로 설정

    //printf("%s\n",filename);
    if (TextureImage[0] = LoadBMPFile(filename))
    {
        Status = TRUE;                            // Status를 TRUE로 설정
        glGenTextures(1, &texture[num]);                    // 텍스처를 만듬

        // 비트맵으로부터 가져온 데이터를 사용한 일반적인 텍스처 생성
        glBindTexture(GL_TEXTURE_2D, texture[num]);
        // 텍스처를 만든다
        glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);    // 선형 필터링
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);    // 선형 필터링
    }

    if (TextureImage[0])                            // 텍스처가 존재하는지 확인
    {
        if (TextureImage[0]->data)                    // 텍스처 이미지가 존재하는지 확인
        {
            free(TextureImage[0]->data);                // 텍스처 이미지 메모리를 해제
        }

        free(TextureImage[0]);                        // 이미지 구조체를 해제
    }

    return Status;                                // Status를 반환
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
    drawSphere(1.0f, 36, 18);  // 반지름이 1.0, 가로 조각 수가 36, 세로 조각 수가 18인 구 그리기

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

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMotionFunc(mouseMotion);  // 추가됨
    glutKeyboardFunc(keyboard);

    glutMainLoop();

    return 0;
}
