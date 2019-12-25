#pragma once

/* ----------------------------------------------------------------
   name:           InputManager
   purpose:        input handling, glut callbacks
   version:	   LIBRARY CODE
   TODO:           nothing
   author:         katrin lang
   computer graphics
   htw berlin
   ------------------------------------------------------------- */

/* --------------------------------------------------------------- 
   implemented glut callbacks:
   display            - display scene (from Application)
   reshape            - reshape window (from Application)
   menu               - right mouse button menu (from Application)
   mouseButton        - mouse pressed / released
   mouseMoved         - mouse moved
   mouseDragged       - mouse moved while mouse button pressed
   keyPressed         - keyboard callback
   idle               - called each frame without input (from Application)
   timer              - called when timer expires (from Application)
   ---------------------------------------------------------------- */

#include <string>

#include <iostream> 

#include <vector>
// for pair
#include <utility>

#define GLM_SWIZZLE 
#include "glm/glm.hpp"

using namespace std;

template <class Application> class InputManager{

public:

  static void startEventLoop(void);

private:

  // reshape callback
  static void reshape(int width, int height);
  
  // mouse callbacks
  static void mouseButton(int button, int state, int x, int y);
  static void mouseMoved(int x, int y);
  static void mouseDragged(int x, int y);

  // keyboard callbacks
  static void keyPressed(unsigned char key, int x, int y);
  static void keyReleased(unsigned char key, int x, int y);
  static void specialKeyPressed(int key, int x, int y);
  static void specialKeyReleased(int key, int x, int y);

  static void retrieveModifiers(void);
};

#include "InputManager.cpp"

