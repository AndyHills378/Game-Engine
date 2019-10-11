#pragma once

#include <vector>
#include "SubSystemEnum.h"
#include "EventTypeEnum.h"

class Event
{
public:
	Event(EventTypeEnum myEvent) { myType = myEvent; }
	~Event() {};
	void addSubsystem(SubSystemEnum mySubsystem) { mySubSystems.push_back(mySubsystem); }
	EventTypeEnum myType;
	
	std::vector<SubSystemEnum> mySubSystems;
};



