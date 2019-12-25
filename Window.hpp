/* ----------------------------------------------------------------
   name:           window.h
   purpose:        GLUT (sub-) window class declaration
   version:	   LIBRARY CODE
   TODO:           nothing (see window.cpp)
   author:         katrin lang
   computer graphics
   tu berlin
   ------------------------------------------------------------- */

#pragma once

#include <iostream>
#include "glm/glm.hpp"

class Window{

public:
  
  // constructors
  Window(std::string title, glm::uvec2 position, glm::uvec2 size);
  Window(Window &parent, std::string title, glm::uvec2 position, glm::uvec2 size);

  // flags
  static const unsigned int RGBA, RGB, DOUBLE, DEPTH, MULTISAMPLE;
  
  // make window current
  void makeCurrent(void);
  // is current?
  bool isCurrent(void) const;

  void redisplay(void);
  void swapBuffers(void);
  
  std::string getTitle(void) const;

  // get size
  glm::uvec2 size() const;
  // get width
  unsigned int width() const;
  // get height
  unsigned int height() const;

  // reshape window
  void reshape(int width, int height);
  // reposition window
  void reposition(int x, int y);

private:
  
  // window id returned from glut
  unsigned int id;
  // window title 
  std::string title;
};
