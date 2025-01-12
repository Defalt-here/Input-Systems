#include "KeyboardInput.cpp"
#include "MouseInput.cpp"
#include <unordered_map>
#include <iostream>
#include <vector>
using namespace std;
class InputManager
{
public:
    enum keyState
    {
        Idle,
        Pressed,
        Held,
        Released
    };
    bool setBinds(int key,string Actions);
    void Update();
    void ResetKeyState(int V_Key);
    keyState GetKeyState(int V_Key);
    int WhichKey();
    vector<int> WhichKeyMultiple();

private:
    unordered_map<int,string> keyBinds;
    unordered_map<int, keyState> keyStates;
    unordered_map<int, bool> lastkeyStates;
};

bool InputManager::setBinds(int key,string Actions)
{
    if(keyBinds.find(key) == keyBinds.end()){
    keyBinds[key] = Actions;
    return true;
    }
    return false;
}
void InputManager::Update()
{
    for (int key = 0x01; key <= 0xFE; ++key)
    {
        bool isPressed = IsKeyDown(key);
        if (isPressed)
        {
            if (!lastkeyStates[key])
            {
                keyStates[key] = Pressed; 
            }
            else
            {
                keyStates[key] = Held; 
            }
        }
        else
        {
            if (lastkeyStates[key])
            {
                keyStates[key] = Released; 
            }
            else
            {
                keyStates[key] = Idle; 
            }
        }
        lastkeyStates[key] = isPressed;
    }
}

void InputManager::ResetKeyState(int V_Key)
{
    keyStates[V_Key] = Idle;
}
InputManager::keyState InputManager::GetKeyState(int V_Key)
{
    return keyStates[V_Key];
}

int InputManager::WhichKey(){
    for(auto it = keyBinds.begin(); it != keyBinds.end(); it++){
        int key = it -> first;
        if (IsKeyDown(key)) {
            return key; 
        }
    }
    return 0;
}
