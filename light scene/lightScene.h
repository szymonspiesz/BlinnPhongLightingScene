#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <gtx/hash.hpp>

#include <iostream>
#include <fstream>
#include <String>
#include <vector>
#include <math.h>

#include "shaders.h"
#include "renderer.h"


#include "vertexBuffer.h"
#include "indexBuffer.h"
#include "vertexArray.h"

const int WIDTH = 640;
const int HEIGHT = 480;

struct vertex {
	glm::vec3 pos;
	glm::vec3 color;
	glm::vec3 normal;

	bool operator==(const vertex& other) const {
		return pos == other.pos && color == other.color && normal == other.normal;
	}
};

namespace std {
	template<> struct hash<vertex> {
		size_t operator()(vertex const& vert) const {
			return ((hash<glm::vec3>()(vert.pos) ^
				(hash<glm::vec3>()(vert.color) << 1)) >> 1) ^
				(hash<glm::vec2>()(vert.normal) << 1);
		}
	};
}

struct Material {
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float shininess;

};

struct model {

	unsigned int vertexBufferID;
	vertexArray* vArray;
	indexBuffer* iBuffer;
	shaders* shaderProgram;
	glm::mat4 modelMatrix;
	glm::vec3 initPosition;
	Material mat;

	model(vertexArray* va, indexBuffer* ib, shaders* sProgram, glm::mat4 modelMat, unsigned int vBufferID, Material& mats)
		:vArray(va), iBuffer(ib), shaderProgram(sProgram), modelMatrix(modelMat), vertexBufferID(vBufferID), mat(mats)
	{
	}

	glm::vec3 getPos() {
		return glm::vec3(modelMatrix[3][0], modelMatrix[3][1], modelMatrix[3][2]);
	}

};


class lightScene {

public:
	void run();

private:
	GLFWwindow* window;

	std::vector<int> keyStates;


	glm::mat4 proj;
	glm::mat4 view;

	//const glm::vec3 cubeColor = { 1.0f, 0.5f, 0.31f };
	//const glm::vec3 cubeColor = { 1.0f, 1.0f, 0.0f }; // yellow
	//const glm::vec3 cubeColor = { 0.804f, 0.498f, 0.196f }; // bronze
	const glm::vec3 cubeColor = { 0.0f, 0.92f, 0.0f }; // emerald
	const glm::vec3 sceneColor = { 0.2f, 0.2f, 0.2f };
	glm::vec3 lightColor = { 0.8f, 0.8f, 0.8f };

	std::vector<model> models;
	bool modelsInitialized = false;


	void initWindow();
	void mainLoop();
	void drawFrame(renderer& renderProgram);
	void loadModel(std::string path, std::vector<vertex>& vertices, std::vector<unsigned int>& indices);
	void initModels();
	void keyboardAction();
	static void keyPressed(GLFWwindow* window, int key, int scancode, int action, int mods);
	


};





