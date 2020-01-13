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

SceneGraph::SceneGraph(Node* root)
	: root(root)
	, selected(root)
	, rotationMode(Rotation::MATRIX)
{
	root->select();

	colorizeShader.loadVertexShader("shaders/skeletal.vert");
	colorizeShader.compileVertexShader();
	colorizeShader.loadFragmentShader("shaders/skeletal.frag");
	colorizeShader.compileFragmentShader();
	colorizeShader.bindVertexAttribute("position", TriangleMesh::attribVertex);
	colorizeShader.link();
}

SceneGraph::~SceneGraph() {

	clear(root);
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

void SceneGraph::setShader(glsl::Shader* shader) {
	this->shader = shader;
}

// traverse and draw the scenegraph
// nothing to do here
// (see helper function)
void SceneGraph::traverse() {

	traverse(root, mat4(1));
}

// reset all rotations in the scenegraph
// nothing to do here
// (see helper function)
void SceneGraph::reset() {
	reset(root);
}

// navigation in tree
// (needed for node selection)
void SceneGraph::up() {

	if (selected->getParent() == NULL) return;
	selected->deselect();
	selected = selected->getParent();
	selected->select();
}

void SceneGraph::down() {

	if (selected->getChild() == NULL) return;
	selected->deselect();
	selected = selected->getChild();
	selected->select();
}

void SceneGraph::left() {

	if (selected->getPrevious() == NULL) return;
	selected->deselect();
	selected = selected->getPrevious();
	selected->select();
}

void SceneGraph::right() {

	if (selected->getNext() == NULL) return;
	selected->deselect();
	selected = selected->getNext();
	selected->select();
}

// setter and getter for rotation mode
void SceneGraph::setRotationMode(Rotation::Mode mode) {

	rotationMode = mode;
}

Rotation::Mode SceneGraph::getRotationMode(void) {

	return rotationMode;
}

// increment / decrement rotation of selected node
void SceneGraph::rotate(ivec3 angles) {

	selected->rotate(angles);
}


// traverse and draw the scenegraph from a given node
// XXX: NEEDS TO BE IMPLEMENTED
void SceneGraph::traverse(Node* node, mat4 modelMatrix) {

	if (node == NULL) return;

	// traverse possible siblings
	traverse(node->getNext(), modelMatrix);

	// apply local transformations
	modelMatrix *= node->transform(rotationMode);

	shader->bind();
	shader->setUniform("modelMatrix", modelMatrix * glm::scale(node->dimension));
	shader->setUniform("normalMatrix", mat3(inverse(transpose(modelMatrix * glm::scale(node->dimension)))));
	shader->setUniform("material.ambient", node == selected ? vec4(1, 0.15, 0.15, 1) : node->material.ambient);
	shader->setUniform("material.diffuse", node == selected ? vec4(1, 0.15, 0.15, 1) : node->material.diffuse);
	shader->setUniform("material.specular", node == selected ? vec4(1, 0.15, 0.15, 1) : node->material.specular);
	shader->setUniform("material.shininess", node->material.shininess);
	node->draw();
	shader->unbind();

	// continue concatenating transformations
	// if this node has children
	if (Node* child = node->getChild()) {
		traverse(child, modelMatrix);
	}
}

void SceneGraph::clear(Node* node) {

	if (node == NULL) return;
	clear(node->getNext());
	clear(node->getChild());
	delete node;
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
