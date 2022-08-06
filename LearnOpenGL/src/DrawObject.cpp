#include "DrawObject.h"
#include "Application.h"

DrawObject::DrawObject(VertexBuffer *vbo, ElementBuffer* ebo)
{
	this->vao = VertexArray();
	this->vbo = vbo;
	this->ebo = ebo;
	vao.bind();
	vbo->bind();
	ebo->bind();

	GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (const void*)0));
	GLCall(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (const void*)(3 * sizeof(float))));
	GLCall(glEnableVertexAttribArray(0));
	GLCall(glEnableVertexAttribArray(1));
}

void DrawObject::draw()
{
	vao.bind();
	ebo->bind();
	GLCall(glDrawElements(GL_TRIANGLES, ebo->getCount(), GL_UNSIGNED_INT, nullptr));
}
