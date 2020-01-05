#pragma once

/* ----------------------------------------------------------------
   name:           Control.hpp
   purpose:        robot control
   version:	   SKELETON CODE
   TODO:           nothing (see Control.cpp)
   author:         katrin lang
				   computer graphics
				   htw berlin
   ------------------------------------------------------------- */

#include <vector>
   // for pair
#include <utility>

#include "glm/glm.hpp"

using namespace glm;

#include "SceneGraph.hpp"
#include "Application.hpp"
#include "shaders/LightSource.h"

class Control : public OpenGLApplication {

public:

	// initialization
	static void init();

	// add a scenegraph
	static void addSceneGraph(SceneGraph* sceneGraph);

	// display scene
	static void display(void);

	// called after window rehape
	static void reshape(void);

	// called when mouse pressed
	static void mousePressed(void);

	// called when mouse dragged
	static void mouseDragged(void);

	static std::vector<std::pair< unsigned int, std::string> > menuEntries;

	// called when menu item was selected                                                              
	static void menu(int id);

	// keyboard callback
	static void keyPressed(void);

private:

	static void updateViewMatrix(void);
	static void updateProjectionMatrix(void);

	static void drawParameters(void);

	static LightSource lightSource;

	static glsl::Shader diffuseShader;

	// the scenegraph
	static SceneGraph* sceneGraph;

	// field of view (in degrees)                                               
	static unsigned int fov;

	static float pan;

	// camera position                                                           
	static float cameraZ;

	// near and far plane                                                        
	static float nearPlane, farPlane;

	struct Menu {
		enum Item { QUIT, EULER, MATRIX, RESET, RESET_CAMERA };
	};
};
