/********
* File: inputmanager.h
* Team: P-6
* Creation Date: 
* Description: Manage serial communication with the remote controller
*			   Syncronize keyboard and controller inputs
*
* Full project and latest version: https://github.com/Philou-X8/S2_Projet_Interface.git
********/
#pragma once

#include <iostream>	// std::cout
#include <string>
#include <thread>	// std::thread
#include <mutex>
#include <list>
#include <queue>
#include <conio.h>  // old
#include "include/serial/SerialPort.hpp"
#include "include/json.hpp"

using json = nlohmann::json;

#define BAUD 9600           // Frequence de transmission serielle
#define MSG_MAX_SIZE 1024   // Longueur maximale d'un message


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
	bool enter = ARMED;
	bool muon = ARMED;
	int dir = 0; // up, down, right, left
	char ply = PLY1;
};

class InputManager
{
public:
	InputManager();
	~InputManager();

	bool connectController();

	void updateOutputInfo(int nbDisplay, int ledMode); // send to controller
	char getInput(); // recieve from controller
	void addKey(char key); // add key to the queue

	void startThreads();
	bool stopThreads();

private:
	std::mutex jsonOut;
	json comsIn;
	json comsOut;

	/********** Thread management **********/
	std::mutex threadLock; // to lock pendingInput
	std::queue<char, std::list<char>> pendingInput;
	std::thread keyboardComs; // reading from the keyboard
	std::thread controllerComs; // reading from the controller
	void readKeyboard(); // looping thread
	void readController(); // looping thread
	bool isActiveKeyboard; // should keep the threads running
	bool isActiveController; // should keep the threads running
	
	bool controllerConnected; // connection is succesful

	buttonstates keyboardState; // unused
	buttonstates controllerState;
	int joystickHold;

	/********** Used by readController() **********/
	std::string newStr;
	std::list<char> decodeController();
	char joystickMove(int recivedState, int ply);
	char buttonPress(int recivedState, bool& buttonState, char map);


	/********** Serial ports **********/
	bool sendComs(); // serial port communication
	bool recieveComs(); // serial port communication
	void flushSerial();

};

