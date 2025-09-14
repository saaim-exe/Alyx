#version 460 core 

out vec4 FragColor; 


// in vec3 Color;

in vec3 NormalFragment;
in vec2 TexCoord; 
in vec3 FragPos;


// uniform vec3 color; 
// uniform sampler2D texture1; 

uniform vec3 objectColor; 
uniform vec3 lightColor; 
uniform vec3 lightPos; 
uniform vec3 viewPos; 

struct Material { 
	sampler2D diffuse; 
	sampler2D specular; 
	float shininess; 

};

struct Light { 
	vec3 position; 
	// vec3 direction; 

	vec3 ambient; 
	vec3 diffuse; 
	vec3 specular; 

	float constant; 
	float linear; 
	float quadratic; 

};


uniform Material material; 
uniform Light light; 


void main() {

	float ambientStrength = 0.1; 
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoord));  

	vec3 norm = normalize(NormalFragment);
	vec3 lightDir = normalize(light.position - FragPos); 
	// vec3 lightDir = normalize(-light.direction); 


	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoord));

	float specularStrength = 0.5; 

	vec3 viewDir = normalize(viewPos - FragPos); 
	vec3 reflectDir = reflect(-lightDir, norm); 

	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoord)); 

	// attenuation
	float distance = length(light.position - FragPos); 
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance)); 

	ambient *= attenuation; 
	diffuse *= attenuation;
	specular *= attenuation;

	vec3 result = (ambient + diffuse + specular);


	FragColor = vec4(result, 1.0); 
}