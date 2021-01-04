#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inColor;
layout(location = 2) in vec3 inNormal;

out vec3 Color;
out vec3 Normal;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main() {

	//FragPos = vec3(model * vec4(inPosition, 1.0f));
	FragPos = (model * vec4(inPosition, 1.0f)).xyz;
	Color = inColor;
	
	Normal = mat3(transpose(inverse(model))) * inNormal;

    gl_Position = proj * view * vec4(FragPos, 1.0f);
}