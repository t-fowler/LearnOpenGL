#include "VertexArray.h"
#include "Application.h"

VertexArray::VertexArray()
{
	GLCall(glGenVertexArrays(1, &arrayID));
	GLCall(glBindVertexArray(arrayID));
}

void VertexArray::bind()
{
	GLCall(glBindVertexArray(arrayID));
}

void VertexArray::unbind()
{
	GLCall(glBindVertexArray(0));
}
