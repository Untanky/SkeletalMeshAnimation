/* ----------------------------------------------------------------
   name:           Scenegraph.cpp
   purpose:        implementation of the scenegraph functions
   version:	   SKELETON CODE
   TODO:           traverse reset
   author:         katrin lang
				   computer graphics
				   htw berlin
   ------------------------------------------------------------- */

#include "GLIncludes.hpp"

#include <iostream>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/vector_angle.hpp"
#include "glm/gtx/string_cast.hpp"

#define DEBUG // (enable/disable logging)
#include "Log.hpp"
#include "SceneGraph.hpp"
#include "TriangleMesh.hpp"

   // use this with care
   // might cause name collisions
using namespace std;
using namespace glm;

SceneGraph::SceneGraph(AnimatedMesh* mesh)
	: mesh(mesh),
	currentJoint(mesh->getRootJoint()),
	rotationMode(Rotation::MATRIX)
{

	colorizeShader.loadVertexShader("shaders/color.vert");
	colorizeShader.compileVertexShader();
	colorizeShader.loadFragmentShader("shaders/color.frag");
	colorizeShader.compileFragmentShader();
	colorizeShader.bindVertexAttribute("position", TriangleMesh::attribVertex);
	colorizeShader.link();
}

SceneGraph::~SceneGraph() {

	delete mesh;
}

void SceneGraph::setViewMatrix(glm::mat4 viewMatrix) {

	this->viewMatrix = viewMatrix;

	shader->bind();
	shader->setUniform("viewMatrix", viewMatrix);
	shader->unbind();

	colorizeShader.bind();
	colorizeShader.setUniform("viewMatrix", viewMatrix);
	colorizeShader.unbind();
}

void SceneGraph::setProjectionMatrix(glm::mat4 projectionMatrix) {

	this->projectionMatrix = projectionMatrix;

	shader->bind();
	shader->setUniform("projectionMatrix", projectionMatrix);
	shader->bind();

	colorizeShader.bind();
	colorizeShader.setUniform("projectionMatrix", projectionMatrix);
	colorizeShader.bind();
}

void SceneGraph::setBoneMatrix(glm::mat4* boneMatrix) {


	shader->bind(); 
	shader->setUniform("jointTransforms", boneMatrix);
	shader->bind();
}

void SceneGraph::setShader(glsl::Shader* shader) {
	this->shader = shader;
}

// traverse and draw the scenegraph
// nothing to do here
// (see helper function)
void SceneGraph::traverse() {

	traverse(mat4(1));
}

// reset all rotations in the scenegraph
// nothing to do here
// (see helper function)
void SceneGraph::reset() {
	mesh->getRootJoint()->reset();
}

// navigation in tree
// (needed for node selection)
void SceneGraph::up() {

	if (Joint* parent = getCurrentJoint()->getParent()) {
		currentJoint = parent;
	}
}

void SceneGraph::down() {

	if (Joint* child = getCurrentJoint()->getChild()) {
		currentJoint = child;
	}
}

void SceneGraph::left() {

	if (Joint * previousSibling = getCurrentJoint()->getPrevious()) {
		currentJoint = previousSibling;
	}
}

void SceneGraph::right() {

	if (Joint * nextSibling = getCurrentJoint()->getNext()) {
		currentJoint = nextSibling;
	}
}

// setter and getter for rotation mode
void SceneGraph::setRotationMode(Rotation::Mode mode) {

	rotationMode = mode;
}

Rotation::Mode SceneGraph::getRotationMode(void) {

	return rotationMode;
}

Joint* SceneGraph::getCurrentJoint() const {

	return this->currentJoint;
}

// increment / decrement translation of selected node
void SceneGraph::translate(vec3 translation) {

	if (Joint* currentJoint = getCurrentJoint()) {
		currentJoint->translate(translation);
	}
}

// increment / decrement rotation of selected node
void SceneGraph::rotate(ivec3 angles) {

	if (Joint* currentJoint = getCurrentJoint()) {
		currentJoint->rotate(vec3(angles));
	}
}

// traverse and draw the scenegraph from a given node
// XXX: NEEDS TO BE IMPLEMENTED
void SceneGraph::traverse(mat4 modelMatrix) {
	
	std::vector<glm::mat4> jointTransforms = mesh->getJointTransforms();
	glm::mat4 boneMatrix[50];

	for (int i = 0; i < 50; i++)
	{
		if (i < jointTransforms.size())
			boneMatrix[i] = jointTransforms[i];
		else
			boneMatrix[i] = mat4(1);
	}

	setBoneMatrix(boneMatrix);

	// apply local transformations
	modelMatrix = glm::translate(modelMatrix, vec3(0, -400, 0));
	//modelMatrix = glm::rotate(modelMatrix, radians(-45.0f), vec3(1, 0, 0));
	modelMatrix = scale(modelMatrix, vec3(100, 100, 100));
	// TODO: modelMatrix *= transform;


	// material parameters
	Material material = { vec4(1, 0.15, 0.15, 1),
						vec4(1, 0.15, 0.15, 1),
						vec4(1, 0.15, 0.15, 1),
						3.0f };

	shader->bind();
	shader->setUniform("modelMatrix", modelMatrix);
	shader->setUniform("normalMatrix", mat3(inverse(transpose(modelMatrix))));
	shader->setUniform("material.ambient", material.ambient);
	shader->setUniform("material.diffuse", material.diffuse);
	shader->setUniform("material.specular", material.specular);
	shader->setUniform("material.shininess", material.shininess );
	mesh->draw();
	shader->unbind();
}

// reset the subtree corresponding 
// to a given node
// XXX: NEEDS TO BE IMPLEMENTED
void SceneGraph::reset(Node* node) {

	// XXX

	node->reset();

	if (Node* next = node->getChild())
		reset(next);

	if (Node* child = node->getChild())
		reset(child);

	// END XXX
}
