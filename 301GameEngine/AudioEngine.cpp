#include "AudioEngine.h"
#include <fmod_errors.h>

int(*AudioEngine::EventReaction[2])();
FMOD::Studio::System* AudioEngine::system = NULL;
FMOD::System* AudioEngine::lowLevelSystem = NULL;
FMOD::Sound* AudioEngine::sound = NULL;
FMOD::Channel* AudioEngine::Channel = NULL;
FMOD::Channel* AudioEngine::BGM = NULL;
FMOD::Sound* AudioEngine::BGMSound = NULL;
bool bIsPlaying = false;
bool BGMPlaying = false;

///if audioengine breaks use commented code below to work out the error
//FMOD_RESULT result = 
/*if (result)
{
	std::cout << FMOD_ErrorString(result) << std::endl;
}*/
AudioEngine::AudioEngine()
{
}

AudioEngine::~AudioEngine()
{
}

int AudioEngine::auAccelerate()
{
	if (Channel->isPlaying(&bIsPlaying))
	{
		//std::cout << FMOD_ErrorString(result) << std::endl;
		lowLevelSystem->playSound(sound, NULL, false, &Channel);
		bIsPlaying = true;
	}
	return 0;
}

int AudioEngine::auDecelerate()
{
	return 0;
}


void AudioEngine::updateEngine(int deltaTime)
{
	system->update();
	//read event queue
	for (int i = 0; i < GameEngine::EventQueue.size();i++)
	{
		for (int j = 0; j < GameEngine::EventQueue[i].mySubSystems.size(); j++)
		{
			if (GameEngine::EventQueue[i].mySubSystems[j] == SubSystemEnum::audioEngine)
			{
				EventReaction[(int)GameEngine::EventQueue[i].myType]();
				GameEngine::EventQueue[i].mySubSystems.erase(GameEngine::EventQueue[i].mySubSystems.begin() + j);
			}
		}
	}
}

void AudioEngine::initEngine()
{

	FMOD::Studio::System::create(&system);

	if (system) {
		cout << "High-level (fmod studio) audio system created." << "\n";
	}

	system->getLowLevelSystem(&lowLevelSystem);
	if (lowLevelSystem) {
		cout << "Low-level (fmod) audio system created." << "\n";
	}

	lowLevelSystem->setSoftwareFormat(0, FMOD_SPEAKERMODE_STEREO, 0);
	system->initialize(1024, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, NULL);


	lowLevelSystem->createSound("car_engine.wav", FMOD_LOOP_OFF, NULL, &sound);
	lowLevelSystem->createSound("BGM.wav", FMOD_LOOP_NORMAL, NULL, &BGMSound);

	if (sound) {
		cout << "Sound loaded." << "\n";
	}
	if (BGMSound)
	{
		cout << "background music loaded" << "\n";
	}

	sound->setDefaults(16400, 0);
	BGMSound->setDefaults(16400, 0);
	
		//std::cout << FMOD_ErrorString(result) << std::endl;
	
	lowLevelSystem->playSound(BGMSound, NULL, false, &BGM);

	int(*p_auAccelerate)() = auAccelerate;
	int(*p_auDecelerate)() = auDecelerate;
	EventReaction[0] = p_auAccelerate;
	EventReaction[1] = p_auDecelerate;
}