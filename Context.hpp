#pragma once

/* ----------------------------------------------------------------
   name:           Context.hpp
   purpose:        OpenGL loading, context creation and initialization
   version:	   LIBRARY CODE
   TODO:           nothing
   author:         katrin lang
   computer graphics
   htw berlin
   ------------------------------------------------------------- */

template <class Application> class OpenGLContext {

public:

	enum Profile { CORE, COMPATIBILITY };

	// intialization
	static void init(int argc, char** argv);
};

#include "Context.cpp"

