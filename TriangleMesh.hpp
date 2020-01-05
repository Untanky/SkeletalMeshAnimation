/* ----------------------------------------------------------------
   name:           TriangleMesh.cpp
   purpose:        cg1_ex3 2014 triangle mesh for OpenGL rendering
   version:	   SKELETON CODE
   TODO:           nothing (see TriangleMesh.cpp)
   author:         katrin lang
                   computer graphics
                   tu berlin
   ------------------------------------------------------------- */

#pragma once

#include <string>
#include <vector>

#include "GLIncludes.hpp"

// OpenGL mathematics library
// http://glm.g-truc.net
#include "glm/glm.hpp"

/*
 * Class for a simple triangle mesh represented as an indexed face set
 */
class TriangleMesh{

public:

  // default constructor
  TriangleMesh();
  
  // constructor, calls loadOff()
  TriangleMesh(const std::string& fileName);

  // destructor
  ~TriangleMesh();

  // clockwise / counter-clockwise?
  enum PolygonWinding{
    CW,
    CCW
  };
  
  // set polygon winding
  void setWinding(PolygonWinding winding);
  
  // load the mesh
  virtual void load(const std::string& filename);

  // normalize to bounding sphere radius 1
  void unitize(void);
  // center model
  void center(void);
  // compute bounding sphere
  void computeBoundingSphere(void);
  // compute bounding box
  void computeBoundingBox(void);

  bool hasNormals(void);
  // compute the normals of the vertices
  void computeNormals(void);

  // draw the model
  virtual void draw(void);
  
  // vertex attribute bindings
  // see https://www.opengl.org/sdk/docs/tutorials/ClockworkCoders/attributes.php
  static const GLuint attribVertex;
  static const GLuint attribNormal;
  static const GLuint attribColor;
  static const GLuint attribTexCoord;

protected:
  
  // load the mesh from an off file
  void loadOff(const std::string& fileName);
  // load the mesh from an off file
  void loadObj(const std::string& fileName);
  void triangulate(std::vector<GLuint> pi, std::vector<GLuint> ti, std::vector<GLuint> ni);
  void clean();
  
  // Position of the vertices
  std::vector<glm::vec3> positions;
  // normals of the vertices
  std::vector<glm::vec3> normals;
  std::vector<glm::vec3> normalsRaw;
  // texture coordinates
  std::vector<glm::vec2> texCoords;
  std::vector<glm::vec2> texCoordsRaw;
  
  // indices of the faces
  std::vector<glm::uvec3> faces;
  // (raw) indices of the normals
  std::vector<glm::uvec3> normalIndices;
  // (raw) indices of the texture coordinates
  std::vector<glm::uvec3> texCoordIndices;
  
  PolygonWinding winding;

  float boundingSphereRadius;
  // two opposite corners of bounding box 
  glm::vec3 boundingBoxMin;
  glm::vec3 boundingBoxMax;
};
