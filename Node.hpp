#pragma once

/* ----------------------------------------------------------------
   name:           Node.hpp
   purpose:        class declaration for a scenegraph node
   version:	   SKELETON CODE
   TODO:           nothing (see Node.cpp)
   author:         katrin lang
				   computer graphics
				   htw berlin
   ------------------------------------------------------------- */

#include "glm/glm.hpp"

using namespace glm;

#include "RotationMode.hpp"
#include "Mesh.h"
#include "Joint.h"
#include "shaders/Material.h"

// NOTE: each node in the scenegraph can have multiple 
//       children/siblings by pointing to its first child via 
//       the 'child' pointer and then linking up the children 
//       using the 'sibling' pointers (previous and next). 
//       in the following example diagram, N = node
//
//
//       the diagram/linking:
//
//                    N (root node of this example scenegraph)
//                   /
//               child
//                /
//               N - sibling - N - sibling - N
//              /             /
//          child         child        
//           /             /
//          N             N - sibling - N
// 
//
//       represents the following scenegraph/tree:
//
//
//                    N (root node of this example scenegraph)
//                   /|\
//                 /  |  \
//               N    N   N
//              /    /|
//            /    /  |
//           N    N   N
//

class Node {

public:

	// constructor
	// x,y,z: position of node center of mass relative to parent node center
	// length, height, and width of this body part
	// jointx, jointy, jointz: x,y,z offset of  rotation axis from center of body part
	// i.e. for rotation about a "shoulder" as opposed to the center of mass of a glutsolidcube
	// x,y,z: rotation (in degrees) of node relative to parent node rotation
	Node(Mesh* mesh,
		Material material,
		float x, float y, float z,
		float length, float height, float width,
		float jointx, float jointy, float jointz,
		float rotx, float roty, float rotz);

	// destructor
	~Node();

	// scenegraph has access to protected functions
	friend class SceneGraph;

	// increment / decrement Euler rotation
	void rotate(glm::ivec3 angles);

	// transform an individual node
	// according to its position, 
	// rotation, and rotation center
	glm::mat4 transform(Rotation::Mode rotationMode);

	// draw an individual node
	void draw(void);

	glm::mat4 getRotation(void);
	void setRotation(glm::mat4 r);

	// return parent / child / siblings
	Node* getNext();
	Node* getPrevious();
	Node* getParent();
	Node* getChild();

	// sets the parent of this node
	void setParent(Node* parent);

	// select / deselect node
	void select();
	void deselect();

	// reset rotation
	void reset();

	const Material material;

	const glm::vec3 dimension;  // length, height,
								// and width 
								// of this body part

protected:

	glm::vec3 position;   // x,y,z position of
						  // node center relative
						  // to parent node center

	glm::vec3 joint;      // x,y,z offset of 
				  // rotation axis
					  // from center of body part
						  // i.e. for rotation about
						  // a "shoulder" as opposed
						  // to the center of mass
			  // of a glutsolidcube

	const glm::ivec3 initialAngles;  // initial x,y,z rotation
  // (in degrees) of node relative
  // to parent node rotation

	glm::ivec3 eulerAngles; // x,y,z rotation (in degrees)
							// of node relative
							// to parent node rotation
							// as euler angles

	glm::mat4 rotationMatrix;    // rotation (in degrees)
							 // of node relative
								 // to parent node rotation
								 // accumulated in matrix


	// is node selected?
	bool selected;

	// siblings
	Node* next;
	Node* previous;
	// parent / child node
	Node* parent;
	Node* child;

	Mesh* mesh;
};
