#version 460 core 

out vec4 FragColor; 
in vec2 TexCoords; 

struct Material { 
	sampler2D texture_diffuse1;
	sampler2D texture_specular1; 
}; 

uniform Material material; 

void main() {
	vec3 color = texture(material.texture_diffuse1, TexCoords).rgb; 
	FragColor = vec4(color, 1.0); 
}




