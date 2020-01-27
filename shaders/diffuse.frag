in vec2 pass_textureCoords;
in vec3 pass_normal;
in vec4 pass_diffuse;

out vec4 outColor;

uniform sampler2D diffuseMap;

void main(void){
	
	vec4 diffuseColor = texture(diffuseMap, pass_textureCoords);
	outColor = diffuseColor * pass_diffuse;
	//outColor = diffuseColor;
	//outColor = inColor;		
}
