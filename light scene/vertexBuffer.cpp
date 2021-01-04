#include "vertexBuffer.h"

#include <gl/glew.h>

vertexBuffer::vertexBuffer(const void* data, unsigned int size)
{
    glGenBuffers(1, &vBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, vBufferID);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

vertexBuffer::~vertexBuffer()
{
    glDeleteBuffers(1, &vBufferID);
}

void vertexBuffer::bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, vBufferID);
}

void vertexBuffer::unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
