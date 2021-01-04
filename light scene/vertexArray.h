#pragma once

#include "vertexBuffer.h"
#include "vertexBufferLayout.h"

class vertexArray {

//private:

public:
	unsigned int  vArrayID;
	vertexArray();
	~vertexArray();

	void addVertexBuffer(const vertexBuffer& vBuffer, const vertexBufferLayout& vBufferLayout);
	void bind() const;
	void unbind() const;

};