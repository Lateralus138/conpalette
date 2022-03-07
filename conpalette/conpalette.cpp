#include <Windows.h>
#include "Functions.h"
#include <iostream>
#include <vector>
#include <regex>
using namespace std;
int main(int argc, const char* argv[])
{
  SetConsoleCtrlHandler(SignalControlCHandler, true);
  DWORD
    dwProcessIdMain,
    dwProcessIdThis = GetCurrentProcessId();
  HWND conHwnd = GetConsoleWindow();
  GetWindowThreadProcessId(conHwnd, &dwProcessIdMain);
  const bool isOwnConWin = (dwProcessIdThis == dwProcessIdMain);
  const string
    TITLE = "Console Palette",
    TITLEESC = "\x1b]0;" + TITLE + "\007";
  bool
    isOwnWindow = IsOwnWindow();
  auto wait_continue =
    [isOwnWindow]()
  {
    if (isOwnWindow)
    {
      cout << "Press [Enter] to continue... ";
      cin.get();
      cout << '\n';
    }
  };
  const std::regex
    RGX_HELP("^/([hH]|[hH][eE][lL][pP]|\\?)$");
  SetConsoleOutputCP(CP_UTF8);
  SetConsoleCP(CP_UTF8);
  SetConsoleTitleA(TITLE.c_str());
  if (isOwnConWin)
  {
    SetWindowTextA(conHwnd, TITLE.c_str());
  }
  const vector <string> BOX =
  {
    u8"\u250C", u8"\u2500", u8"\u2510", u8"\u2502",
    u8"\u2514", u8"\u2518", u8"\u251C", u8"\u2524"
  };
  const string CR = u8"\u00A9";
  string box_line;
  for (auto i = 0; i < 48; ++i)
  {
    box_line += BOX[1];
  }
  if (argc > 1)
  {
    std::string thisArg;
    for (auto i = 1; i < argc; i++)
    {
      thisArg = argv[i];
      if (std::regex_match(thisArg, RGX_HELP))
      {
        std::cout <<
          '\n' +
          BOX[0] + box_line + BOX[2] + '\n' +
          BOX[3] + "                Console Palette                 " + BOX[3] + '\n' +
          BOX[6] + box_line + BOX[7] + '\n' +
          BOX[3] + " Display the 4bit colors of the current console " + BOX[3] + '\n' +
          BOX[6] + box_line + BOX[7] + '\n' +
          BOX[3] + " conpalette [/H]                                " + BOX[3] + '\n' +
          BOX[6] + box_line + BOX[7] + '\n' +
          BOX[3] + " /h,/HELP,/?     This help screen.              " + BOX[3] + '\n' +
          BOX[6] + box_line + BOX[7] + '\n' +
          BOX[3] + " " + CR + " 2022 Ian Pride - New Pride Software/Services " + BOX[3] + '\n' +
          BOX[4] + box_line + BOX[5] + "\n\n";
        wait_continue();
        return 0;
      }
    }
  }
  cout <<
    '\n' +
    BOX[0] + box_line + BOX[2] + '\n' +
    BOX[3] + "                Console Palette                 " + BOX[3] + '\n' +
    BOX[6] + box_line + BOX[7] + '\n' +
    BOX[3] + " Display the 4bit colors of the current console " + BOX[3] + '\n' +
    BOX[6] + box_line + BOX[7] + '\n' +
    BOX[3] + " Colors 30-37                                   " + BOX[3] + '\n' +
    BOX[3] + "30    31    32    33    34    35    36    37    " + BOX[3] + '\n' +
    BOX[3] + "\x1b[40m      \x1b[41m      \x1b[42m      \x1b[43m      \x1b[44m      \x1b[45m      \x1b[46m      \x1b[47m      \x1b[m" + BOX[3] + '\n' +
    BOX[3] + "\x1b[40m      \x1b[41m      \x1b[42m      \x1b[43m      \x1b[44m      \x1b[45m      \x1b[46m      \x1b[47m      \x1b[m" + BOX[3] + '\n' +
    BOX[6] + box_line + BOX[7] + '\n' +
    BOX[3] + " Colors 90-97                                   " + BOX[3] + '\n' +
    BOX[3] + "90    91    92    93    94    95    96    97    " + BOX[3] + '\n' +
    BOX[3] + "\x1b[100m      \x1b[101m      \x1b[102m      \x1b[103m      \x1b[104m      \x1b[105m      \x1b[106m      \x1b[107m      \x1b[m" + BOX[3] + '\n' +
    BOX[3] + "\x1b[100m      \x1b[101m      \x1b[102m      \x1b[103m      \x1b[104m      \x1b[105m      \x1b[106m      \x1b[107m      \x1b[m" + BOX[3] + '\n' +
    BOX[6] + box_line + BOX[7] + '\n' +
    BOX[3] + " " + CR + " 2022 Ian Pride - New Pride Software/Services " + BOX[3] + '\n' +
    BOX[4] + box_line + BOX[5] + "\n\n";
  wait_continue();
}
