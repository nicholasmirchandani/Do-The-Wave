#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <fstream>

#define MAX_WAVES 100

enum VAO_IDs { Triangles, NumVAOs };
enum Buffer_IDs { ArrayBuffer, ElementBuffer, NumBuffers };
enum Attrib_IDs { vPosition = 0 };

GLuint CreateShader(GLenum shadertype, std::string filename);

int main() {
	//GLFW/GLEW Initialization
	glfwInit();
	GLFWwindow* window = glfwCreateWindow(640, 480, "Do The Wave", NULL, NULL);
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	glewInit();

	//Initialize Vertex data
	const int numVertices = 4;
	GLfloat vertices[numVertices][2] = {
		{-1, -1}, // 0
		{ 1, -1}, // 1
		{-1,  1}, // 2
		{ 1,  1}  // 3
	};


	GLuint VAOs[NumVAOs];
	GLuint Buffers[NumBuffers];
	glCreateBuffers(NumBuffers, Buffers);
	glNamedBufferStorage(Buffers[ArrayBuffer], sizeof(vertices), vertices, 0);

	glGenVertexArrays(NumVAOs, VAOs);
	glBindVertexArray(VAOs[Triangles]);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
	glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, 0); //BUFFER_OFFSET(0) isn't defined?
	glEnableVertexAttribArray(vPosition);

	//Initialize Element data
	const int numElements = 6;
	GLuint elements[6] = {
		0, 1, 2, 1, 3, 2
	};

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Buffers[ElementBuffer]);
	glNamedBufferStorage(Buffers[ElementBuffer], sizeof(elements), elements, 0);


	//Shader setup
	GLuint program = glCreateProgram();

	GLuint vertexShader = CreateShader(GL_VERTEX_SHADER, "passthrough_vert.shader");
	GLuint fragmentShader = CreateShader(GL_FRAGMENT_SHADER, "wave_frag.shader");
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);
	glValidateProgram(program);
	glUseProgram(program);

	//Uniform preparation and render loop
	int sinSpeedLocation = glGetUniformLocation(program, "sinSpeed");
	int blueLocLocation = glGetUniformLocation(program, "blueLoc");
	int numWavesLocation = glGetUniformLocation(program, "numWaves");
	int screenXLocation = glGetUniformLocation(program, "screenX");
	int screenYLocation = glGetUniformLocation(program, "screenY");

	int screenX, screenY;
	float sinSpeed = 1.0;
	float step = 0.01f;
	float blue = 0.0f;
	bool increaseStep = true;
	float numWaves = 1.0f;
	bool increaseNumWaves = true;

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window)) {
		static const float black[] = { 0.0f, 0.0f, 0.0f, 0.0f };
		glClearBufferfv(GL_COLOR, 0, black);
		glfwGetWindowSize(window, &screenX, &screenY);

		glUniform1f(sinSpeedLocation, sinSpeed);
		glUniform1f(blueLocLocation, blue);
		glUniform1f(numWavesLocation, numWaves);
		glUniform1i(screenXLocation, screenX);
		glUniform1i(screenYLocation, screenY);
		glViewport(0, 0, screenX, screenY);

		glDrawElements(GL_TRIANGLES, numElements, GL_UNSIGNED_INT, nullptr);

		if (blue < 0.0f) {
			increaseStep = true;
		} else if (blue > 1.0f) {
			increaseStep = false;
		}

		if (numWaves > MAX_WAVES) {
			increaseNumWaves = false;
		} else if (numWaves <= 1) {
			increaseNumWaves = true;
		}

		if (increaseNumWaves) {
			numWaves += .01 * numWaves;
		} else {
			numWaves -= .01 * numWaves;
		}

		if (increaseStep) {
			step = (0.01 - blue / 110);
		} else {
			step = -0.01 + ((1 - blue) / 110);
		}
		blue += step;
		sinSpeed -= step;

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}

GLuint CreateShader(GLenum shaderType, std::string filename) {
	GLuint shader = glCreateShader(shaderType);
	std::ifstream is(filename);
	std::string source;
	std::string line;
	while (!is.eof()) {
		std::getline(is, line);
		source += line + '\n';
	}
	const GLchar* sourceChar(source.c_str());
	glShaderSource(shader, 1, &sourceChar, 0);
	glCompileShader(shader);
	return shader;
}