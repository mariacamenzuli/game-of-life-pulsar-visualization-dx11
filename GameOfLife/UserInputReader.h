#pragma once

#define DIRECTINPUT_VERSION 0x0800

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

#include <dinput.h>
#include <wrl/client.h>

class UserInputReader {
public:
    UserInputReader(int screenWidth, int screenHeight, HINSTANCE hinstance, HWND hwnd);
    ~UserInputReader();

    void read();
    bool isEscapePressed();
    bool isQPressed();
    bool isWPressed();
    bool isEPressed();
    bool isAPressed();
    bool isSPressed();
    bool isDPressed();
    bool isZPressed();
    bool isCPressed();
    void getMouseLocation(int& mouseX, int& mouseY) const;

private:
    Microsoft::WRL::ComPtr<IDirectInput8> directInput;
    Microsoft::WRL::ComPtr<IDirectInputDevice8> keyboard;
    Microsoft::WRL::ComPtr<IDirectInputDevice8> mouse;

    unsigned char keyboardState[256];
    DIMOUSESTATE mouseState;

    int screenWidth, screenHeight;
    int mouseX, mouseY;

    void readKeyboard();
    void readMouse();
};

