/********
* File: inputmanager.cpp
* Team: P-6
* Creation Date: 
* Description: Manage serial communication with the remote controller
*			   Syncronize keyboard and controller inputs
*
* Full project and latest version: https://github.com/Philou-X8/S2_Projet_Interface.git
********/
#include "inputmanager.h"

SerialPort* arduino; //doit etre un objet global!

InputManager::InputManager() {
    //arduino = nullptr;
    isActiveController = false;
    isActiveKeyboard = true; // should only be false is there is no other keyboard listener 

    joystickHold = 0;

    newStr.clear();
    //jsonOut.lock();
    comsOut["nb"] = 0;
    comsOut["r"] = 255;
    comsOut["g"] = 0;
    comsOut["b"] = 0;
    //jsonOut.unlock();
    
    connectController();
    startThreads();
}
InputManager::~InputManager() {
    stopThreads();
    //arduino->closeSerial();
}
// establish connection with the serial port
bool InputManager::connectController() {
    if (arduino != nullptr) {
        if (arduino->isConnected()) {
            controllerConnected = true;
            return controllerConnected;
        }
    }
    // try COM ports until the right one is found
    std::string comPort = "COM1";
    for (int i = '1'; i <= '9'; i++) {
        comPort[3] = i;
        std::cout << "attemping port " << comPort << std::endl;
        arduino = new SerialPort(comPort.c_str(), BAUD); // try to connect
        if (arduino->isConnected()) {
            controllerConnected = true;
            std::cout << "controller connnected on port " << comPort << std::endl;
            //flushSerial();
            return controllerConnected;
        }
        else {
            std::cout << "failed to connect to " << comPort << std::endl;
            delete arduino;
        }
    }
    controllerConnected = false;
    return controllerConnected;
}
// format information for sending
void InputManager::updateOutputInfo(int nbDisplay, int ledMode) {
    //jsonOut.lock();
    comsOut.clear(); 
    comsOut["nb"] = nbDisplay;
    switch (ledMode)
    {
    case 1:
        comsOut["r"] = 255;
        comsOut["g"] = 0;
        comsOut["b"] = 0;
        break;
    case 2:
        comsOut["r"] = 0;
        comsOut["g"] = 0;
        comsOut["b"] = 255;
        break;
    default:
        comsOut["r"] = 0;
        comsOut["g"] = 0;
        comsOut["b"] = 0;
        break;
    }
    //std::cout << "Updated coms: " << comsOut.dump() << std::endl;
    //jsonOut.unlock();
    /*
    std::string str = "{00a00}";
    str.replace(1, 2, std::to_string(nbDisplay));
    str.replace(4, 5, std::to_string(ledMode));
    std::cout << "Updated coms: " << str << std::endl;

    bool success = arduino->writeSerialPort(
        str.c_str(),
        str.length()
    );
    */

    sendComs();
}
// get oldest input from the queue
char InputManager::getInput() {

    char returnVal = 0;
    threadLock.lock();
    if (pendingInput.size() > 0) {
        returnVal = pendingInput.front();
        pendingInput.pop();
    }
    threadLock.unlock();
    return returnVal;
}
// add input to the queue
void InputManager::addKey(char key) {

    threadLock.lock();
    if (pendingInput.size() < 5) {
        pendingInput.push(key);
    }
    threadLock.unlock();
}
// start the listeners threads
void InputManager::startThreads() {
    if (!isActiveKeyboard) { // if there is no keyboard thread 
        isActiveKeyboard = true;
        //keyboardComs = std::thread(&InputManager::readKeyboard, this); // create thread
    }
    if (!isActiveController) { // if there is no controller thread 
        isActiveController = true;
        controllerComs = std::thread(&InputManager::readController, this); // create thread
    }
    std::cout << "\nThreads ready\n";
}
// stop threads
bool InputManager::stopThreads() {
    if (isActiveKeyboard) {
        isActiveKeyboard = false; // stop the thread's loop
        //if(keyboardComs.joinable()) keyboardComs.join(); // stop the thread
    }
    if (isActiveController) {
        isActiveController = false; // stop the thread's loop
        if (controllerComs.joinable()) controllerComs.join(); // stop the thread
    }
    return true;

}

// weak keyboard lister. Better listener should be used along with this.addKey(key);
void InputManager::readKeyboard() {
	char inputchar = 0;
	while (isActiveKeyboard) { // keep the thread running
		inputchar = _getch(); // read keyboard

		threadLock.lock();
		if (pendingInput.size() < 5) {
			pendingInput.push(inputchar);
		}
		threadLock.unlock();
	}
}

void InputManager::flushSerial() {

    char char_buffer[MSG_MAX_SIZE];
    int buffer_size = MSG_MAX_SIZE;
    while (buffer_size > 25) {
        buffer_size = arduino->readSerialPort(char_buffer, MSG_MAX_SIZE);
    }
    
}

void InputManager::readController() {
    char inputchar = 0;
    flushSerial();
    newStr.clear();
    while (isActiveController) { // keep the thread running
        //Sleep(10);
        if (!controllerConnected) {
            //std::cout << "Notice: no controller connected\n";
            Sleep(5000);
            continue;
        }
        // skip loop if serial port is empty
        if (!recieveComs()) { // read serial port
            continue;
        }
        
        //std::cout << comsIn.dump() << std::endl;
        std::list<char> newInput(decodeController()); // decode serial

        threadLock.lock();
        for (char c : newInput) {
            //cout << c << endl;


            // temp
            if (c == 'm') std::cout << "muon detected" << std::endl;
            // temp


            if (c != 0) {
                pendingInput.push(c); // add inputs to queue
            }
        }
        threadLock.unlock();

        //tempExample = comsIn["mouvment"].get<int>(); // read json field
    }
}


std::list<char> InputManager::decodeController() {
    std::list<char> inputList;
    int activePlayer;
    activePlayer = comsIn["act"];
    //std::cout << "activePlayer: " << activePlayer << std::endl;
    
    if (activePlayer == 2 && controllerState.ply == PLY1) {
        controllerState.ply = PLY2;
        inputList.push_back(controllerState.ply);
    }
    else if (activePlayer == 1 && controllerState.ply == PLY2) {
        controllerState.ply = PLY1;
        inputList.push_back(controllerState.ply);
    }
    

    inputList.push_back(buttonPress(comsIn["rst"], controllerState.reload, 'r'));
    inputList.push_back(buttonPress(comsIn["m1"], controllerState.reload, 'r'));
    inputList.push_back(buttonPress(comsIn["m2"], controllerState.menu, 'p'));
    inputList.push_back(buttonPress(comsIn["a2"], controllerState.enter, ' '));
    inputList.push_back(buttonPress(comsIn["mu"], controllerState.muon, 'm'));

    //std::cout << "muon state: " << controllerState.muon << std::endl;
    if (activePlayer == 2) {
        inputList.push_back(buttonPress(comsIn["a1"], controllerState.action, 'h'));
        char cntInput = joystickMove(comsIn["dir"], activePlayer);
        if (cntInput != 0) inputList.push_back(cntInput);
    }
    else {
        inputList.push_back(buttonPress(comsIn["a1"], controllerState.action, 'f'));
        char cntInput = joystickMove(comsIn["dir"], activePlayer);
        if (cntInput != 0) inputList.push_back(cntInput);
    }
    return inputList;
}


char InputManager::joystickMove(int recivedState, int ply) {
    if (recivedState == controllerState.dir) {
        joystickHold++;
        if (joystickHold > 10) {
            joystickHold = 0;
            controllerState.dir = 0;
        }
        return 0;
    }

    controllerState.dir = recivedState;
    if (ply == 1) {
        switch (recivedState) {
        case 1:
            return 'w'; // up
        case 2:
            return 's'; // down
        case 3:
            return 'd'; // right
        case 4:
            return 'a'; // left
        }
    }
    else if (ply == 2) {
        switch (recivedState) {
        case 1:
            return 'i'; // up
        case 2:
            return 'k'; // down
        case 3:
            return 'l'; // right
        case 4:
            return 'j'; // left
        }
    }
    
}

// generate an input only on toggle down
char InputManager::buttonPress(int recivedState, bool& buttonState, char map) {
    
    if (recivedState == 1 && buttonState == ARMED) {
        buttonState = ACTIVE;
        return map;
    }
    else if (recivedState == 0) {
        buttonState = ARMED;
    }
    return 0;
}


bool InputManager::recieveComs() {
    std::string str_buffer;
    char char_buffer[MSG_MAX_SIZE];
    //Sleep(50);
    int buffer_size = arduino->readSerialPort(char_buffer, MSG_MAX_SIZE);
    if (buffer_size <= 0) {
        return false;
    }
    bool returnVal = false;
    str_buffer.assign(char_buffer, buffer_size);
    //std::cout << "Serial read: " << str_buffer << std::endl;
    //Sleep(20);

    size_t startChar = str_buffer.find_first_of('{');
    size_t endChar = str_buffer.find_first_of('}');
    //std::cout << "start char pos: " << startChar << std::endl;
    if ((endChar != std::string::npos) && (newStr.size() > 40)) { // json completed
        newStr.append(str_buffer, 0, endChar);
        newStr += '}';
        comsIn.clear();
        //std::cout << "completed string: " << newStr << std::endl;
        newStr = newStr.substr(0, 60); // size of json = 60
        comsIn = json::parse(newStr);
        newStr.clear();
        returnVal = true;
        
    }
    if (startChar != std::string::npos) { // start new json
        newStr.assign(str_buffer, startChar, std::string::npos);
    }
    else if (endChar == std::string::npos && newStr.size() > 0) { // json ongoing
        newStr.append(str_buffer);
    }

    return returnVal;
}
bool InputManager::sendComs() {
    //std::cout << "sending coms\n";
    //Sleep(50);
    //jsonOut.lock();
    //cout << "trying to send: " << comsOut.dump() << "----\n";
    if (!controllerConnected) return false;

    bool success = arduino->writeSerialPort(
        comsOut.dump().c_str(),
        comsOut.dump().length()
    );
    //jsonOut.unlock();
    return success;
}

