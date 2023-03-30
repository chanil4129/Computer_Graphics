#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>

int main(void)
{
	//GLFW 초기화
	if (!glfwInit())
		exit(EXIT_FAILURE);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // OpenGL 버전(x.y 중 x)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5); // 4.6에 맞춰 실행(x.y 중 y)
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 더 이상 쓰이지 않는 하위 호환 기능들 에러 처리
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // 상위 호환성 지원

	//Window 생성
	GLFWwindow* window = glfwCreateWindow(1080, 720, "title", NULL, NULL);
	/*전체화면 코드
	GLFWmonitor* primary = glfwGetPrimaryMonitor();
	GLFWwindow* window = glfwCreateWindow(1080, 720, "title", primary, NULL);
	*/
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);

	int framebuf_width, framebuf_height;
	glfwGetFramebufferSize(window, &framebuf_width, &framebuf_height);
	glViewport(0, 0, framebuf_width, framebuf_height);

	if (glewInit() != GLEW_OK)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}