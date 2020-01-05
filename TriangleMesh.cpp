/* ----------------------------------------------------------------
   name:           TriangleMesh.cpp
   purpose:        cg1_ex3 2014 triangle mesh for OpenGL rendering
   version:	   SKELETON CODE
   TODO:           copy draw() from exercise 1.3
   author:         katrin lang
				   computer graphics
				   htw berlin
   ------------------------------------------------------------- */

#include "TriangleMesh.hpp"

   // use this with care
   // might cause name collisions
using namespace glm;

#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

// NVIDIA wants it like this
// see https://www.opengl.org/sdk/docs/tutorials/ClockworkCoders/attributes.php
const GLuint TriangleMesh::attribVertex = 0;
const GLuint TriangleMesh::attribNormal = 2;
const GLuint TriangleMesh::attribColor = 3;
const GLuint TriangleMesh::attribTexCoord = 8;

TriangleMesh::TriangleMesh() : winding(CW) {
}

TriangleMesh::TriangleMesh(const std::string& fileName) : winding(CW) {

	load(fileName);
}

TriangleMesh::~TriangleMesh() {

}

void TriangleMesh::setWinding(PolygonWinding winding) {
	this->winding = winding;
}

// center the mesh at its origin
void TriangleMesh::center(void) {

	computeBoundingBox();

	vec3 center = (boundingBoxMin + boundingBoxMax) * vec3(0.5);

	for (unsigned int i = 0; i < positions.size(); i++) {
		positions[i] -= center;
	}
	boundingBoxMin -= center;
	boundingBoxMax -= center;
}

// scale to size 1
void TriangleMesh::unitize(void) {

	computeBoundingSphere();

	for (unsigned int i = 0; i < positions.size(); ++i) {
		positions[i] /= boundingSphereRadius;
	}
	boundingSphereRadius = 1;
	boundingBoxMin = vec3(-1);
	boundingBoxMax = vec3(1);
}

// compute bounding sphere
void TriangleMesh::computeBoundingSphere(void) {

	boundingSphereRadius = 0;
	for (unsigned int i = 0; i < positions.size(); i++) {
		vec3 v = positions[i];
		if (length(v) > boundingSphereRadius) boundingSphereRadius = length(v);
	}
}

// compute bounding box
void TriangleMesh::computeBoundingBox(void) {

	boundingBoxMin = vec3(numeric_limits<float>::max());
	boundingBoxMax = vec3(numeric_limits<float>::min());
	for (unsigned int i = 0; i < positions.size(); i++) {
		if (positions[i].x < boundingBoxMin.x) boundingBoxMin.x = positions[i].x;
		if (positions[i].x > boundingBoxMax.x) boundingBoxMax.x = positions[i].x;
		if (positions[i].y < boundingBoxMin.y) boundingBoxMin.y = positions[i].y;
		if (positions[i].y > boundingBoxMax.y) boundingBoxMax.y = positions[i].y;
		if (positions[i].z < boundingBoxMin.z) boundingBoxMin.z = positions[i].z;
		if (positions[i].z > boundingBoxMax.z) boundingBoxMax.z = positions[i].z;
	}
}

void TriangleMesh::load(const string& fileName) {

	loadObj(fileName);
	center();
	unitize();
	if (!hasNormals()) computeNormals();
}

// load an OBJ model
void TriangleMesh::loadObj(const string& fileName) {

	/**
	 * .obj file format
	 *
	 * '#'  -  comment
	 * 'v'  -  vertex position (3 floats separated by whitespace)
	 * 'vt' -  texture coordinates (2 floats separated by whitespace)
	 * 'vn' -  vertex normal (3 floats separated by whitespace)
	 * 'f'  -  faces, n times 3 v/vt/vn indices separated by /  and whitespace: v/t/n v/t/n ... v/t/n
	 */

	const string POSITION = "v";
	const string TEX_COORD = "vt";
	const string NORMAL = "vn";
	const string FACE = "f";

	ifstream file;
	file.open(fileName.c_str());

	vector<GLuint> pi;
	vector<GLuint> ti;
	vector<GLuint> ni;
	string l;

	while (getline(file, l)) {

		stringstream line(l);
		string type;
		line >> type;

		if (type == POSITION) {

			float x, y, z;
			line >> x >> y >> z;
			positions.push_back(vec3(x, y, z));
		}
		else if (type == TEX_COORD) {

			float u, v;
			line >> u >> v;
			texCoordsRaw.push_back(vec2(u, v));
		}
		else if (type == NORMAL) {

			float nx, ny, nz;
			line >> nx >> ny >> nz;
			normalsRaw.push_back(vec3(nx, ny, nz));
		}
		else if (type == FACE) {
			cout << "jhvgz" << endl;
			pi.clear();
			ti.clear();
			ni.clear();
			GLuint positionIndex, texCoordIndex, normalIndex;
			char slash;

			while (!line.eof()) {

				// v v v
				if (line.str().find('/') == string::npos && line.str().length() > 5) {
					line >> positionIndex;
					pi.push_back(positionIndex - 1);
				}
				// v//n v//n v//n
				else if (line.str().find("//") != string::npos) {
					line >> positionIndex >> slash >> slash >> normalIndex;
					pi.push_back(positionIndex - 1);
					ni.push_back(normalIndex - 1);
				}
				else {
					// v/t v/t v/t
					line >> positionIndex >> slash >> texCoordIndex;
					pi.push_back(positionIndex - 1);
					ti.push_back(texCoordIndex - 1);
					// v/t/n v/t/n v/t/n
					if (line.peek() == '/') {
						line >> slash >> normalIndex;
						ni.push_back(normalIndex - 1);
					}
				}
			} // line end
			// FIX ME!!!
			//      if(pi.size()>15 && pi[(int)pi.size()-1]==pi[(int)pi.size()-2]) pi.pop_back();
			triangulate(pi, ti, ni);
		} // end face
	}
	file.close();

	// bring to format opengl eats
	// this means possible duplication of normals 
	// and / or texture coordinates
	clean();

	cout << "loaded " << fileName << ": "
		<< positions.size() << " vertices, " << texCoordsRaw.size() << " texture coordinates, " << normalsRaw.size() << " normals, "
		<< faces.size() << " faces" << endl;
}

// triangulate a polygon
void TriangleMesh::triangulate(vector<GLuint> pi, vector<GLuint> ti, vector<GLuint> ni) {

	for (unsigned int v = 2; v < pi.size(); v++) {

		cout << pi[0] << " " << pi[v - 1] << " " << pi[v] << endl;
		if (winding == CW)
			faces.push_back(uvec3(pi[0], pi[v - 1], pi[v]));
		else
			faces.push_back(uvec3(pi[v], pi[v - 1], pi[0]));
	}

	for (size_t v = 2; v < ti.size(); v++) {

		if (winding == CW)
			texCoordIndices.push_back(uvec3(ti[0], ti[v - 1], ti[v]));
		else
			texCoordIndices.push_back(uvec3(ti[v], ti[v - 1], ti[0]));
	}

	for (unsigned int v = 2; v < ni.size(); v++) {

		if (winding == CW)
			normalIndices.push_back(uvec3(ni[0], ni[v - 1], ni[v]));
		else
			normalIndices.push_back(uvec3(ni[v], ni[v - 1], ni[0]));
	}

	pi.clear();
	ti.clear();
	ni.clear();
}

// bring to format opengl eats
// this means possible duplication of normals
// and / or texture coordinates
void TriangleMesh::clean() {

	cout << "lisudhcliuesh " << faces.size() << " " << normalIndices.size() << " " << texCoordIndices.size() << endl;

	if (normalIndices.size() > 0) normals.resize(positions.size());

	for (unsigned int i = 0; i < normalIndices.size(); i++) {
		cout << "..." << normals.size() << " " << normalsRaw.size() << endl;
		cout << faces[i][0] << " " << normalIndices[i][0] << endl;
		normals[faces[i][0]] = normalsRaw[normalIndices[i][0]];
		normals[faces[i][1]] = normalsRaw[normalIndices[i][1]];
		normals[faces[i][2]] = normalsRaw[normalIndices[i][2]];
	}
	cout << "------------------------" << endl;
	normalsRaw.clear();
	normalIndices.clear();

	//normalize
	for (size_t i = 0; i < normals.size(); i++) {
		normals[i] = normalize(normals[i]);
	}

	if (texCoordIndices.size() > 0) texCoords.resize(positions.size());
	for (unsigned int i = 0; i < texCoordIndices.size(); i++) {
		texCoords[faces[i][0]] = texCoordsRaw[texCoordIndices[i][0]];
		texCoords[faces[i][1]] = texCoordsRaw[texCoordIndices[i][1]];
		texCoords[faces[i][2]] = texCoordsRaw[texCoordIndices[i][2]];
	}
	texCoordsRaw.clear();
	texCoordIndices.clear();
}

// TODO: load triangle mesh in OFF format
void TriangleMesh::loadOff(const string& fileName) {

}

bool TriangleMesh::hasNormals(void) {
	return normals.size() > 0;
}

/**
 * compute smooth per-vertex normals
 * simple averaging is fine
 */
void TriangleMesh::computeNormals(void) {

}

// TODO: draw positions and normals
void TriangleMesh::draw(void)
{
	glBindVertexArray(0);

	glEnableVertexAttribArray(attribVertex);
	glVertexAttribPointer(attribVertex, 3, GL_FLOAT, GL_FALSE, 0, &positions[0]);

	glEnableVertexAttribArray(attribNormal);
	glVertexAttribPointer(attribNormal, 3, GL_FLOAT, GL_FALSE, 0, &normals[0]);

	glDrawElements(GL_TRIANGLES, faces.size() * 3, GL_UNSIGNED_INT, &faces[0]);

	glDisableVertexAttribArray(attribVertex);
	glDisableVertexAttribArray(attribNormal);
}
