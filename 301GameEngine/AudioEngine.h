#pragma once
#include "Header.h"
#include "SubSystemSuper.h"
#include "GameEngine.h"

class AudioEngine : public SubSystemSuper
{
private:
	static int(*EventReaction[2])();
public:
	static FMOD::Studio::System* system;
	static FMOD::System* lowLevelSystem;
	static FMOD::Sound* sound;
	static FMOD::Channel* Channel;
	AudioEngine();
	~AudioEngine();
	static int auAccelerate();
	static int auDecelerate();
	static void initEngine(/*int argc, char** argv*/);
	static void updateEngine(int deltaTime);
};

