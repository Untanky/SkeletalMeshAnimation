uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform mat3 normalMatrix;

uniform LightSource lightSource;
uniform Material material;

attribute vec4 position;
attribute vec3 normal;
       
varying vec4 color;
       
void main(){

  vec4 ambient= lightSource.ambient*material.ambient;

  vec3 n= normalize(normalMatrix*normal);
  vec3 l= normalize(lightSource.position.xyz-(modelMatrix*position).xyz);

  vec4 diffuse= dot(n, l)*lightSource.diffuse*material.diffuse;

  color= diffuse + ambient;

   // transform to clip space
   gl_Position = projectionMatrix*viewMatrix*modelMatrix*position;
}
