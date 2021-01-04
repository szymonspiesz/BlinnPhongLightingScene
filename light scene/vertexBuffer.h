#pragma once


class vertexBuffer {

public:
	//id of a vertex buffer
	unsigned int vBufferID;
	vertexBuffer(const void* data, unsigned int size);
	~vertexBuffer();
	void bind() const;
	void unbind() const;


};