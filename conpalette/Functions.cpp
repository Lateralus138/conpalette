#include "functions.h"
bool IsOwnWindow()
{
  HWND hwndConsole = GetConsoleWindow();
  DWORD dwProcessId;
  GetWindowThreadProcessId(hwndConsole, &dwProcessId);
  return (GetCurrentProcessId() == dwProcessId);
}
BOOL WINAPI SignalControlCHandler(DWORD ctrlEvent)
{
  switch (ctrlEvent)
  {
    case CTRL_C_EVENT: exit(127);
    default: exit(0);
  }
}