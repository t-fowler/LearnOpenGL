#include "ElementBuffer.h"
#include "Application.h"

ElementBuffer::ElementBuffer(const unsigned int* data, int count)
    : count(count)
{
    GLCall(glGenBuffers(1, &bufferID));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferID));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

void ElementBuffer::bind()
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferID));
}

void ElementBuffer::unbind()
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
