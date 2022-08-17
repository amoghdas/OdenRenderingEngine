#include "mesh.h"

Mesh::Mesh() {
	VAO_ = 0;
	VBO_ = 0;
	IBO_ = 0;
	indexCount_ = 0;
}

void Mesh::createMesh(GLfloat* vertices, unsigned int* indices, unsigned int numOfVertices, unsigned int numOfIndices) {
	indexCount_ = numOfIndices;

	glGenVertexArrays(1, &VAO_);
	glBindVertexArray(VAO_);

	glGenBuffers(1, &IBO_);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO_);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * numOfIndices, indices, GL_STATIC_DRAW);

	glGenBuffers(1, &VBO_);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * numOfVertices, vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

void Mesh::renderMesh() {
	glBindVertexArray(VAO_);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO_);
	glDrawElements(GL_TRIANGLES, indexCount_, GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Mesh::clearMesh() {
	if (IBO_ != 0) {
		glDeleteBuffers(1, &IBO_);
		IBO_ = 0;
	}

	if (VBO_ != 0) {
		glDeleteBuffers(1, &VBO_);
		VBO_ = 0;
	}

	if (VAO_ != 0) {
		glDeleteVertexArrays(1, &VAO_);
		VAO_ = 0;
	}

	indexCount_ = 0;
}

Mesh::~Mesh() {
	clearMesh();
}