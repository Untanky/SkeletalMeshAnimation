#pragma once

/* ----------------------------------------------------------------
   name:           SceneGraph.hpp
   purpose:        scenegraph class declaration
   version:	   SKELETON CODE
   TODO:           nothing (see SceneGraph.cpp)
   author:         katrin lang
				   computer graphics
				   htw berlin
   ------------------------------------------------------------- */

#include "Node.hpp"
#include "GLSL.hpp"

class SceneGraph {

public:

	SceneGraph(Node* root);

	~SceneGraph();

	// traverse and draw the scenegraph
	void traverse();

	// navigation in tree
	// (needed for node selection)
	void up();
	void down();
	void left();
	void right();

	void setViewMatrix(glm::mat4 viewMatrix);
	void setProjectionMatrix(glm::mat4 projectionMatrix);

	void setShader(glsl::Shader* shader);

	// setter and getter for rotation mode
	void setRotationMode(Rotation::Mode mode);

	Rotation::Mode getRotationMode(void);

	// increment / decrement rotation of selected node
	void rotate(glm::ivec3 angles);

	// reset all rotations
	void reset();

	glsl::Shader* shader;

protected:

	// traverse and draw the scenegraph from a given node
	void traverse(Node* node, glm::mat4 modelMatrix);

	// reset all rotations below given node
	void reset(Node* node);

	// destroy all nodes
	void clear(Node* node);

	// root node
	Node* root;

	// currently selected node
	Node* selected;

	// rotation mode (extra assignment)
	Rotation::Mode rotationMode;

	glsl::Shader colorizeShader;

	glm::mat4 viewMatrix, projectionMatrix;
};
