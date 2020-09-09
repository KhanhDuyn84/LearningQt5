#version 330 core

in vec3 Normal;
in vec3 FragPos;
in vec2 OurTexCoords;

out vec4 FragColor;

//uniform vec3 objectColor;
//uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

struct Material {
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

struct Light {
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

uniform Material material;
uniform Light light;

void main()
{
	//float ambientStrength = 0.1;
	//vec3 ambient = ambientStrength * lightColor;
	vec4 containerTexture = texture(material.diffuse, OurTexCoords);
	vec3 ambient = vec3(containerTexture) * light.ambient;
	
	vec3 norm = normalize(Normal);
	//vec3 lightDir = normalize(lightPos - FragPos);
	vec3 lightDir = normalize(lightPos - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	//vec3 diffuse = diff * lightColor;
	vec3 diffuse = (diff * vec3(containerTexture)) * light.diffuse;
	
	//float specularStrength = 0.5;
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	//float spec = pow(max(dot(viewDir, reflectDir), 0.0), 256);
	//vec3 specular = specularStrength * spec * lightColor;
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = (spec * vec3(texture(material.specular, OurTexCoords))) * light.specular;
	
	vec3 result = (ambient + diffuse + specular);
	FragColor = vec4(result, 1.0);
}