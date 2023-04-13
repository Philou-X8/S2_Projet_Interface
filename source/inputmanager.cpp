#include "inputmanager.h"

SerialPort* arduino; //doit etre un objet global!

InputManager::InputManager() {
    //arduino = nullptr;
    isActiveController = false;
    isActiveKeyboard = true;

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

bool InputManager::connectController() {
    if (arduino != nullptr) {
        if (arduino->isConnected()) {
            controllerConnected = true;
            return controllerConnected;
        }
    }
    
    std::string comPort = "COM1";
    for (int i = '1'; i <= '9'; i++) {
        comPort[3] = i;
        std::cout << "attemping port " << comPort << std::endl;
        arduino = new SerialPort(comPort.c_str(), BAUD);
        if (arduino->isConnected()) {
            controllerConnected = true;
            std::cout << "controller connnected on port " << comPort << std::endl;
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

void InputManager::addKey(char key) {

    threadLock.lock();
    if (pendingInput.size() < 5) {
        pendingInput.push(key);
    }
    threadLock.unlock();
}

void InputManager::startThreads() {
    if (!isActiveKeyboard) {
        isActiveKeyboard = true;
        keyboardComs = std::thread(&InputManager::readKeyboard, this);
    }
    if (!isActiveController) {
        isActiveController = true;
        controllerComs = std::thread(&InputManager::readController, this);
    }
    std::cout << "\nThreads ready\n";
}

bool InputManager::stopThreads() {
    if (isActiveKeyboard) {
        isActiveKeyboard = false;
        if(keyboardComs.joinable()) keyboardComs.join();
    }
    if (isActiveController) {
        isActiveController = false;
        if (controllerComs.joinable()) controllerComs.join();
    }
    return true;

}

void InputManager::readKeyboard() {
	char inputchar = 0;
	while (isActiveKeyboard) {
		inputchar = _getch();

		threadLock.lock();
		if (pendingInput.size() < 5) {
			pendingInput.push(inputchar);
		}
		threadLock.unlock();
	}
}

void flushSerial() {

    char char_buffer[MSG_MAX_SIZE];
    int buffer_size = MSG_MAX_SIZE;
    while (buffer_size > 25) {
        buffer_size = arduino->readSerialPort(char_buffer, MSG_MAX_SIZE);
    }
    
}

void InputManager::readController() {
    char inputchar = 0;
    flushSerial();
    while (isActiveController) {
        //Sleep(10);
        if (!controllerConnected) {
            //std::cout << "Notice: no controller connected\n";
            Sleep(5000);
            continue;
        }
        // skip loop if serial port is empty
        if (!recieveComs()) {
            continue;
        }
        
        //std::cout << comsIn.dump() << std::endl;
        std::list<char> newInput(decodeController());

        threadLock.lock();
        for (char c : newInput) {
            //cout << c << endl;
            if (c != 0) {
                pendingInput.push(c);
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
    
    if (activePlayer == 2 && controllerState.ply == PLY1) {
        controllerState.ply = PLY2;
        inputList.push_back(controllerState.ply);
    }
    else if (activePlayer == 1 && controllerState.ply == PLY2) {
        controllerState.ply = PLY1;
        inputList.push_back(controllerState.ply);
    }
    
    
    if (activePlayer == 2) {
        inputList.push_back(buttonPress(comsIn["rst"], controllerState.reload, 'r'));
        inputList.push_back(buttonPress(
            int(comsIn["dir"]) == 1,
            controllerState.up,
            'i'
        ));
        inputList.push_back(buttonPress(
            int(comsIn["dir"]) == 2,
            controllerState.down,
            'k'
        ));
        inputList.push_back(buttonPress(
            int(comsIn["dir"]) == 3,
            controllerState.right,
            'l'
        ));
        inputList.push_back(buttonPress(
            int(comsIn["dir"]) == 4,
            controllerState.left,
            'j'
        ));
        inputList.push_back(buttonPress(comsIn["a1"], controllerState.action, 'h'));

    }
    else {
        inputList.push_back(buttonPress(comsIn["rst"], controllerState.reload, 'r'));
        inputList.push_back(buttonPress(
            int(comsIn["dir"]) == 1,
            controllerState.up,
            'w'
        ));
        inputList.push_back(buttonPress(
            int(comsIn["dir"]) == 2,
            controllerState.down,
            's'
        ));
        inputList.push_back(buttonPress(
            int(comsIn["dir"]) == 3,
            controllerState.right,
            'd'
        ));
        inputList.push_back(buttonPress(
            int(comsIn["dir"]) == 4,
            controllerState.left,
            'a'
        ));
        inputList.push_back(buttonPress(comsIn["a1"], controllerState.action, 'f'));

    }
    return inputList;
}


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
        
        comsIn = json::parse(newStr);
        newStr.clear();
        returnVal = true;
        
    }
    if (startChar != std::string::npos) { // start new json
        newStr.assign(str_buffer, startChar, std::string::npos);
    }
    else if (endChar == std::string::npos) { // json ongoing
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

