#pragma once
#include "Header.h"
#include "event.h"

class SubSystemSuper
{
public:

	static std::map <int, bool> specialKeys;
	static std::map <char, bool> keys;
	static bool debugMode;
	SubSystemSuper();
	~SubSystemSuper();
	
};

