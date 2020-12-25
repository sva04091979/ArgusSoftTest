#include "MainLoop.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <map>
#include "opencv2/opencv.hpp"

using namespace std;

map<string, cv::Mat> list;

enum class ECommand
{
	Load,
	Store,
	Blur,
	Resize,
	Help,
	Exit,
	Error
};

ECommand GetCommand(string&);
void LoadEvent(string& s) { cout << "load: " << s<< endl; }
void StoreEvent(string& s) { cout << "store: " << s<< endl; }
void BlurEvent(string& s) { cout << "blur: " << s << endl; }
void ResizeEvent(string& s) { cout << "resize: " << s << endl; }
void HelpEvent(string& s) { cout << "help: " << s << endl; }
void ExitEvent() { cout << "exit" << endl; }
void ErrorEvent(string& s) { cout << "error" << endl; }

void MainLoop() {
	bool isWork = true;
	while (isWork) {
		string command;
		getline(cin, command);
		switch (GetCommand(command)) {
		case:: ECommand::Load:
			LoadEvent(command);
			break;
		case ECommand::Store :
			StoreEvent(command);
			break;
		case ECommand::Blur:
			BlurEvent(command);
			break;
		case ECommand::Resize:
			ResizeEvent(command);
			break;
		case ECommand::Help:
			HelpEvent(command);
			break;
		case ECommand::Exit:
			ExitEvent();
			return;
		case ECommand::Error:
			ErrorEvent(command);
			break;
		}
	}
}

ECommand GetCommand(string& mCommand) {
	static map<string, ECommand> commands = {
		{"load",ECommand::Load},
		{"ld",ECommand::Load},
		{"store",ECommand::Store},
		{"s",ECommand::Store},
		{"blur",ECommand::Blur},
		{"resize",ECommand::Resize},
		{"help",ECommand::Help},
		{"h",ECommand::Help},
		{"exit",ECommand::Exit},
		{"quit",ECommand::Exit},
		{"q",ECommand::Exit}
	};
	auto pos = mCommand.find(" ");
	auto command = pos==string::npos?mCommand:mCommand.substr(0, pos);
	transform(command.begin(), command.end(), command.begin(), tolower);
	auto find = commands.find(command);
	if (find == commands.end()) return ECommand::Error;
	if (pos!=string::npos) pos= mCommand.find_first_not_of(" ", pos);
	if (pos == string::npos) mCommand.clear();
	else mCommand.erase(0, pos);
	return find->second;
}