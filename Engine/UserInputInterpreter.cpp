#include "UserInputInterpreter.h"

UserInputInterpreter::UserInputInterpreter(int screenWidth, int screenHeight, HINSTANCE hinstance, HWND hwnd): screenWidth(screenWidth), screenHeight(screenHeight), mouseX(0), mouseY(0) {
    HRESULT result;

    result = DirectInput8Create(hinstance, DIRECTINPUT_VERSION, IID_IDirectInput8, reinterpret_cast<void**>(directInput.GetAddressOf()), nullptr);
    if (FAILED(result)) {
        //todo handle error
    }

    result = directInput->CreateDevice(GUID_SysKeyboard, keyboard.GetAddressOf(), nullptr);
    if (FAILED(result)) {
        //todo handle error
    }

    // Set the data format.  In this case since it is a keyboard we can use the predefined data format.
    result = keyboard->SetDataFormat(&c_dfDIKeyboard);
    if (FAILED(result)) {
        //todo handle error
    }

    // Set the cooperative level of the keyboard to not share with other programs.
    result = keyboard->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE);
    if (FAILED(result)) {
        //todo handle error
    }

    // Now acquire the keyboard.
    result = keyboard->Acquire();
    if (FAILED(result)) {
        //todo handle error
    }

    // Initialize the direct input interface for the mouse.
    result = directInput->CreateDevice(GUID_SysMouse, mouse.GetAddressOf(), nullptr);
    if (FAILED(result)) {
        //todo handle error
    }

    // Set the data format for the mouse using the pre-defined mouse data format.
    result = mouse->SetDataFormat(&c_dfDIMouse);
    if (FAILED(result)) {
        //todo handle error
    }

    // Set the cooperative level of the mouse to share with other programs.
    result = mouse->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
    if (FAILED(result)) {
        //todo handle error
    }

    // Acquire the mouse.
    result = mouse->Acquire();
    if (FAILED(result)) {
        //todo handle error
    }

    for (unsigned char& keyState : keyboardState) {
        keyState = '\0';
    }
}


UserInputInterpreter::~UserInputInterpreter() {
    mouse->Unacquire();
    keyboard->Unacquire();
}

void UserInputInterpreter::detect() {
    readKeyboard();
    readMouse();
}

bool UserInputInterpreter::isEscapePressed() {
    return (keyboardState[DIK_ESCAPE] & 0x80) != 0;
}

void UserInputInterpreter::getMouseLocation(int& mouseX, int& mouseY) const {
    mouseX = this->mouseX;
    mouseY = this->mouseY;
}

void UserInputInterpreter::readKeyboard() {
    HRESULT result = keyboard->GetDeviceState(sizeof(keyboardState), static_cast<LPVOID>(&keyboardState));
    if (FAILED(result)) {
        // If the keyboard lost focus or was not acquired then try to get control back.
        if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED)) {
            keyboard->Acquire();
        } else {
            // todo: handle error
        }
    }
}

void UserInputInterpreter::readMouse() {
    HRESULT result = mouse->GetDeviceState(sizeof(DIMOUSESTATE), static_cast<LPVOID>(&mouseState));
    if (FAILED(result)) {
        // If the mouse lost focus or was not acquired then try to get control back.
        if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED)) {
            mouse->Acquire();
        } else {
            // todo: handle error
        }
    }

    // Update the location of the mouse cursor based on the change of the mouse location during the frame.
    mouseX += mouseState.lX;
    mouseY += mouseState.lY;

    // Ensure the mouse location doesn't exceed the screen width or height.
    if (mouseX < 0) { mouseX = 0; }
    if (mouseY < 0) { mouseY = 0; }

    if (mouseX > screenWidth) { mouseX = screenWidth; }
    if (mouseY > screenHeight) { mouseY = screenHeight; }
}
