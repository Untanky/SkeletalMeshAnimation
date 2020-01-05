/* ----------------------------------------------------------------
   name:           Robot.cpp
   purpose:        implementation of the scenegraph construction
   version:	   SKELETON CODE
   TODO:           buildRobot
   author:         katrin lang
				   computer graphics
				   htw berlin
   ------------------------------------------------------------- */

#include "Robot.hpp"
#include "TriangleMesh.hpp"

   // nodes of the scenegraph

   // XXX: CURRENTLY ONLY TORSO. INSERT OTHER BODY PARTS HERE.
   //      SEE EXAMPLE BINARY cg1_ex1.exe (win32) and cg1_ex1 (linux).
   //      EXPERIMENTATION IS ENCOURAGED. THE FINAL MODEL/SCENEGRAPH
   //      NEED NOT BE IDENTICAL TO THE PROPOSED SOLUTION.

   // XXX: EXTEND THE SCENEGRAPH i.e.
   // Node *part1, *part2, *part3, etc...

   // build the robot scenegraph
Node* Robot::buildRobot() {

	// mesh
	TriangleMesh* mesh = new TriangleMesh("meshes/cube.obj");

	// material parameters
	Material material = { glm::vec4(0.5, 0.5, 0.5, 1.0),
						glm::vec4(0.5, 0.5, 0.5, 1.0),
						glm::vec4(0.5, 0.5, 0.5, 1.0),
						3.0f };

	// torso attributes and initial position.
	// for parameters of constructor and their meanings,
	// see file node.h
	Node* torso = new Node(mesh, material,
		0, 50, 0,
		200, 300, 100,
		0, 0, 0,
		0, 0, 0);

	Node* leftArm = new Node(mesh, material,
		150, 50, 0,
		40, 200, 40,
		0, 100, 0,
		0, 0, 0);

	leftArm->setParent(torso);

	Node* leftForeArm = new Node(mesh, material,
		0, -250, 0,
		40, 200, 40,
		0, 150, 0,
		0, 0, 0);

	leftForeArm->setParent(leftArm);

	Node* rightArm = new Node(mesh, material,
		-150, 50, 0,
		40, 200, 40,
		0, 100, 0,
		0, 0, 0);

	rightArm->setParent(torso);

	Node* rightForeArm = new Node(mesh, material,
		0, -250, 0,
		40, 200, 40,
		0, 150, 0,
		0, 0, 0);

	rightForeArm->setParent(rightArm);

	Node* leftLeg = new Node(mesh, material,
		70, -375, 0,
		80, 300, 80,
		0, 150, 0,
		0, 0, 0);

	leftLeg->setParent(torso);

	Node* rightLeg = new Node(mesh, material,
		-70, -375, 0,
		80, 300, 80,
		0, 150, 0,
		0, 0, 0);

	rightLeg->setParent(torso);

	Node* head = new Node(mesh, material,
		0, 250, 0,
		100, 100, 100,
		0, 100, 0,
		0, 0, 0);

	head->setParent(torso);

	// XXX: implement more body/robot/whatever parts here

	// INSERT YOUR CODE HERE



	// finally, attach the robot/model parts
	// example: leftArm->setParent(torso), etc...
	// BUILD THE SCENEGRAPH

	// XXX: attach other body parts here

	// INSERT YOUR CODE HERE

	// END XXX

	// return root node
	return torso;
}
