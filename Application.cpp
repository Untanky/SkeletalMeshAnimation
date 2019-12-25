#include "Application.hpp"

#include "GLIncludes.hpp"
//#define FREEGLUT_STATIC
#ifdef __APPLE__
#include <GL/freeglut.h>
#elif _WIN32
#include "GL\freeglut.h"
#else
#include "GL/freeglut.h"
#endif

Window * OpenGLApplication::window= NULL;

OpenGLApplication::Mouse OpenGLApplication::mouse;
OpenGLApplication::Keyboard OpenGLApplication::keyboard;

bool OpenGLApplication::Keyboard::isActive(Keyboard::Modifier modifier){
  
  switch(modifier){
  case ALT:
    return modifiers & GLUT_ACTIVE_ALT;
	break;
  case CTRL:
    return modifiers & GLUT_ACTIVE_CTRL;
	break;
  case SHIFT:
    return modifiers & GLUT_ACTIVE_SHIFT;
	break;
  default: 
	break;
  }
  return false;
}

OpenGLApplication::Config::Config(glm::uvec2 version, enum Config::Profile profile, unsigned int flags, unsigned int samples, glm::uvec2 position, glm::uvec2 size, std::string title)
  : version(version), profile(profile), flags(flags), samples(samples), position(position), size(size), title(title){}

const OpenGLApplication::Config OpenGLApplication::config(glm::uvec2(2, 1),
	Config::Profile::COMPATIBILITY,
	(Window::DOUBLE | Window::DEPTH | Window::RGB | Window::MULTISAMPLE),
			8,	
							  glm::uvec2(50,50),
							  glm::uvec2(600, 600),
							  "");

std::vector< std::pair<unsigned int, std::string> > OpenGLApplication::menuEntries;

void OpenGLApplication::init(){}
void OpenGLApplication::display(void){}
void OpenGLApplication::reshape(void){}
void OpenGLApplication::mousePressed(void){}
void OpenGLApplication::mouseMoved(void){}
void OpenGLApplication::mouseDragged(void){}
void OpenGLApplication::mouseReleased(void){}
void OpenGLApplication::keyPressed(void){}
void OpenGLApplication::keyReleased(void){}
void OpenGLApplication::menu(int){}
