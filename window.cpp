#include "window.h"

Window::Window() {
	width_ = 800;
	height_ = 800;
}

Window::Window(GLint windowWidth, GLint windowHeight) {
	width_ = windowWidth;
	height_ = windowHeight;
}

int Window::initialize() {
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

	mainWindow_ = glfwCreateWindow(width_, height_, "Test Window", NULL, NULL);
	if (!mainWindow_) {
		std::cout << "GLFW window creation failed!\n";
		glfwTerminate();
		return 1;
	}

	// Get Buffer size information
	int bufferWidth, bufferHeight;
	glfwGetFramebufferSize(mainWindow_, &bufferWidth, &bufferHeight);

	// Set context for GLEW to use
	glfwMakeContextCurrent(mainWindow_);

	// Allow modern extension features
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK) {
		std::cout << "GLEW initialization failed!\n";
		glfwDestroyWindow(mainWindow_);
		glfwTerminate();
		return 1;
	}

	glEnable(GL_DEPTH_TEST);

	// Create Viewport
	glViewport(0, 0, bufferWidth, bufferHeight);
}

Window::~Window() {
	glfwDestroyWindow(mainWindow_);
	glfwTerminate();
}



