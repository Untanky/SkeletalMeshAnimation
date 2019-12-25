/* ----------------------------------------------------------------
   name:           InputManager.cpp
   purpose:        input handling, glut callbacks
   version:	   LIBRARY CODE
   TODO:           nothing
   author:         katrin lang
   computer graphics
   htw berlin
   ------------------------------------------------------------- */

#include <string>

#include <vector>
// for pair
#include <utility>

#include "GLIncludes.hpp"
//#define FREEGLUT_STATIC
#ifdef __APPLE__
#include <GL/freeglut.h>
#elif _WIN32
#include "GL\freeglut.h"
#else
#include "GL/freeglut.h"
#endif

#include "InputManager.hpp"

// use this with care
// might cause name collisions

using namespace std;
using namespace glm;

template <class Application> void InputManager<Application>::startEventLoop(void){

  glutDisplayFunc(Application::display); 
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyPressed);
  glutKeyboardUpFunc(keyReleased);	
  glutSpecialFunc(specialKeyPressed);
  glutSpecialUpFunc(specialKeyReleased);
  glutMouseFunc(mouseButton);
  glutPassiveMotionFunc(mouseMoved);
  glutMotionFunc(mouseDragged);

  if(!Application::menuEntries.empty())
    glutCreateMenu(Application::menu);
  for(unsigned int i= 0; i<Application::menuEntries.size(); i++) glutAddMenuEntry(Application::menuEntries[i].second.c_str(), Application::menuEntries[i].first);
  glutAttachMenu(GLUT_RIGHT_BUTTON);

  glutMainLoop();
}

template <class Application> void InputManager<Application>::reshape(int width, int height){
  Application::reshape();
}
  
// mouse pressed callback
template <class Application> void InputManager<Application>::mouseButton(int button, int state, int x, int y){
  
  retrieveModifiers();
  
  if (state == GLUT_UP){
    
    Application::mouse.movement= ivec2(x, y)-Application::mouse.position;
    Application::mouse.position = ivec2(x, y);	
    Application::mouseReleased();
  }
  else if (state == GLUT_DOWN){

    Application::mouse.movement= ivec2(0);
    Application::mouse.position = ivec2(x, y);	

    Application::mouse.button= button == GLUT_LEFT ? Application::Mouse::LEFT : Application::Mouse::RIGHT;
    
    Application::mousePressed();
  }
}

template <class Application> void InputManager<Application>::mouseMoved(int x, int y){

  if(x == Application::mouse.position.x && y == Application::mouse.position.y) return;
  Application::mouse.movement = ivec2(x, y) - Application::mouse.position;
  Application::mouse.position = ivec2(x, y);	
  retrieveModifiers();
  Application::mouseMoved();
}

template <class Application> void InputManager<Application>::mouseDragged(int x, int y){

  if (x == Application::mouse.position.x && y == Application::mouse.position.y) return;
  Application::mouse.movement = ivec2(x, y) - Application::mouse.position;
  Application::mouse.position = ivec2(x, y);
 
  retrieveModifiers();
  Application::mouseDragged();
}

template <class Application> void InputManager<Application>::keyPressed(unsigned char key, int x, int y){

  retrieveModifiers();

  Application::keyboard.pressed= true;
  Application::keyboard.key= static_cast<typename Application::Keyboard::Key>(key);

  Application::mouse.position= ivec2(x, y);

  Application::keyPressed();
}

template <class Application> void InputManager<Application>::retrieveModifiers(){

  Application::keyboard.modifiers= glutGetModifiers();
}

template <class Application> void InputManager<Application>::specialKeyPressed(int key, int x, int y){
  
  retrieveModifiers();
  
  Application::keyboard.pressed= true;
  Application::keyboard.key= Application::Keyboard::Key::SPECIAL;

  switch (key) {
      
  case GLUT_KEY_UP:
    Application::keyboard.code= Application::Keyboard::Code::UP;
    break;
  case GLUT_KEY_DOWN:
    Application::keyboard.code= Application::Keyboard::Code::DOWN;
    break;
  case GLUT_KEY_LEFT:
    Application::keyboard.code= Application::Keyboard::Code::LEFT;
    break;
  case GLUT_KEY_RIGHT:
    Application::keyboard.code= Application::Keyboard::Code::RIGHT;	
    break;
  default:
    return;
    break;
  }

  Application::mouse.position = ivec2(x, y);	
  
  Application::keyPressed();
}

template <class Application> void InputManager<Application>::keyReleased(unsigned char key, int x, int y){

  Application::keyboard.pressed= false;
  Application::keyboard.key= static_cast<typename Application::Keyboard::Key>(key);
  
  Application::mouse.position = ivec2(x, y);	
  
  Application::keyReleased();
}

template <class Application> void InputManager<Application>::specialKeyReleased(int key, int x, int y) {

  Application::keyboard.pressed = false;
  Application::keyboard.key= Application::Keyboard::Key::SPECIAL;

  switch (key) {
    
  case GLUT_KEY_UP:
    Application::keyboard.code= Application::Keyboard::Code::UP;
    break;
  case GLUT_KEY_DOWN:
    Application::keyboard.code = Application::Keyboard::Code::DOWN;
    break;
  case GLUT_KEY_LEFT:
    Application::keyboard.code = Application::Keyboard::Code::LEFT;
    break;
  case GLUT_KEY_RIGHT:
    Application::keyboard.code = Application::Keyboard::Code::RIGHT;
    break;
  default: break;
  }
  
  Application::mouse.position= ivec2(x, y);
  
  Application::keyReleased();
}
