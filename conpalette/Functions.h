#pragma once
#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <Windows.h>
bool IsOwnWindow();
BOOL WINAPI SignalControlCHandler(DWORD ctrlEvent);
#endif // !FUNCTIONS_H