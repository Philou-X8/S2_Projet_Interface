#include "inputmanager.h"

SerialPort* arduino; //doit etre un objet global!

InputManager::InputManager() {
    //arduino = nullptr;
    isActiveController = false;
    isActiveKeyboard = false;

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
}

bool InputManager::connectController() {
    if (arduino != nullptr) {
        if (arduino->isConnected()) {
            controllerConnected = true;
            return controllerConnected;
        }
    }
    
    string comPort = "COM1";
    for (int i = '1'; i <= '9'; i++) {
        comPort[3] = i;
        cout << "attemping port " << comPort << endl;
        arduino = new SerialPort(comPort.c_str(), BAUD);
        if (arduino->isConnected()) {
            controllerConnected = true;
            std::cout << "controller connnected on port " << comPort << endl;
            return controllerConnected;
        }
        else {
            std::cout << "failed to connect to " << comPort << endl;
            delete arduino;
        }
    }
    controllerConnected = false;
    return controllerConnected;
}

void InputManager::updateOutputInfo(int lvl, int ply) {
    //jsonOut.lock();
    comsOut.clear(); 
    int oddLvl = lvl % 2;
    comsOut["nb"] = lvl;
    switch (ply)
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
    //cout << "Updated coms: " << comsOut.dump() << endl;
    //jsonOut.unlock();

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

void InputManager::startThreads() {
    if (!isActiveKeyboard) {
        isActiveKeyboard = true;
        keyboardComs = thread(&InputManager::readKeyboard, this);
    }
    if (!isActiveController) {
        isActiveController = true;
        controllerComs = thread(&InputManager::readController, this);
    }
    cout << "\nThreads ready\n";
}

bool InputManager::stopThreads() {
    if (isActiveKeyboard) {
        isActiveKeyboard = false;
        keyboardComs.join();
    }
    if (isActiveController) {
        isActiveController = false;
        controllerComs.join();
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
    //Sleep(200);
    while (isActiveController) {
        //Sleep(20);
        if (!controllerConnected) {
            Sleep(1000);
            continue;
        }
        /*
        if (!sendComs()) {
            std::cout << "couldn't send to arduino\n";
        }
        */
        // skip loop if serial port is empty
        if (!recieveComs()) {
            continue;
        }
        
        //std::cout << comsIn.dump() << endl;
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
    string str_buffer;
    char char_buffer[MSG_MAX_SIZE];
    //Sleep(10);
    int buffer_size = arduino->readSerialPort(char_buffer, MSG_MAX_SIZE);
    if (buffer_size <= 0) {
        return false;
    }
    bool returnVal = false;
    str_buffer.assign(char_buffer, buffer_size);
    //cout << str_buffer << endl;

    size_t startChar = str_buffer.find_first_of('{');
    size_t endChar = str_buffer.find_first_of('}');
    if ((endChar != string::npos) && (newStr.size() > 40)) { // json completed
        newStr.append(str_buffer, 0, endChar);
        newStr += '}';
        comsIn.clear();
        //cout << "completed string: " << newStr << endl;
        
        comsIn = json::parse(newStr);
        newStr.clear();
        returnVal = true;
        
    }
    if (startChar != string::npos) { // start new json
        newStr.assign(str_buffer, startChar, string::npos);
    }
    else if (endChar == string::npos) { // json ongoing
        newStr.append(str_buffer);
    }

    return returnVal;
}
bool InputManager::sendComs() {
    //std::cout << "sending coms\n";
    //Sleep(50);
    //jsonOut.lock();
    //cout << "trying to send: " << comsOut.dump() << "----\n";
    bool success = arduino->writeSerialPort(
        comsOut.dump().c_str(),
        comsOut.dump().length()
    );
    //jsonOut.unlock();
    return success;
}

