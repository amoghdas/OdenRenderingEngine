#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <GL/glew.h>

class Shader
{
public:
	Shader();

	void createFromString(const char *vertexCode, const char *fragmentCode);
	void createFromFiles(const char* vertexLocation, const char* fragmentLocation);

	std::string readFile(const char* fileLocation);

	GLuint getProjectionLocation();
	GLuint getModelLocation();
	GLuint getViewLocation();

	void useShader();
	void clearShader();

	~Shader();

private:
	GLuint shaderID_, uniformProjection_, uniformModel_, uniformView_;

	void compileShader(const char* vertexCode, const char* fragmentCode);
	void addShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
};

