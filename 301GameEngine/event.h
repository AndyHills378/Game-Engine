#pragma once
#include <vector>
enum subSystem{uiManager, graphicsEngine };
enum eventType{accelerate, decelerate, turnLeft, turnRight};

class Event
{
public:
	
	Event(eventType myEvent) { myType = myEvent; }
	~Event() {};
	void addSubsystem(subSystem mySubsystem) { mySubSystems.push_back(mySubsystem); }
	eventType myType;
	vector<subSystem> mySubSystems;
};



