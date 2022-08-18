#pragma once

#include <iostream>
#include <stdio.h>
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

	bool* getKeys()  {
		return keys_;
	}

	GLfloat getXChange();
	GLfloat getYChange();

	void swapBuffers() {
		glfwSwapBuffers(mainWindow_);
	}

	~Window();

private:
	GLFWwindow* mainWindow_;
	GLint width_, height_;
	GLint bufferWidth_, bufferHeight_;

	bool keys_[1024];

	GLfloat lastX_;
	GLfloat lastY_;
	GLfloat xChange_;
	GLfloat yChange_;
	bool mouseFirstMoved_;

	void createCallbacks();
	static void handleKeys(GLFWwindow *window, int key, int code, int action, int mode);
	static void handleMouse(GLFWwindow* window, double xPos, double yPos);
};

