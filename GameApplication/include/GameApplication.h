#ifndef _GAMEAPPLICATION_H
#define _GAMEAPPLICATION_H

#include "Common.h"

//Game Application class, this basically wraps up the initialisation of a game
//this will be the base class of any game we are making. You should override this
//and some of the methods to create your own game
class GameApplication:public NonCopyable
{
public:
	//Constructor
	GameApplication();
	//Virtual Deconstructor
	virtual ~GameApplication();

	//This is where all major subsystems are created
	virtual bool init(int args,char * arg[]);

	//Basically runs our game
	void run();
protected:
	ProgramOptions m_Options;

	unsigned int m_WindowWidth;
	unsigned int m_WindowHeight;
	unsigned int m_WindowCreationFlags;
	string m_WindowTitle;

	void parseConfig(int args,char * arg[]);
};
#endif
