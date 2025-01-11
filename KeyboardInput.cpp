#include <Windows.h>
#include <iostream>
bool shift = false;
bool IsKeyDown(int key)
{
    return GetAsyncKeyState(key) & 0x8000;
}
bool CheckToggleKeys(int key)
{
    int evaluateKey = GetAsyncKeyState(key) & 0x0001;
    if(evaluateKey) return true;
    else return false;
}
bool MultiKeysPressed(std::initializer_list<int> keys)
{
    for (int key : keys)
    {
        if (!IsKeyDown(key))
        {
            return false;
        }
    }
    return true;
}
int WhichKey(){
    for (int key = 0x01; key <= 0xFE; ++key) {
        if (IsKeyDown(key)) {
            return key; 
        }
    }
    return 0; 
}
