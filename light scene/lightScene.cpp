#include "lightScene.h"
#include "unordered_map"

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

std::vector<vertex> cubeVertices = {
	{{-1.0, -1.0,  1.0}, {1.0f, 0.5f, 0.31f}},
	{{ 1.0, -1.0,  1.0}, {1.0f, 0.5f, 0.31f}},
	{{ 1.0,  1.0,  1.0}, {1.0f, 0.5f, 0.31f}},
	{{-1.0,  1.0,  1.0}, {1.0f, 0.5f, 0.31f}},
	{{-1.0, -1.0, -1.0}, {1.0f, 0.5f, 0.31f}},
	{{ 1.0, -1.0, -1.0}, {1.0f, 0.5f, 0.31f}},
	{{ 1.0,  1.0, -1.0}, {1.0f, 0.5f, 0.31f}},
	{{-1.0,  1.0, -1.0}, {1.0f, 0.5f, 0.31f}},
};
std::vector<unsigned int> cubeIndices = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3
};

std::vector<vertex> lightVertices = {
	{{-1.0, -1.0,  1.0}, {1.0f, 0.0f, 0.0f}},
	{{ 1.0, -1.0,  1.0}, {0.0f, 1.0f, 0.0f}},
	{{ 1.0,  1.0,  1.0}, {0.0f, 0.0f, 1.0f}},
	{{-1.0,  1.0,  1.0}, {1.0f, 1.0f, 1.0f}},
	{{-1.0, -1.0, -1.0}, {1.0f, 0.0f, 0.0f}},
	{{ 1.0, -1.0, -1.0}, {0.0f, 1.0f, 0.0f}},
	{{ 1.0,  1.0, -1.0}, {0.0f, 0.0f, 1.0f}},
	{{-1.0,  1.0, -1.0}, {1.0f, 1.0f, 1.0f}},
};

std::vector<unsigned int> lightIndices = {
	// front
	0, 1, 2,
	2, 3, 0,
	// right
	1, 5, 6,
	6, 2, 1,
	// back
	7, 6, 5,
	5, 4, 7,
	// left
	4, 0, 3,
	3, 7, 4,
	// bottom
	4, 5, 1,
	1, 0, 4,
	// top
	3, 2, 6,
	6, 7, 3
};

void lightScene::run()
{
	initWindow();
	initModels();
	mainLoop();
}

void lightScene::initWindow()
{
	if(!glfwInit())
		throw std::runtime_error("glfw failed to init");

	window = glfwCreateWindow(WIDTH, HEIGHT, "Light Scene", nullptr, nullptr);

	glfwMakeContextCurrent(window);

	//set this class as a user of glfw window
	glfwSetWindowUserPointer(window, this);

	if (glewInit() != GLEW_OK)
		throw std::runtime_error("glew failed to init");


	keyStates.resize(4);
	keyStates[0] = -1; //arrow left
	keyStates[1] = -1; //arrow right
	keyStates[2] = -1; //arrow up
	keyStates[3] = -1; //arrow down

	glfwSetKeyCallback(window, keyPressed);

}

void lightScene::mainLoop()
{
	renderer renderProgram;
	
	while (!glfwWindowShouldClose(window)) {
		drawFrame(renderProgram);
	}
}

void lightScene::drawFrame(renderer& renderProgram)
{
	renderProgram.clear();

	keyboardAction();


	//models[0].modelMatrix = glm::rotate(models[0].modelMatrix, glm::radians(1.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	models[1].modelMatrix = glm::rotate(glm::translate(models[1].modelMatrix, glm::vec3(-26.0f, 0.0f, 28.0f)), glm::radians(-1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	models[1].modelMatrix = glm::translate(models[1].modelMatrix, glm::vec3(26.0f, 0.0f, -28.0f));
	
	for (size_t i = 0; i < models.size(); i++) {
		
		models[i].shaderProgram->bind();

		if (i == 0 || i == 2) {
			models[i].shaderProgram->setUniformMat4("model", glm::value_ptr(models[i].modelMatrix));
			models[i].shaderProgram->setUniformMat4("view", glm::value_ptr(view));
			models[i].shaderProgram->setUniformMat4("proj", glm::value_ptr(proj));

				models[i].shaderProgram->setUniformVec3f("lightColor", glm::value_ptr(lightColor));

			models[i].shaderProgram->setUniformVec3f("lightPos", glm::value_ptr(models[1].getPos()));
			models[i].shaderProgram->setUniformVec3f("viewPos", glm::value_ptr(glm::vec3(view[3][0], view[3][1], view[3][2])));

			models[i].shaderProgram->setUniformVec3f("mat.ambient", glm::value_ptr(models[i].mat.ambient));
			models[i].shaderProgram->setUniformVec3f("mat.diffuse", glm::value_ptr(models[i].mat.diffuse));
			models[i].shaderProgram->setUniformVec3f("mat.specular", glm::value_ptr(models[i].mat.specular));
			models[i].shaderProgram->setUniformFloat("mat.shininess", &models[i].mat.shininess);
		}
		else {
			models[i].shaderProgram->setUniformMat4("model", glm::value_ptr(models[i].modelMatrix));
			models[i].shaderProgram->setUniformMat4("view", glm::value_ptr(view));
			models[i].shaderProgram->setUniformMat4("proj", glm::value_ptr(proj));
		}
		renderProgram.draw(*models[i].vArray, *models[i].iBuffer, *models[i].shaderProgram);
		
	}


	glfwSwapBuffers(window);

	glfwPollEvents();

}

void lightScene::loadModel(std::string path, std::vector<vertex>& vertices, std::vector<unsigned int>& indices) {

	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	std::string warn;
	std::string err;

	tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, path.c_str());

	std::unordered_map<vertex, uint32_t> uniqueVertices{};
	// Loop over shapes
	for (size_t s = 0; s < shapes.size(); s++) {
		// Loop over faces(polygon)
		size_t index_offset = 0;
		for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
			int fv = shapes[s].mesh.num_face_vertices[f];

			// Loop over vertices in the face.
			for (size_t v = 0; v < fv; v++) {
				// access to vertex
				tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
				tinyobj::real_t vx = attrib.vertices[3 * idx.vertex_index + 0];
				tinyobj::real_t vy = attrib.vertices[3 * idx.vertex_index + 1];
				tinyobj::real_t vz = attrib.vertices[3 * idx.vertex_index + 2];
				tinyobj::real_t nx = attrib.normals[3 * idx.normal_index + 0];
				tinyobj::real_t ny = attrib.normals[3 * idx.normal_index + 1];
				tinyobj::real_t nz = attrib.normals[3 * idx.normal_index + 2];
				tinyobj::real_t tx = attrib.texcoords[2 * idx.texcoord_index + 0];
				tinyobj::real_t ty = attrib.texcoords[2 * idx.texcoord_index + 1];
				// Optional: vertex colors
				// tinyobj::real_t red = attrib.colors[3*idx.vertex_index+0];
				// tinyobj::real_t green = attrib.colors[3*idx.vertex_index+1];
				// tinyobj::real_t blue = attrib.colors[3*idx.vertex_index+2];

				glm::vec3 col = cubeColor;
				
				//change normals for cube scene
				if (models.size() == 1) {
					col = sceneColor;
					nx *= -1;
					ny *= -1;
					nz *= -1;
				}

				vertex vert = { {vx, vy, vz},
								 col,
								{nx, ny, nz} };


				if (uniqueVertices.count(vert) == 0) {
					uniqueVertices[vert] = static_cast<uint32_t>(vertices.size());
					vertices.push_back(vert);
				}

				indices.push_back(uniqueVertices[vert]);

			}
			index_offset += fv;

		}
	}


}

void lightScene::initModels()
{
	glEnable(GL_DEPTH_TEST);

	//view and proj matrices
	view = glm::lookAt(glm::vec3(0.0f, 2.0f, 60.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	proj = glm::perspective(glm::radians(45.0f), (float)WIDTH/HEIGHT, 0.1f, 200.0f);


	//data layout in vertex buffer
	vertexBufferLayout vBufferLayout;
	vBufferLayout.push<float>(3); //positions
	vBufferLayout.push<float>(3); //colors
	vBufferLayout.push<float>(3); //normals


	std::vector<vertex> vertices;
	std::vector<unsigned int> indices;

	//
	//SPHERE
	//

	//load sphere data
	loadModel("../models/duck.obj", vertices, indices);

	//sphere model matrix
	glm::mat4 mode = glm::scale(glm::rotate(glm::translate(glm::mat4(1), glm::vec3(0.0f, -8.0f, 0.0f)), glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f)), glm::vec3(0.3f)); // duck
	//glm::mat4 mode = glm::scale(glm::mat4(1), glm::vec3(2.0f)); //cube

	//sphere vertex buffer
	vertexBuffer* vBufferSphere = new vertexBuffer(vertices.data(), vertices.size() * sizeof(vertex));

	//sphere vertex array
	vertexArray* vArraySphere = new vertexArray();
	vArraySphere->addVertexBuffer(*vBufferSphere, vBufferLayout);

	//sphere shaders
	shaders* shaderProgram = new shaders("shaders/shader.vert", "shaders/shader.frag");

	//sphere material
	Material sphereMat;

	
	//emerald
	sphereMat.ambient  = glm::vec3(0.0215f, 0.1745f, 0.0215f);
	sphereMat.diffuse  = glm::vec3(0.07568f, 0.61424f, 0.07568f);
	sphereMat.specular = glm::vec3(0.633f, 0.727811f, 0.633f);
	sphereMat.shininess = 0.6f;
	

	/*
	//yellow Rubber
	sphereMat.ambient = glm::vec3(0.05f, 0.05f, 0.0f);
	sphereMat.diffuse = glm::vec3(0.5f, 0.5f, 0.4f);
	sphereMat.specular = glm::vec3(0.3f, 0.3f, 0.04f);
	sphereMat.shininess = 0.078125f;
	*/

	/*
	//ruby
	sphereMat.ambient = glm::vec3(0.1745f, 0.01175f, 0.01175f);
	sphereMat.diffuse = glm::vec3(0.61424f, 0.04136f, 0.04136f);
	sphereMat.specular = glm::vec3(0.727811f, 0.626959f, 0.626959f);
	sphereMat.shininess = 0.6f;
	*/

	/*
	//bronze
	sphereMat.ambient = glm::vec3(0.2125f, 0.1275f, 0.054f);
	sphereMat.diffuse = glm::vec3(0.714f, 0.4284f, 0.18144f);
	sphereMat.specular = glm::vec3(0.393548f, 0.271906f, 0.166721f);
	sphereMat.shininess = 0.2f;
	*/

	//create sphere model
	model sphere(vArraySphere, new indexBuffer(indices.data(), indices.size()), shaderProgram, mode, vBufferSphere->vBufferID, sphereMat);
	sphere.initPosition = sphere.getPos();
	models.push_back(sphere);
	

	//
	//LIGHT
	//

	std::vector<vertex> lightVertices;
	std::vector<unsigned int> lightIndices;

	//load light cube data
	loadModel("../models/cube.obj", lightVertices, lightIndices);

	//light cube model matrix
	mode = glm::scale(glm::translate(glm::mat4(1), glm::vec3(26.0f, 0.0f, -28.0f)), glm::vec3(1.0f));

	//light cube vertex buffer
	vertexBuffer* vBufferLight = new vertexBuffer(lightVertices.data(), lightVertices.size() * sizeof(vertex));

	//light cube vertex array
	vertexArray* vArrayLight = new vertexArray();
	vArrayLight->addVertexBuffer(*vBufferLight, vBufferLayout);

	//light cube shaders
	shaders* lightShaderProgram = new shaders("shaders/lightShader.vert", "shaders/lightShader.frag");

	//light cube material
	Material lightMat;
	lightMat.ambient  = glm::vec3(1.0f, 1.0f, 1.0f);
	lightMat.diffuse  = glm::vec3(1.0f, 1.0f, 1.0f);
	lightMat.specular = glm::vec3(1.0f, 1.0f, 1.0f);
	lightMat.shininess = 0.5f;

	//create light cube model
	model light(vArrayLight, new indexBuffer(lightIndices.data(), lightIndices.size()), lightShaderProgram, mode, vBufferLight->vBufferID, lightMat);
	light.initPosition = light.getPos();
	models.push_back(light);

	//
	//SCENE
	//

	//scene model matrix
	mode = glm::scale(glm::mat4(1), glm::vec3(60.0f, 40.0f, 60.0f));

	//scene material
	Material sceneMat;
	sceneMat.ambient  = glm::vec3(0.1f, 0.1f, 0.1f);
	sceneMat.diffuse  = glm::vec3(1.0f, 1.0f, 1.0f);
	sceneMat.specular = glm::vec3(0.0f, 0.0f, 0.0f);
	sceneMat.shininess = 1.0f;

	//create scene model
	model scene(vArrayLight, new indexBuffer(lightIndices.data(), lightIndices.size()), shaderProgram, mode, vBufferLight->vBufferID, sceneMat);
	models.push_back(scene);

	modelsInitialized = true;
}

void lightScene::keyboardAction() {

	if (keyStates[0] == 1) {
		models[1].modelMatrix = glm::translate(models[1].modelMatrix, glm::vec3(-0.3f, 0.0f, 0.0f));
	}

	if (keyStates[1] == 1) {
		models[1].modelMatrix = glm::translate(models[1].modelMatrix, glm::vec3(0.3f, 0.0f, 0.0f));
	}

	if (keyStates[2] == 1) {
		models[1].modelMatrix = glm::translate(models[1].modelMatrix, glm::vec3(0.0f, 0.0f, -0.3f));
	}

	if (keyStates[3] == 1) {
		models[1].modelMatrix = glm::translate(models[1].modelMatrix, glm::vec3(0.0f, 0.0f, 0.3f));
	}

}


void lightScene::keyPressed(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	auto app = reinterpret_cast<lightScene*>(glfwGetWindowUserPointer(window));


	if (action == GLFW_PRESS && key == GLFW_KEY_LEFT) app->keyStates[0] = 1; //left arrow pressed
	if (action == GLFW_PRESS && key == GLFW_KEY_RIGHT) app->keyStates[1] = 1; //right arrow pressed

	if (action == GLFW_RELEASE && key == GLFW_KEY_LEFT) app->keyStates[0] = -1; //left arrow released
	if (action == GLFW_RELEASE && key == GLFW_KEY_RIGHT) app->keyStates[1] = -1; //right arrow released


	if (action == GLFW_PRESS && key == GLFW_KEY_UP) app->keyStates[2] = 1; //up arrow pressed
	if (action == GLFW_PRESS && key == GLFW_KEY_DOWN) app->keyStates[3] = 1; //down arrow pressed

	if (action == GLFW_RELEASE && key == GLFW_KEY_UP) app->keyStates[2] = -1; //up arrow released
	if (action == GLFW_RELEASE && key == GLFW_KEY_DOWN) app->keyStates[3] = -1; //down arrow released

	if (action == GLFW_PRESS && key == GLFW_KEY_SPACE) { //space pressed

	}

}
