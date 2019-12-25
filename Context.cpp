/* ----------------------------------------------------------------
   name:           Context.cpp
   purpose:        OpenGL loading, context creation and initialization
   version:	   LIBRARY CODE
   TODO:           nothing
   author:         katrin lang
   computer graphics
   htw berlin
   ------------------------------------------------------------- */


#include "Context.hpp"
#include "GLIncludes.hpp"
//#define FREEGLUT_STATIC
#ifdef __APPLE__
#include <GL/freeglut.h>
#elif _WIN32
#include "GL\freeglut.h"
#else
#include "GL/freeglut.h"
#endif

#include "Window.hpp"

// use this with care
// might cause name collisions

using namespace std;

template <class Application> void OpenGLContext<Application>::init(int argc, char** argv){

  // create window with glut
  glutInit(&argc, argv);
  
  glutInitContextVersion(Application::config.version[0], Application::config.version[1]);
  
  glutInitContextProfile(Application::config.profile==Application::Config::CORE ? GLUT_CORE_PROFILE : GLUT_COMPATIBILITY_PROFILE);

#ifndef __APPLE__
  glutSetOption(GLUT_MULTISAMPLE, Application::config.samples);
#endif
  
  glutInitDisplayMode(Application::config.flags);
  
  Application::window= new Window(Application::config.title.c_str(), Application::config.position, Application::config.size);
  
  glewExperimental = GL_TRUE;
  
  if (glewInit() != GLEW_OK) {
    cerr << "Error init GLEW." << endl;
    exit( 0);
  }
  
  cout << "GPU: " << glGetString(GL_RENDERER) << ", OpenGL version: " << glGetString(GL_VERSION) << ", GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl; 
  
  Application::init();

}
