#include <GL/glew.h>
#include <GLFW/glfw3.h>

int main(void)
{

	/* Initialize the library */
	glfwInit();

	glewInit();

	/* Create a windowed mode window and its OpenGL context */
	GLFWwindow* window = glfwCreateWindow(1920, 1080, "Hello World", NULL, NULL);

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}