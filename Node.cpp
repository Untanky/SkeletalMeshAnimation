/* ----------------------------------------------------------------
   name:           Node.cpp
   purpose:        implementation for a scenegraph node
   version:	   SKELETON CODE
   TODO:           transform
   author:         katrin lang
				   computer graphics
				   htw berlin
   ------------------------------------------------------------- */

#include <iostream>

#include "GLIncludes.hpp"

#include "Node.hpp"
#include "Debug.hpp"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/vector_angle.hpp"
#include "glm/gtx/string_cast.hpp"

   // use this with care
   // might cause name collisions
using namespace glm;
using namespace std;


// constructor
// x,y,z: position of node center of mass relative to parent node center
// length, height, and width of this body part
// jointx, jointy, jointz: x,y,z offset of  rotation axis from center of body part
// i.e. for rotation about a "shoulder" as opposed to the center of mass of a cube
// x,y,z: rotation (in degrees) of node relative to parent node rotation
// radius: radius of virtual trackball
Node::Node(Mesh* mesh,
	Material material,
	float x, float y, float z,
	float length, float height, float width,
	float jointx, float jointy, float jointz,
	float rotx, float roty, float rotz)

	: selected(false)
	, position(vec3(x, y, z))
	, dimension(vec3(length, height, width))
	, joint(vec3(jointx, jointy, jointz))
	, initialAngles(vec3(rotx, roty, rotz))
	, eulerAngles(initialAngles)
	, rotationMatrix(mat4(1))
	, parent(NULL)
	, child(NULL)
	, previous(NULL)
	, next(NULL)
	, mesh(mesh)
	, material(material)
{
	reset();
}

// destructor
// nothing to do so far
Node::~Node() {}

// sets the parent of this node
// and adds this node 
// to the list of the parent's children
void Node::setParent(Node* parent) {

	this->parent = parent;
	if (parent->child == NULL) {
		parent->child = this;
	}
	else {
		Node* sibling = parent->child;
		while (sibling->next != NULL) sibling = sibling->next;
		sibling->next = this;
		this->previous = sibling;
	}
}

glm::mat4 Node::getRotation(void) {
	return rotationMatrix;
}

void Node::setRotation(glm::mat4 r) {
	rotationMatrix = r;
}


// increment / decrement rotation
void Node::rotate(ivec3 angles) {

	eulerAngles += angles;

	rotationMatrix *= glm::rotate(radians((float)angles.x), vec3(1.0, 0.0, 0.0));
	rotationMatrix *= glm::rotate(radians((float)angles.y), vec3(0.0, 1.0, 0.0));
	rotationMatrix *= glm::rotate(radians((float)angles.z), vec3(0.0, 0.0, 1.0));
}

// TODO: transform an individual node
// according to its position, 
// rotation, and rotation center
// XXX: NEEDS TO BE IMPLEMENTED
glm::mat4 Node::transform(Rotation::Mode rotationMode) {

	// note the order of the operations:
	// the transformations are applied in "reverse" order
	// of rotate/translate calls
	// (also see cg1 lecture notes on this topic)

	mat4 transformation(1);

	// translate to final position
	transformation *= translate(this->position);

	// translate node center to joint position
	transformation *= translate(this->joint);


	if (rotationMode == Rotation::EULER) {

		// apply this node's rotation, use Euler angles
		transformation *= glm::rotate(radians((float)eulerAngles.x), vec3(1, 0, 0));
		transformation *= glm::rotate(radians((float)eulerAngles.y), vec3(0, 1, 0));
		transformation *= glm::rotate(radians((float)eulerAngles.z), vec3(0, 0, 1));
	}
	else {

		// apply this node's rotation, use rotation matrix
		transformation *= rotationMatrix;
	}


	// translate center of rotation into limb's origin
	// XXX

	transformation *= translate(-this->joint);

	// END XXX

	return transformation;
}

// draw an individual node
void Node::draw(void) {

	mesh->draw();
}

// getter for next pointer
Node* Node::getNext() {
	return next;
}

// getter for previous pointer
Node* Node::getPrevious() {
	return previous;
}

// getter for parent pointer
Node* Node::getParent() {
	return parent;
}

// getter for child pointer
Node* Node::getChild() {
	return child;
}

// select node
void Node::select() {
	selected = true;
}

// deselect node
void Node::deselect() {
	selected = false;
}

// (re)sets an individual node
// to the initial rotation 
// specified in constructor
void Node::reset() {

	eulerAngles = initialAngles;

	rotationMatrix = mat4(1);
	rotationMatrix *= glm::rotate(radians((float)initialAngles.x), vec3(1, 0, 0));
	rotationMatrix *= glm::rotate(radians((float)initialAngles.y), vec3(0, 1, 0));
	rotationMatrix *= glm::rotate(radians((float)initialAngles.z), vec3(0, 0, 1));
}
