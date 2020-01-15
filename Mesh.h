#pragma once

#include "GLIncludes.hpp"

class Mesh
{
public: 
	static const GLuint attribVertex = 0;
	static const GLuint attribNormal = 2;
	static const GLuint attribTexCoord = 8;
	static const GLuint attribJointIndices = 10;
	static const GLuint attribWeights = 11;
	virtual void draw(void) = 0;
};

