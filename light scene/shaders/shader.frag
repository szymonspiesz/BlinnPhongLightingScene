#version 450
#extension GL_ARB_separate_shader_objects : enable


struct Material{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

in vec3 Color;
in vec3 Normal;
in vec3 FragPos;

out vec4 outColor;

uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform Material mat;

void main() {

	//ambient
	vec3 ambient = mat.ambient * lightColor;
	
	//diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	float diffuseStrength = max(dot(norm, lightDir), 0.0f);
	vec3 diffuse = diffuseStrength * mat.diffuse * lightColor;
	
	//specular
	vec3 specular = vec3(0.0f);
	vec3 viewDir = normalize(viewPos - FragPos);
		//if(diffuseStrength > 0){
		// phong //
		//vec3 reflDir = reflect(lightDir, norm);
		//float spec = pow(max(dot(viewDir, reflDir), 0.0f), mat.shininess * 128.0);

		// blinn //
		vec3 halfwayDir = normalize(lightDir - viewDir);
		float spec = pow(max(dot(norm, halfwayDir), 0.0f), mat.shininess * 32.0);
		
		specular = mat.specular * spec * lightColor;
		//}
	
	vec3 result = (ambient + diffuse + specular) * Color;
	
    outColor = vec4(result, 1.0f);
}