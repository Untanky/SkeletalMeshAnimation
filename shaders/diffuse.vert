const int MAX_JOINTS = 50;//max joints allowed in a skeleton
const int MAX_WEIGHTS = 3;//max number of joints that can affect a vertex

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform mat3 normalMatrix;

uniform LightSource lightSource;
uniform Material material;

uniform mat4 jointTransforms[MAX_JOINTS];
uniform mat4 projectionViewMatrix;

in vec3 position;
in vec3 normal;
in vec2 textureCoords;
in uvec3 jointIndices;
in vec3 weights;

out vec2 pass_textureCoords;
out vec4 pass_diffuse;

out vec3 pass_normalInterp;
out vec3 pass_vertPos;

out vec3 pass_ambient;
       
out vec4 inColor;
       
void deform(out vec4 totalLocalPos, out vec4 totalNormal) {
	totalLocalPos = vec4(0.0);
	totalNormal = vec4(0.0);

	for(int i=0;i<MAX_WEIGHTS;i++){
		mat4 jointTransform = jointTransforms[jointIndices[i]];
		vec4 posePosition = jointTransform * vec4(position, 1.0);
		totalLocalPos += posePosition * weights[i];
		
		vec4 worldNormal = jointTransform * vec4(normal, 0.0);
		totalNormal += worldNormal * weights[i];
	}
}

void shade(in vec4 totalLocalPos, in vec4 totalNormal) {
	vec4 ambient= lightSource.ambient*material.ambient;

	vec3 n= normalize(normalMatrix*totalNormal.xyz);
	vec3 l= normalize(lightSource.position.xyz-(modelMatrix*totalLocalPos).xyz);

	vec4 diffuse= dot(n, l)*lightSource.diffuse*material.diffuse;
   
	pass_diffuse = dot(n, l) * lightSource.diffuse;
}

void main(){
	vec4 totalLocalPos;
	vec4 totalNormal;

	deform(totalLocalPos, totalNormal);

	shade(totalLocalPos, totalNormal);

	// transform to clip space
	vec4 vertPos4 = viewMatrix * modelMatrix * totalLocalPos;
	gl_Position = projectionMatrix * vertPos4;

	pass_textureCoords = textureCoords;

	pass_vertPos = vec3(vertPos4) / vertPos4.w;
	pass_normalInterp = normalMatrix * totalNormal.xyz;
}
