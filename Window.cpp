/* ----------------------------------------------------------------
   name:           Window.cpp
   purpose:        GLUT (sub-) window implementation
   version:	   LIBRARY CODE
   TODO:           nothing
   author:         katrin lang
		   computer graphics
		   tu berlin
   ------------------------------------------------------------- */

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

using namespace std;
using namespace glm;

const unsigned int Window::RGBA = GLUT_RGBA, Window::RGB = GLUT_RGB, Window::DOUBLE = GLUT_DOUBLE, Window::DEPTH = GLUT_DEPTH, Window::MULTISAMPLE = GLUT_MULTISAMPLE;

// main window
Window::Window(string title, uvec2 position, uvec2 size) :

	title(title) {

	glutInitWindowPosition(position.x, position.y);
	glutInitWindowSize(size.x, size.y);
	id = glutCreateWindow(title.c_str());
}

Window::Window(Window& parent, string title, uvec2 position, uvec2 size) :

	title(title) {

	id = glutCreateSubWindow(parent.id, position.x, position.y, size.x, size.y);
}

// get width
unsigned int Window::width() const {

	return glutGet(GLUT_WINDOW_WIDTH);
}

// get height
unsigned int Window::height() const {

	return glutGet(GLUT_WINDOW_HEIGHT);
}

// get size
uvec2 Window::size() const {

	return vec2(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
}

// make window current
void Window::makeCurrent(void) {

	glutSetWindow(id);
}

// is current?
bool Window::isCurrent(void) const {

	return glutGetWindow() == (int)id;
}

string Window::getTitle(void) const {
	return title;
}

void Window::redisplay(void) {
	glutPostRedisplay();
}

void Window::swapBuffers(void) {
	glutSwapBuffers();
}

// reshape window
void Window::reshape(int width, int height) {

	glutReshapeWindow(width, height);
	redisplay();
}

// reposition window
void Window::reposition(int x, int y) {

	glutPositionWindow(x, y);
}
