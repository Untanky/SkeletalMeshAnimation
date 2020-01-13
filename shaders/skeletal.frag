#version 150

const vec2 lightBias = vec2(0.7, 0.6);//just indicates the balance between diffuse and ambient lighting

in vec2 pass_textureCoords;
in vec3 pass_normal;

out vec4 out_colour;

uniform sampler2D diffuseMap;
uniform vec3 lightDirection;

void main(void){

	gl_FragColor = vec3(0, 1, 0);
	
}