uniform LightSource lightSource;
uniform Material material;

uniform mat4 modelMatrix;
uniform mat3 normalMatrix;

in vec2 pass_textureCoords;
in vec4 pass_diffuse;

in vec3 pass_normalInterp;
in vec3 pass_vertPos;

in vec3 pass_ambient;

out vec4 outColor;

uniform sampler2D diffuseMap;

void calculateDiffuse(in vec4 textureDiffuse, out vec4 ambient, out vec4 diffuse) {
	ambient= lightSource.ambient*textureDiffuse;

	vec3 n= normalize(normalMatrix*pass_normalInterp.xyz);
	vec3 l= normalize(lightSource.position.xyz-(modelMatrix*vec4(pass_vertPos, 1.f)).xyz);

	diffuse= dot(n, l)*lightSource.diffuse*textureDiffuse;
}

void test(in vec4 ambientColor, in vec4 diffuseColor, out vec4 color) {

  vec3 normal = normalize(pass_normalInterp);
  vec3 lightDir = normalize(lightSource.position.xyz - pass_vertPos);

  float lambertian = max(dot(lightDir,normal), 0.0);
  float specular = 0.0;

  if(lambertian > 0.0) {

    vec3 viewDir = normalize(-pass_vertPos);

    // this is blinn phong
    vec3 halfDir = normalize(lightDir + viewDir);
    float specAngle = max(dot(halfDir, normal), 0.0);
    specular = pow(specAngle, 16.0);
       
    vec3 reflectDir = reflect(-lightDir, normal);
    specAngle = max(dot(reflectDir, viewDir), 0.0);
    specular = pow(specAngle, 4.0);
  }

  color = vec4(ambientColor +
                      lambertian * diffuseColor +
                      specular * lightSource.specular);
}

void main(void){
	
	vec4 textureDiffuseColor = texture(diffuseMap, pass_textureCoords);

	vec4 ambient;
	vec4 diffuse;

	calculateDiffuse(textureDiffuseColor, ambient, diffuse);

	vec4 color;

	test(ambient, diffuse, color);

	outColor = color;	
}