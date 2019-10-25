#pragma once
#include "Header.h"
#include "GraphicsEngine.h"

class Model : public GraphicsEngine
{
public:
	Model();
	~Model();
	void setup(int modelNumber);
};

