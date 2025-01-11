#include "KeyboardInput.cpp"
#include <unordered_map>
#include <iostream>
using namespace std;
class InputManager
{
public:
    enum KeyState
    {
        Idle,
        Pressed,
        Held,
        Released
    };
    void setBinds(int key, string Actions);
    void Update();
    void ResetKeyStates(int V_Key);
    KeyState GetKeyState(int V_Key);

private:
    unordered_map<string, int> keyBinds;
    unordered_map<int, KeyState> KeyStates;
    unordered_map<int, bool> lastKeyStates;
};

void InputManager::setBinds(int key, string Actions)
{
    keyBinds[Actions] = key;
}
void InputManager::Update()
{
    for (int key = 0x01; key <= 0xFE; ++key)
    {
        bool isPressed = IsKeyDown(key);
        if (isPressed)
        {
            if (!lastKeyStates[key])
            {
                KeyStates[key] = Pressed; 
            }
            else
            {
                KeyStates[key] = Held; 
            }
        }
        else
        {
            if (lastKeyStates[key])
            {
                KeyStates[key] = Released; 
            }
            else
            {
                KeyStates[key] = Idle; 
            }
        }
        lastKeyStates[key] = isPressed;
    }
}

void InputManager::ResetKeyStates(int V_Key)
{
    KeyStates[V_Key] = Idle;
}
InputManager::KeyState InputManager::GetKeyState(int V_Key)
{
    return KeyStates[V_Key];
}
