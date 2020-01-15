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
#include "AnimatedMesh.h"
#include "AnimatedModelLoader.h"

   // nodes of the scenegraph

   // XXX: CURRENTLY ONLY TORSO. INSERT OTHER BODY PARTS HERE.
   //      SEE EXAMPLE BINARY cg1_ex1.exe (win32) and cg1_ex1 (linux).
   //      EXPERIMENTATION IS ENCOURAGED. THE FINAL MODEL/SCENEGRAPH
   //      NEED NOT BE IDENTICAL TO THE PROPOSED SOLUTION.

   // XXX: EXTEND THE SCENEGRAPH i.e.
   // Node *part1, *part2, *part3, etc...

   // build the robot scenegraph
Node* Robot::buildRobot() {

	AnimatedMesh* animatedMesh = AnimatedModelLoader::loadAnimatedMesh("meshes/model.dae", "");

	// mesh
	TriangleMesh* mesh = new TriangleMesh("meshes/cube.obj");

	Mesh* animatedMeshAsMesh = (Mesh*)animatedMesh;

	// material parameters
	Material material = { glm::vec4(0.5, 0.5, 0.5, 1.0),
						glm::vec4(0.5, 0.5, 0.5, 1.0),
						glm::vec4(0.5, 0.5, 0.5, 1.0),
						3.0f };

	Node* animatedModel = new Node(animatedMeshAsMesh, material, 0, -400, 0, 100, 100, 100, 0, 0, 0, -45, 0, 0);
	animatedModel->setCurrentJoint(animatedMesh->getRootJoint());
	
	return animatedModel;
}
