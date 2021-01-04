#pragma once

#include"vertexArray.h"
#include"indexBuffer.h"
#include"shaders.h"


class renderer {

private:

public:
	void draw(const vertexArray& vArray, const indexBuffer& iBuffer, const shaders& shaderProgram) const;
	void clear() const;
};