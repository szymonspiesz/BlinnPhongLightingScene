#include "indexBuffer.h"

#include <gl/glew.h>


indexBuffer::indexBuffer(const unsigned int* data, unsigned int count)
    : indexCount(count)
{
    glGenBuffers(1, &iBufferID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iBufferID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
}

indexBuffer::~indexBuffer()
{
    glDeleteBuffers(1, &iBufferID);
}

void indexBuffer::bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iBufferID);
}

void indexBuffer::unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
