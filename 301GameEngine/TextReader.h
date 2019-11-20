#ifndef TREADER_H
#define TREADER_H

#include "vertex.h"
//reader.h
#include "Header.h"

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


	TVertex vertex[15000];
	TVertex texCoord[15000];
	TFace faces[15000];
	TFace texfaces[15000];

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
