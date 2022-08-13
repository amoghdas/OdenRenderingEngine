#include <iostream>
#include <GL/glew.h>
#include <glfw/glfw3.h>
#include <string.h>

// Window dimensions
const GLint WIDTH = 800, HEIGHT = 600;

GLuint VAO, VBO, shader;

// Vertex Shader
static const char *vShader = "									\n\
#version 330													\n\
																\n\
layout (location = 0) in vec3 pos;								\n\
																\n\
void main() {													\n\
	gl_Position = vec4(0.4 * pos.x, 0.4 * pos.y, pos.z, 1.0);	\n\
}";

// Fragment Shader
static const char *fShader = "									\n\
#version 330													\n\
																\n\
out vec4 colour;												\n\
																\n\
void main() {													\n\
	colour = vec4(1.0, 0.0, 0.0, 1.0);							\n\
}";

void createTriangle() {
	GLfloat vertices[] = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f
	};

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

void addShader(GLuint theProgram, const char *shaderCode, GLenum shaderType) {
	GLuint theShader = glCreateShader(shaderType);

	const GLchar* theCode[1];
	theCode[0] = shaderCode;
	
	GLint codeLength[1];
	codeLength[0] = strlen(shaderCode);
	
	glShaderSource(theShader, 1, theCode, codeLength);
	glCompileShader(theShader);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
	if (!result) {
		glGetShaderInfoLog(theShader, sizeof(eLog), NULL, eLog);
		std::cout << "Error copiling the " << shaderType << " shader: '" << eLog << "'\n";
		return;
	}

	glAttachShader(theProgram, theShader);
}

void compileShaders() {
	shader = glCreateProgram();
	
	if (!shader) {
		std::cout << "Error creating shader program!\n";
		return;
	}

	addShader(shader, vShader, GL_VERTEX_SHADER);
	addShader(shader, fShader, GL_FRAGMENT_SHADER);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glLinkProgram(shader);
	glGetProgramiv(shader, GL_LINK_STATUS, &result);
	if (!result) {
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		std::cout << "Error linking program: '" << eLog << "'\n";
		return;
	}

	glValidateProgram(shader);
	glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);
	if (!result) {
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		std::cout << "Error validating program: '" << eLog << "'\n";
		return;
	}
}

int main() {
	// Initialize GLFW
	if (!glfwInit()) {
		std::cout << "GLFW Initialization failed!\n";
		glfwTerminate();
		return 1;
	}

	// Setup GLFW window properties
	// Setting OpenGL version to be 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Core profile = No backwards compatibility
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// Allow forward compatibility
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow* mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "Test Window", NULL, NULL);
	if (!mainWindow) {
		std::cout << "GLFW window creation failed!\n";
		glfwTerminate();
		return 1;
	}

	// Get Buffer size information
	int bufferWidth, bufferHeight;
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	// Set context for GLEW to use
	glfwMakeContextCurrent(mainWindow);

	// Allow modern extension features
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK) {
		std::cout << "GLEW initialization failed!\n";
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	// Create Viewport
	glViewport(0, 0, bufferWidth, bufferHeight);

	createTriangle();
	compileShaders();

	// Loop until window closed
	while (!glfwWindowShouldClose(mainWindow)) {
		// Get + Handle user input events
		glfwPollEvents();

		// Clear window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shader);

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		glUseProgram(0);

		// Normally there are 2 buffers - one that the user can see and one that you're drawing to.
		//   Once you're done drawing to a buffer and you want the user to see it, you swap buffers
		//   so that the one you just drew to is now the one the user sees and the one the user was 
		//   seeing is the one you're drawing to.
		glfwSwapBuffers(mainWindow);
	}

	return 0;
}