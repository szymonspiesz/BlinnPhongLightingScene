#pragma once

#include<vector>
#include<GL/glew.h>
#include<glm.hpp>



struct vertexBufferLayoutElement {
	unsigned int type;
	unsigned int count;
	unsigned char normalized;

	static unsigned int sizeOfType(unsigned int type) {
		switch (type) {
		case GL_FLOAT: return 4;
		case GL_UNSIGNED_INT: return 4;
		case GL_UNSIGNED_BYTE: return 1;
		}
		return 0;
	}

};

class vertexBufferLayout {

private:
	std::vector<vertexBufferLayoutElement> elements;
	unsigned int stride;

public:

	vertexBufferLayout() 
		: stride(0) {}

	~vertexBufferLayout() {}

	template<typename T>
	void push(unsigned int count){
		static_assert(false);
	}
	
	template<>
	void push<float>(unsigned int count) {
		elements.push_back({GL_FLOAT, count, GL_FALSE});
		stride += vertexBufferLayoutElement::sizeOfType(GL_FLOAT) * count;
	}

	template<>
	void push<unsigned int>(unsigned int count) {
		elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		stride += vertexBufferLayoutElement::sizeOfType(GL_UNSIGNED_INT) * count;
	}

	template<>
	void push<unsigned char>(unsigned int count) {
		elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
		stride += vertexBufferLayoutElement::sizeOfType(GL_UNSIGNED_BYTE) * count;
	}

	inline unsigned int getStrinde() const { return stride; }
	inline const std::vector<vertexBufferLayoutElement>& getElements() const { return elements; }
};