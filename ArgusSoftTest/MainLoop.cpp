#include "MainLoop.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <map>
#include <vector>
#include "opencv2/opencv.hpp"

using namespace std;

struct SImg {
	cv::Mat img;
	cv::Mat dst;
};

map < string, SImg > matList;
string prefix;
SImg* working=nullptr;

enum class ECommand
{
	Load,
	Store,
	Switch,
	Free,
	Blur,
	Resize,
	Help,
	Exit,
	Error
};

ECommand GetCommand(string&);
void LoadEvent(string&);
void StoreEvent(string&);
void SwitchEvent(string&);
void FreeEvent(string&);
void BlurEvent(string& s) { cout << "blur: " << s << endl; }
void ResizeEvent(string& s) { cout << "resize: " << s << endl; }
void HelpEvent(string& s) { cout << "help: " << s << endl; }
void ExitEvent() { cout << "exit" << endl; }
void ErrorEvent(string& s) { cout << "error" << endl; }
void MakeParams(vector<string>&);
string LoadHelp();
string StoreHelp();

void MainLoop() {
	prefix.clear();
	bool isWork = true;
	while (isWork) {
		string command;
		cout << "[" << prefix << "]";
		getline(cin, command);
		transform(command.begin(), command.end(), command.begin(), tolower);
		switch (GetCommand(command)) {
		case:: ECommand::Load:
			LoadEvent(command);
			break;
		case ECommand::Store :
			StoreEvent(command);
			break;
		case ECommand::Switch:
			SwitchEvent(command);
			break;
		case ECommand::Free:
			FreeEvent(command);
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
	matList.clear();
}

ECommand GetCommand(string& mCommand) {
	static map<string, ECommand> commands = {
		{"load",ECommand::Load},
		{"ld",ECommand::Load},
		{"store",ECommand::Store},
		{"s",ECommand::Store},
		{"switch",ECommand::Switch},
		{"blur",ECommand::Blur},
		{"resize",ECommand::Resize},
		{"help",ECommand::Help},
		{"h",ECommand::Help},
		{"exit",ECommand::Exit},
		{"quit",ECommand::Exit},
		{"q",ECommand::Exit}
	};
	auto pos = mCommand.find(" ");
	string command = pos==string::npos?mCommand:mCommand.substr(0, pos);
	auto find = commands.find(command);
	if (find == commands.end()) return ECommand::Error;
	if (pos!=string::npos) pos= mCommand.find_first_not_of(" ", pos);
	if (pos == string::npos) mCommand.clear();
	else mCommand.erase(0, pos);
	return find->second;
}

void LoadEvent(string& mParam) {
	vector<string> params;
	MakeParams(params);
	switch (params.size()) {
	default:
		cout << "wrong params" << endl << LoadHelp() << endl;
		break;
	case 2: {
		cv::Mat obj = cv::imread(params[0]);
		if (obj.empty()) 
			cout << "load error" << endl;
		else if (matList.find(params[1]) == matList.end())
			cout << "name is busy" << endl;
		else {
			prefix = params[1];
			auto ret = matList.insert({ params[1],SImg{obj.clone(),obj.clone() } });
			if (!ret.second) 
				cout << "map insert error" << endl;
			else {
				cout << "load ok" << endl;
				working = &ret.first->second;
			}
		}
	}
	}
}

void StoreEvent(string& mParam) {
	vector<string> params;
	MakeParams(params);
	switch (params.size()) {
	case 1:
		if (cv::imwrite(params[0], working->dst))
			cout << "save ok" << endl;
		else
			cout << "save error" << endl;
		break;
	case 2: {
		auto ret = matList.find(params[0]);
		if (ret == matList.end())
			cout << "wrong name" << endl;
		else if (cv::imwrite(params[1], ret->second.dst))
			cout << "save ok" << endl;
		else
			cout << "save error" << endl;
	}
		  break;
	default:
		cout << "wrong params" << endl << StoreHelp() << endl;
		break;
	}
}

void SwitchEvent(string& mParam) {
	vector<string> params;
	MakeParams(params);
	switch (params.size()) {
	default:
		cout << "wrong params" << endl << LoadHelp() << endl;
		break;
	case 1: {
		auto ret = matList.find(params[0]);
		if (ret == matList.end())
			cout << "wrong name" << endl;
		else {
			prefix = ret->first;
			working = &ret->second;
		}
	}
	}
}