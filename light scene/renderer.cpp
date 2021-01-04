#include "renderer.h"
#include<iostream>



void renderer::draw(const vertexArray& vArray, const indexBuffer& iBuffer, const shaders& shaderProgram) const
{
	shaderProgram.bind();


	vArray.bind(); 


	iBuffer.bind();


	glDrawElements(GL_TRIANGLES, iBuffer.getIndexCount(), GL_UNSIGNED_INT, nullptr);
}

void renderer::clear() const
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
