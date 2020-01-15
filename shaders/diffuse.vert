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
out vec3 pass_normal;
       
out vec4 inColor;
       
void main(){

	vec4 totalLocalPos = vec4(0.0);
	vec4 totalNormal = vec4(0.0);

	for(int i=0;i<MAX_WEIGHTS;i++){
		mat4 jointTransform = jointTransforms[jointIndices[i]];
		vec4 posePosition = jointTransform * vec4(position, 1.0);
		totalLocalPos += posePosition * weights[i];
		
		vec4 worldNormal = jointTransform * vec4(normal, 0.0);
		totalNormal += worldNormal * weights[i];
	}

  vec4 ambient= lightSource.ambient*material.ambient;

  vec3 n= normalize(normalMatrix*totalNormal.xyz);
  vec3 l= normalize(lightSource.position.xyz-(modelMatrix*totalLocalPos).xyz);

  vec4 diffuse= dot(n, l)*lightSource.diffuse*material.diffuse;

  inColor= diffuse + ambient;
  //inColor = vec4(jointIndices, 1);

   // transform to clip space
   gl_Position = projectionMatrix*viewMatrix*modelMatrix*totalLocalPos;
   
	pass_normal = totalNormal.xyz;
	pass_textureCoords = textureCoords;
}
