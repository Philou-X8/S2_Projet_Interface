#pragma once

#include <iostream>	// std::cout
#include <string>
#include <thread>	// std::thread
#include <mutex>
#include <list>
#include <queue>
#include <conio.h>
#include "include/serial/SerialPort.hpp"
#include "include/json.hpp"

using json = nlohmann::json;

#define BAUD 9600           // Frequence de transmission serielle
#define MSG_MAX_SIZE 1024   // Longueur maximale d'un message

using namespace std;

#define ACTIVE 1
#define ARMED 0

const char PLY1 = 't';
const char PLY2 = 'y';

struct buttonstates {
	bool up = ARMED;
	bool down = ARMED;
	bool right = ARMED;
	bool left = ARMED;
	bool action = ARMED;
	bool reload = ARMED;
	bool menu = ARMED;
	int dir = 0;
	char ply = PLY1;
};

class InputManager
{
public:
	InputManager();
	~InputManager();

	bool connectController();

	void updateOutputInfo(int lvl, int ply); // send to controller
	char getInput(); // recieve from controller

	void startThreads();
	bool stopThreads();

private:
	mutex jsonOut;
	json comsIn;
	json comsOut;

	/********** Thread management **********/
	mutex threadLock; // to lock pendingInput
	queue<char, std::list<char>> pendingInput;
	thread keyboardComs; // reading from the keyboard
	thread controllerComs; // reading from the controller
	void readKeyboard(); // looping thread
	void readController(); // looping thread
	bool isActiveKeyboard; // should keep the threads running
	bool isActiveController; // should keep the threads running
	
	bool controllerConnected; // connection is succesful

	buttonstates keyboardState; // unused
	buttonstates controllerState;

	/********** Used by readController() **********/
	string newStr;
	std::list<char> decodeController();
	char buttonPress(int recivedState, bool& buttonState, char map);


	/********** Serial ports **********/
	bool sendComs(); // serial port communication
	bool recieveComs(); // serial port communication

};

