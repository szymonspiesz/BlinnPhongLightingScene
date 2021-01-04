#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inColor;

layout(location = 0) out vec3 outColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main() {
    gl_Position = proj * view * model * vec4(inPosition, 1.0f);
	outColor = inColor;
}