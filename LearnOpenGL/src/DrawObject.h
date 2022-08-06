#pragma once
#include "Application.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "ElementBuffer.h"

class DrawObject
{
private:
	VertexArray vao;
	VertexBuffer *vbo;
	ElementBuffer *ebo;

public:
	DrawObject(VertexBuffer* vbo, ElementBuffer* ebo);
	~DrawObject() = default;

	void draw();
};

