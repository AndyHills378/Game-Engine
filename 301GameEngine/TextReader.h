//reader.h
#include "Header.h"

#ifndef TREADER_H
#define TREADER_H

#include "vertex.h"

struct TVertex {
	float x;
	float y;
	float z;
};

struct TFace
{
	int id1;
	int id2;
	int id3;
};

class TextReader {
public:
	int numPts;
	int numFaces;
	int numVerts;


	TVertex vertex[5000];
	TVertex texCoord[5000];
	TFace faces[5000];
	TFace texfaces[5000];

	Vertex* verts;

public:
	TextReader();
	~TextReader();

	void loadVertex(char* filename);
	void LoadFace(char* filename);
	void LoadTexCoord(char* filename);
	void LoadModel(char* filename);

	void FinalVertexData();
};

#endif
