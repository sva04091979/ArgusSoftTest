#pragma once

using namespace std;

string CommonHelp();
string CommandList();
string LoadHelp(bool isSpace=true);
string StoreHelp(bool isDefault = true, bool isSpace = true);
string SwitchHelp(bool isSpace = true);
string ListHelp();
string FreeHelp(bool isSpace = true);
string BlurHelp(bool isDefault = true, bool isSpace = true);
string ResizeHelp(bool isDefault = true, bool isSpace = true);
string HelpHelp();
string ExitHelp();
