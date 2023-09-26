#include <fstream>
#include <glut.h>
#include <GLU.h>
#include <GL.h>

void writeObjFile(const std::string& filename, const GLfloat* vertices, int vertexCount, const GLuint* indices, int indexCount)
{
    std::ofstream file(filename);

    // Write vertices
    for (int i = 0; i < vertexCount; i += 3)
    {
        file << "v " << vertices[i] << " " << vertices[i + 1] << " " << vertices[i + 2] << "\n";
    }

    // Write faces
    for (int i = 0; i < indexCount; i += 3)
    {
        // Obj file indices are 1-based
        file << "f " << (indices[i] + 1) << " " << (indices[i + 1] + 1) << " " << (indices[i + 2] + 1) << "\n";
    }

    file.close();
}

int main()
{
    GLfloat vertices[] = {
        // 추가
    };

    GLuint indices[] = {
        // 추가
    };

    writeObjFile("mesh.obj", vertices, sizeof(vertices) / sizeof(GLfloat), indices, sizeof(indices) / sizeof(GLuint));

    return 0;
}
