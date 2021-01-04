#pragma once


class indexBuffer {

public:
	//how many indices
	unsigned int indexCount;
	//id of an index buffer
	unsigned int iBufferID;
	indexBuffer(const unsigned int* data, unsigned int count);
	~indexBuffer();
	void bind() const;
	void unbind() const;

	inline unsigned int getIndexCount() const { return indexCount; }
};