#pragma once

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window
{
public:
	Window();
	Window(GLint windowWidth, GLint windowHeight);

	int initialize();

	GLfloat getBufferWidth() {
		return bufferWidth_;
	}

	GLfloat getBufferHeight() {
		return bufferHeight_;
	}

	bool getShouldClose() {
		return glfwWindowShouldClose(mainWindow_);
	}

	void swapBuffers() {
		glfwSwapBuffers(mainWindow_);
	}

	~Window();

private:
	GLFWwindow* mainWindow_;
	GLint width_, height_;
	GLint bufferWidth_, bufferHeight_;
};

