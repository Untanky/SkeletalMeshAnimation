/* ----------------------------------------------------------------
   name:           Control.cpp
   purpose:        robot control
   version:	   SKELETON CODE
   TODO:           init, menu, keyPressed, updateProjectionMatrix, updateViewMatrix
   author:         katrin lang
				   computer graphics
				   htw berlin
   ------------------------------------------------------------- */

#include "GLIncludes.hpp"

#include <iostream>
#include <sstream>
#include <iomanip>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/vector_angle.hpp"
#include "glm/gtx/string_cast.hpp"

   // use this with care
   // might cause name collisions
using namespace glm;
using namespace std;

#include "Control.hpp"
#include "Context.hpp"
#include "InputManager.hpp"
#include "Robot.hpp"

// field of view
unsigned int Control::fov = 40;
// camera position
float Control::cameraZ = 1500;
// camera pan
float Control::pan = 0;
// near and far plane
float Control::nearPlane;
float Control::farPlane;
// shader
glsl::Shader Control::diffuseShader;

// light parameters
LightSource Control::lightSource = { vec4(-1000.0, 1000.0, 1000.0, 1.0),
				   vec4(1.0f, 1.0f, 1.0f, 1.0f),
				   vec4(1.0f, 1.0f, 1.0f, 1.0f),
				   vec4(1.0f, 1.0f, 1.0f, 1.0f) };

SceneGraph* Control::sceneGraph = NULL;

std::vector<std::pair< unsigned int, std::string> >Control::menuEntries = { {Menu::QUIT, "quit"},
									 {Menu::RESET, "reset"},
									 {Menu::RESET_CAMERA, "reset camera"},
									 {Menu::EULER, "euler rotation"},
									 {Menu::MATRIX, "matrix rotation"}
};

void Control::init() {

	const std::string version = "#version 120\n";

	diffuseShader.addVertexShader(version);
	diffuseShader.loadVertexShader("shaders/Material.h");
	diffuseShader.loadVertexShader("shaders/LightSource.h");
	diffuseShader.loadVertexShader("shaders/diffuse.vert");
	diffuseShader.compileVertexShader();
	diffuseShader.addFragmentShader(version);
	diffuseShader.loadFragmentShader("shaders/diffuse.frag");
	diffuseShader.compileFragmentShader();
	diffuseShader.bindVertexAttribute("position", TriangleMesh::attribVertex);
	diffuseShader.bindVertexAttribute("normal", TriangleMesh::attribNormal);
	diffuseShader.link();
	diffuseShader.bind();
	diffuseShader.setUniform("lightSource.position", lightSource.position);
	diffuseShader.setUniform("lightSource.ambient", lightSource.ambient);
	diffuseShader.setUniform("lightSource.diffuse", lightSource.diffuse);
	diffuseShader.setUniform("lightSource.specular", lightSource.specular);
	diffuseShader.bind();

	// set background color to black
	glClearColor(0.0, 0.0, 0.0, 1.0);

	// enable depth test (z-buffer)
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);

	glClearColor(0, 0, 0, 1);

	// enable normalization of vertex normals
	glEnable(GL_NORMALIZE);

	// some output to console
	cout << "--------------------------------------------\n";
	cout << " cg1_ex1 opengl robot scenegraph            \n";
	cout << "                                            \n";
	cout << " keyboard:                                  \n";
	cout << " arrow keys: select node                    \n";
	cout << " x/X,y/Y,z/Z: rotate node                   \n";
	cout << " r: reset all rotations                     \n";
	cout << " q/Q: quit program                          \n";
	cout << "                                            \n";
	cout << " mouse:                                     \n";
	cout << " right click: config menu                   \n";
	cout << "--------------------------------------------\n";
}

// add a scenegraph
void Control::addSceneGraph(SceneGraph* sceneGraph) {

	Control::sceneGraph = sceneGraph;
	sceneGraph->setShader(&diffuseShader);
}

// adjust to new window size
void Control::reshape(void) {

	// viewport
	glViewport(0, 0, (GLsizei)window->width(), (GLsizei)window->height());

	updateProjectionMatrix();
	updateViewMatrix();
}

// update projection matrix when viewport changes
// TODO: replace glm::frustum() call with glm::perspective()
void Control::updateProjectionMatrix(void) {

	// window aspect ratio
	float aspect = (float)window->width() / (float)window->height();

	float nearPlane = cameraZ / 10.0f;
	float farPlane = cameraZ * 10.0f;

	// XXX: reset rotations

	// INSERT YOUR CODE HERE

	// perspective projection
	glm::mat4 projectionMatrix = glm::perspective(glm::radians((float)fov), aspect, nearPlane, farPlane);

	sceneGraph->setProjectionMatrix(projectionMatrix);
}

// TODO: pan
void Control::updateViewMatrix(void) {
	// position the camera at (0,0,cameraZ) looking down the
	// negative z-axis at (0,0,0) initially
	vec4 lookat(0, 0, 0, 1);

	mat4 matrix(1);

	matrix *= glm::translate(glm::vec3(0, 0, cameraZ));
	matrix *= glm::rotate(radians(pan), vec3(0, 1, 0));
	matrix *= glm::translate(glm::vec3(0, 0, -cameraZ));

	lookat = matrix * lookat;

	glm::mat4 viewMatrix = glm::lookAt(vec3(0, 0, cameraZ), vec3(lookat), vec3(0, 1, 0));
	sceneGraph->setViewMatrix(viewMatrix);
}

// this is where the drawing happens
void Control::display(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// draw the scenegraph
	sceneGraph->traverse();

	drawParameters();

	// display back buffer
	window->swapBuffers();
}

// keyboard control
void Control::keyPressed() {

	// rotation units
	float step = 2.0;

	// rotate selected node around 
	// x,y and z axes with keypresses
	switch (keyboard.key) {
	case 'q':
	case 'Q': exit(0);
	case 'x':
		sceneGraph->rotate(vec3(step, 0, 0));
		window->redisplay();
		break;
	case 'X':
		sceneGraph->rotate(vec3(-step, 0, 0));
		window->redisplay();
		break;
	case 'y':
		sceneGraph->rotate(vec3(0, step, 0));
		window->redisplay();
		break;
	case 'Y':
		sceneGraph->rotate(vec3(0, -step, 0));
		window->redisplay();
		break;
	case 'z':
		sceneGraph->rotate(vec3(0, 0, step));
		window->redisplay();
		break;
	case 'Z':
		sceneGraph->rotate(vec3(0, 0, -step));
		window->redisplay();
		break;

	case 'r':
		sceneGraph->reset();
		window->redisplay();
		break;

#define FOV_MIN_LIMIT 1
#define FOV_MAX_LIMIT 179

	case 'f':
		if (fov == FOV_MIN_LIMIT)
			break;
		fov -= 1;
		updateProjectionMatrix();
		window->redisplay();
		break;
	case 'F':
		if (fov == FOV_MAX_LIMIT)
			break;
		fov += 1;
		updateProjectionMatrix();
		window->redisplay();
		break;

#define PAN_MIN_LIMIT 0
#define PAN_MAX_LIMIT 360

	case 'p':
		if (pan <= PAN_MIN_LIMIT)
			pan = 360;
		pan -= 1;
		updateViewMatrix();
		window->redisplay();
		break;
	case 'P':
		if (pan >= PAN_MAX_LIMIT)
			pan = 0;
		pan += 1;
		updateViewMatrix();
		window->redisplay();
		break;

	case 'd':
		cameraZ -= 10;
		updateProjectionMatrix();
		updateViewMatrix();
		window->redisplay();
		break;
	case 'D':
		cameraZ += 10;
		updateProjectionMatrix();
		updateViewMatrix();
		window->redisplay();
		break;

	case 'c':
		pan = 0;
		fov = 40;
		cameraZ = 1500;
		updateProjectionMatrix();
		updateViewMatrix();
		window->redisplay();
		break;

	case Keyboard::Key::SPECIAL:

		// rotate selected node around 
		// x,y and z axes
		switch (keyboard.code) {

		case Keyboard::Code::UP:
			sceneGraph->up();
			window->redisplay();
			break;
		case Keyboard::Code::DOWN:
			sceneGraph->down();
			window->redisplay();
			break;
		case Keyboard::Code::LEFT:
			sceneGraph->left();
			window->redisplay();
			break;
		case Keyboard::Code::RIGHT:
			sceneGraph->right();
			window->redisplay();
			break;
		default:
			break;
		}

	default:
		break;
	}
}

// mouse menu control
// TODO: add a reset option
// for all rotations
// XXX: NEEDS TO BE IMPLEMENTED
void Control::menu(int id) {

	switch (id) {
	case Menu::QUIT:
		delete sceneGraph;
		exit(0);

		// XXX: reset rotations

	case Menu::RESET:
		sceneGraph->reset();
		window->redisplay();
		break;

		// END XXX

	case Menu::RESET_CAMERA:
		pan = 0;
		fov = 40;
		cameraZ = 1500;
		updateProjectionMatrix();
		updateViewMatrix();
		window->redisplay();

	case Menu::EULER:
		sceneGraph->setRotationMode(Rotation::EULER);
		window->redisplay();
		break;

	case Menu::MATRIX:
		sceneGraph->setRotationMode(Rotation::MATRIX);
		window->redisplay();
		break;

	default:
		break;
	}
}


// mouse pressed control
void Control::mousePressed() {


}

// mouse dragged control
void Control::mouseDragged() {


}

// select glut bitmap font
void* setFont(const string& name, const int size) {

	GLvoid* font;
	if (name.compare("helvetica") == 0) {
		if (size == 10)
			font = GLUT_BITMAP_HELVETICA_10;
		else if (size == 12)
			font = GLUT_BITMAP_HELVETICA_12;
		else if (size == 18)
			font = GLUT_BITMAP_HELVETICA_18;
	}
	else if (name.compare("times") == 0) {
		if (size == 10)
			font = GLUT_BITMAP_TIMES_ROMAN_10;
		if (size == 24)
			font = GLUT_BITMAP_TIMES_ROMAN_24;
	}
	else if (name.compare("8x13") == 0) {
		font = GLUT_BITMAP_8_BY_13;
	}
	else if (name.compare("9x15") == 0) {
		font = GLUT_BITMAP_9_BY_15;
	}
	return font;
}

// draw a string in 2D
static void drawString(GLvoid* font, float x, float y, const string& s) {
	glRasterPos2f(x, y);
	for (size_t i = 0; i < s.length(); i++)
		glutBitmapCharacter(font, s[i]);
}

// draw a string in 3D
static void drawString(GLvoid* font, float x, float y, float z, const string& s) {
	glRasterPos3f(x, y, z);
	for (size_t i = 0; i < s.length(); i++)
		glutBitmapCharacter(font, s[i]);
}

void Control::drawParameters(void) {

	glColor3f(1, 1, 1);
	glPushMatrix();
	glMatrixMode(GL_PROJECTION);
	mat4 orthographicProjectionMatrix = ortho(0.0f, (float)window->width(), (float)window->height(), 0.0f, -0.1f, 0.1f);
	glLoadMatrixf(&orthographicProjectionMatrix[0][0]);


	// glut bitmap font 
	// see setFont
	GLvoid* font = setFont("helvetica", 12);

	ostringstream s;
	s << "fov (f/F)               : " << fov << endl;
	drawString(font, window->width() - 170, window->height() - 45, s.str());
	s.str("");
	s << "camera z (d/D)     : " << setprecision(2) << cameraZ << endl;
	drawString(font, window->width() - 170, window->height() - 30, s.str());
	s.str("");
	s << "pan (p/P)             : " << setprecision(2) << pan << endl;
	drawString(font, window->width() - 170, window->height() - 15, s.str());

	glPopMatrix();
}

int main(int argc, char** argv) {

	// initialize OpenGL context
	OpenGLContext<Control>::init(argc, argv);

	//  build the robot hierarchy (see robot.cpp)
	Node* root = Robot::buildRobot();

	//make scenegraph
	SceneGraph* sceneGraph = new SceneGraph(root);
	Control::addSceneGraph(sceneGraph);

	//start event loop
	InputManager<Control>::startEventLoop();

	return 0;
}
