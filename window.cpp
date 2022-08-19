#include "window.h"

Window::Window() {
	width_ = 800;
	height_ = 800;
	xChange_ = 0.0f;
	yChange_ = 0.0f;

	for (size_t i = 0; i < 1024; i++) {
		keys_[i] = 0;
	}
}

Window::Window(GLint windowWidth, GLint windowHeight) {
	width_ = windowWidth;
	height_ = windowHeight;
	xChange_ = 0.0f;
	yChange_ = 0.0f;

	for (size_t i = 0; i < 1024; i++) {
		keys_[i] = 0;
	}
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

	// Create the window
	mainWindow_ = glfwCreateWindow(width_, height_, "Test Window", NULL, NULL);
	if (!mainWindow_) {
		std::cout << "GLFW window creation failed!\n";
		glfwTerminate();
		return 1;
	}

	// Get Buffer size information
	glfwGetFramebufferSize(mainWindow_, &bufferWidth_, &bufferHeight_);

	// Set context for GLEW to use
	glfwMakeContextCurrent(mainWindow_);

	//Handle Key + Mouse input
	createCallbacks();
	glfwSetInputMode(mainWindow_, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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
	glViewport(0, 0, bufferWidth_, bufferHeight_);

	glfwSetWindowUserPointer(mainWindow_, this);
}

void Window::createCallbacks() {
	glfwSetKeyCallback(mainWindow_, handleKeys);
	glfwSetCursorPosCallback(mainWindow_, handleMouse);
}

GLfloat Window::getXChange() {
	GLfloat theChange = xChange_;
	xChange_ = 0.0f;
	return theChange;
}

GLfloat Window::getYChange() {
	GLfloat theChange = yChange_;
	yChange_ = 0.0f;
	return theChange;
}

void Window::handleKeys(GLFWwindow* window, int key, int code, int action, int mode) {
	Window *theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	
	if (key >= 0 && key < 1024) {
		if (action == GLFW_PRESS) {
			theWindow->keys_[key] = true;
			std::cout << "Pressed: " << key << '\n';
		}
		else if (action == GLFW_RELEASE) {
			theWindow->keys_[key] = false;
			std::cout << "Released: " << key << '\n';
		}
	}
}

void Window::handleMouse(GLFWwindow* window, double xPos, double yPos) {
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
	
	if (theWindow->mouseFirstMoved_) {
		theWindow->lastX_ = xPos;
		theWindow->lastY_ = yPos;
		theWindow->mouseFirstMoved_ = false;
	}

	theWindow->xChange_ = xPos - theWindow->lastX_;
	theWindow->yChange_ = theWindow->lastY_ - yPos;

	theWindow->lastX_ = xPos;
	theWindow->lastY_ = yPos;
}

Window::~Window() {
	glfwDestroyWindow(mainWindow_);
	glfwTerminate();
}



