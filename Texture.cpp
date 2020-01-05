/* ----------------------------------------------------------------
   name:           Texture.cpp
   purpose:        cg_ex4 texturing tutorial
   version:	   SKELETON CODE
   TODO:           generateTexture(), ~Texture(), setWrapS(), setWrapT(), setMinFilter(), setMagFilter(), bind()
   author:         katrin lang
                   computer graphics
                   htw berlin
   ------------------------------------------------------------- */

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

#include "Texture.hpp"

using namespace std;
using namespace glm;

Texture::Texture() 
     : width(0)
     , height(0) 
     , wrapS(GL_REPEAT)
     , wrapT(GL_REPEAT)
     , min(GL_LINEAR)
     , mag(GL_LINEAR)
     , textureID(0){
}

Texture::Texture(int width, int height)
     : width(width)
     , height(height)
     , data(width*height)
     , wrapS(GL_REPEAT)
     , wrapT(GL_REPEAT)
     , min(GL_LINEAR)
     , mag(GL_LINEAR)
     , textureID(0)
{}

// TODO: free OpenGL texture
// XXX: NEEDS TO BE IMPLEMENTED
Texture::~Texture(){
  
  // XXX

  // INSERT YOUR CODE HERE

  // END XXX
}

// TODO: generate OpenGL texture
// XXX: NEEDS TO BE IMPLEMENTED
void Texture::generateTexture(){ 
  
  if(textureID==0){
    // generate texture id
    // XXX

	glGenTextures(1, &textureID);
    
    // END XXX
  }
  
  // texture filtering and repeat
  // XXX



  // END XXX
  
  // enable automatic mipmap generation
  // XXX
  
  bind();
  glTextureParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, 1);

  // END XXX
  
  // upload texture data
  // XXX

	bind();
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_FLOAT, data.data());
	unbind();

  // END XXX
}

 // return textureID 
  // which can be passed to shader 
  // as uniform
GLuint Texture::id(void){
  return textureID;
}

void Texture::setWrapS(GLuint wrap){

  this->wrapS= wrap;

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
}

void Texture::setWrapT(GLuint wrap){

  this->wrapT= wrap;

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

// set both wrapping modes
void Texture::setWrap(GLuint wrap){
  setWrapS(wrap);
  setWrapT(wrap);
}

void Texture::setMinFilter(GLuint min){

  this->min= min;

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min);
}

void Texture::setMagFilter(GLuint mag){

  this->mag= mag;

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag);
}

void Texture::bind(){
	glBindTexture(GL_TEXTURE_2D, textureID);
}

void Texture::unbind(){
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::load(const std::string& filename){

  data.clear();

  if(filename.substr(filename.size()-4, 4) == ".ppm") loadPPM(filename);
  else{
      cerr << "file " << filename << " is not a PPM file" << endl;
      return;
  }

  generateTexture();
}

void Texture::loadPPM(const std::string& filename){
  
  ifstream file(filename.c_str(), ios::binary);
  
  if(!file.is_open()){
    cerr << "opening file " << filename << " failed" << endl;
    return;
  }
  
  // grab first two chars of the file and make sure that it has the
  // correct magic cookie for a raw PPM file.
  string magic;
  getline(file, magic);
  if(magic.substr(0, 2) != "P6"){
    cerr << "File " << filename << " is not a raw PPM file" << endl;
    return;
  }
  
  // grab the three elements in the header (width, height, maxval).
  string dimensions;
  do{
    getline(file, dimensions);
  }
  while(dimensions[0] == '#');
  
  stringstream(dimensions) >> width >> height;
  
  string max;
  getline(file, max);
  int maxValue;
  stringstream(max) >> maxValue;
  // grab all the Texture data in one fell swoop.
  vector<char> raw(width*height*3);
  file.read(&raw[0], raw.capacity());
  file.close();
  
  data.resize(width*height);
  for(int y = 0; y < height; y++){
    for(int x = 0; x < width; x++){
      data[y*width+x]= vec4((unsigned char)raw[(height - y-1) * width * 3 + 3*x], (unsigned char)raw[(height - y-1) * width * 3 + 3*x + 1], (unsigned char)raw[(height - y-1) * width * 3 + 3*x + 2], maxValue);
      data[y*width+x]/= maxValue; 
    }
  }
  
  raw.clear();
  
  std::cout << "Texture " << filename << " loaded. width: " << width << " height: " << height << endl;
}
