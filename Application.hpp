#pragma once

/* ----------------------------------------------------------------
   name:           Application.hpp
   purpose:        cg1 base class for OpenGL applications
   version:	       LIBRARY CODE
   TODO:           nothing
   author:         katrin lang
				   computer graphics
				   htw berlin
   ------------------------------------------------------------- */

#include "glm/glm.hpp"
#include <vector>
#include <string>
   // for pair
#include <utility>

#include "Context.hpp"

template <class Application> class OpenGLContext;

class OpenGLApplication {

public:

	struct Keyboard {

		enum Key : unsigned char {
			BACKSPACE = 8,
			TAB = 9,
			ESC = 27,
			SPACE = 32,
			SPECIAL = 255
		} key;

		enum Code {
			LEFT,
			RIGHT,
			UP,
			DOWN
		} code;

		bool pressed;

		enum Modifier { SHIFT, CTRL, ALT };

		bool isActive(Modifier modifier);

		int modifiers;
	};

	struct Mouse {
		enum Button { LEFT, RIGHT };
		Button button;
		glm::ivec2 position;
		glm::ivec2 movement;
		bool pressed;
	};

	struct Config {

		glm::uvec2 version;
		enum Profile { CORE, COMPATIBILITY } profile;
		unsigned int flags;
		unsigned int samples;
		glm::uvec2 position;
		glm::uvec2 size;
		std::string title;

		Config(glm::uvec2 version, Profile profile, unsigned int flags, unsigned int samples, glm::uvec2 position, glm::uvec2 size, std::string title);
	};

	static const Config config;

	// initialization
	static void init();

	// called when redisplay was requested
	static void display(void);

	// called after window rehape
	static void reshape(void);

	// called when mouse pressed
	static void mousePressed(void);

	// called when mouse dragged
	static void mouseMoved(void);

	// called when mouse dragged
	static void mouseDragged(void);

	// called when mouse released
	static void mouseReleased(void);

	// called when menu item was selected                                                              
	static void menu(unsigned int id);

	// called when key pressed
	static void keyPressed(void);

	// called when key released
	static void keyReleased(void);

	// called when menu has input
	static void menu(int);

	static std::vector<std::pair< unsigned int, std::string> > menuEntries;

	static Window* window;

	static Mouse mouse;
	static Keyboard keyboard;
};
