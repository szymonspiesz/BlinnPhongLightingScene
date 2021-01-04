#include "vertexArray.h"
#include<iostream>

vertexArray::vertexArray()
{
	glGenVertexArrays(1, &vArrayID);
}

vertexArray::~vertexArray()
{
	glDeleteVertexArrays(1, &vArrayID);
}

void vertexArray::addVertexBuffer(const vertexBuffer& vBuffer, const vertexBufferLayout& vBufferLayout)
{
	bind();

	vBuffer.bind();
	//std::cout << glGetError() << std::endl;
	const auto& elements = vBufferLayout.getElements();
	unsigned int offset = 0;

	for (unsigned int i = 0; i < elements.size(); i++) {

		const auto& element = elements[i];

		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, element.count, element.type, element.normalized, vBufferLayout.getStrinde(), (const void*)offset);

		offset += element.count * vertexBufferLayoutElement::sizeOfType(element.type);

	}

}

void vertexArray::bind() const
{
	glBindVertexArray(vArrayID);
}

void vertexArray::unbind() const
{
	glBindVertexArray(0);
}
