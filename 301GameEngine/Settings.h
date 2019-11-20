#pragma once
#include "Header.h"

#define SCREEN_HEIGHT 1000
#define SCREEN_WIDTH 1000

static vector<Vertex> skyVertices =
{
	{vec3(500.0f, 0.0, -500.0f), vec3(0.0, 0.0, 1.0), vec2(1.0, 0.0)},
	{vec3(500.0f, 1000.0f, -500.0f), vec3(0.0, 0.0, 1.0), vec2(1.0, 1.0)},
	{vec3(-500.0f, 0.0, -500.0f), vec3(0.0, 0.0, 1.0), vec2(0.0, 0.0)},
	{vec3(-500.0f, 1000.0f, -500.0f), vec3(0.0, 0.0, 1.0), vec2(0.0, 1.0)}
};

static Light light0 =
{
	vec4(0.0, 0.0, 0.0, 1.0),
	vec4(1.0, 1.0, 1.0, 1.0),
	vec4(1.0, 1.0, 1.0, 1.0),
	vec4(1.0, 0.0, 0.0, 0.0)
};