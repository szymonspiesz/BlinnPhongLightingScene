#include "shaders.h"
#include <GL/glew.h>
#include <fstream>
#include <iostream>


shaders::shaders(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
	: shaderProgramID(0)
{
    std::string vertexShaderSrc = readFile(vertexShaderPath);
    std::string fragmentShaderSrc = readFile(fragmentShaderPath);

    shaderProgramID = createShaders(vertexShaderSrc, fragmentShaderSrc);

    bind();

}

shaders::~shaders()
{
	glDeleteProgram(shaderProgramID);
}

void shaders::bind() const
{
	glUseProgram(shaderProgramID);
}

void shaders::unbind() const
{
	glUseProgram(0);
}

void shaders::compileShader()
{
}

std::string shaders::readFile(const std::string& filename)
{
    std::ifstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error("failed to open file!");
    }
    std::string buffer;
    std::string line;

    while (getline(file, line)) {
        buffer += line + "\n";
    }
    file.close();

    return buffer;
}

unsigned int shaders::createShaders(const std::string& vertexShader, const std::string& fragmentShader) {
    unsigned int program = glCreateProgram();
    unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

unsigned int shaders::compileShader(unsigned int type, const std::string& source) {

    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);

    if (result == false) {

        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);

        std::cout << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader not compiled" << std::endl;
        std::cout << message << std::endl;

        glDeleteShader(id);
        return 0;
    }

    return id;
}

void shaders::setUniformMat4(const std::string& name, const float* value)
{
    glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, value);
}

void shaders::setUniformMat3(const std::string& name, const float* value)
{
    glUniformMatrix3fv(getUniformLocation(name), 1, GL_FALSE, value);
}

void shaders::setUniformVec3f(const std::string& name, const float* value)
{
    glUniform3fv(getUniformLocation(name), 1, value);
}

void shaders::setUniformFloat(const std::string& name, const float* value)
{
    glUniform1fv(getUniformLocation(name), 1, value);
}

int shaders::getUniformLocation(const std::string& name)
{
    if (uniformLocations.find(name) != uniformLocations.end()) {
        return uniformLocations[name];
    }

    int location = glGetUniformLocation(shaderProgramID, name.c_str());

    uniformLocations[name] = location;

    return location;
}
