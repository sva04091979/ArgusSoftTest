#include "MainLoop.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <map>
#include <vector>
#include "opencv2/opencv.hpp"
#include "CWork.h"

using namespace std;

enum class ECommand
{
	Load,
	Store,
	Switch,
	Dir,
	Free,
	Blur,
	Resize,
	Help,
	Exit,
	Error
};

void HelpEvent(vector<string>&);
void ErrorEvent();
void ExitEvent() {  }
pair<ECommand, vector<string>> MakeCommand(string&);

map<string, ECommand> gCommands = {
	{"load",ECommand::Load},
	{"ld",ECommand::Load},
	{"store",ECommand::Store},
	{"s",ECommand::Store},
	{"switch",ECommand::Switch},
	{"dir",ECommand::Dir},
	{"free",ECommand::Free},
	{"blur",ECommand::Blur},
	{"resize",ECommand::Resize},
	{"help",ECommand::Help},
	{"h",ECommand::Help},
	{"exit",ECommand::Exit},
	{"quit",ECommand::Exit},
	{"q",ECommand::Exit}
};

void MainLoop() {
	CWork work;
	while (true) {
		string input;
		cout << work.Prefix();
		getline(cin, input);
		transform(input.begin(), input.end(), input.begin(), tolower);
		auto in = MakeCommand(input);
		switch (in.first) {
		case:: ECommand::Load:
			work.Load(in.second);
			break;
		case ECommand::Store :
			work.Store(in.second);
			break;
		case ECommand::Switch:
			work.Switch(in.second);
			break;
		case ECommand::Dir:
			work.Dir();
			break;
		case ECommand::Free:
			work.Free(in.second);
			break;
		case ECommand::Blur:
			work.Blur(in.second);
			break;
		case ECommand::Resize:
			work.Resize(in.second);
			break;
		case ECommand::Help:
			HelpEvent(in.second);
			break;
		case ECommand::Exit:
			ExitEvent();
			return;
		case ECommand::Error:
			ErrorEvent();
			break;
		}
	}
}

void HelpEvent(vector<string>& mParams) {
	if (mParams.size() != 1)
		cout << CommonHelp() << endl;
	else {
		auto it = gCommands.find(mParams[0]);
		if (it == gCommands.end())
			cout << CommonHelp() << endl;
		else switch (it->second) {
		default:
			cout<<CommonHelp()<<endl;
			break;
		case::ECommand::Load:
			cout<<LoadHelp()<<endl;
			break;
		case ECommand::Store:
			cout<<StoreHelp<<endl;
			break;
		case ECommand::Switch:
			cout<<SwitchHelp()<<endl;
			break;
		case ECommand::Free:
			cout<<FreeHelp()<<endl;
			break;
		case ECommand::Blur:
			cout<<BlurHelp()<<endl;
			break;
		case ECommand::Resize:
			cout<<ResizeHelp()<<endl;
			break;
		}
	}
}

void MakeParams(string& mParams, vector<string>& mOut) {
	auto it = mParams.begin();
	while (it != mParams.end()) {
		string param;
		while (it != mParams.end() && *it != ' ') {
			param += *it;
			++it;
		}
		mOut.push_back(param);
		while (it!=mParams.end()&&*it == ' ') ++it;
	}
}

void MakeParams(string& mParams, vector<string>& mOut, const char mDel) {
	auto it = mParams.begin();
	while (it != mParams.end()) {
		string param;
		while (it != mParams.end() && *it != mDel) {
			if (*it != ' ') param += *it;
			++it;
		}
		if (it != mParams.end()) ++it;
		mOut.push_back(param);
	}
}

pair<ECommand, vector<string>> MakeCommand(string& mInput) {
	pair<ECommand, vector<string>> ret;
	auto pos = mInput.find(" ");
	string command = mInput.substr(0, pos);
	auto find = gCommands.find(command);
	if (find == gCommands.end()) 
		ret.first = ECommand::Error;
	else {
		ret.first = find->second;
		if (pos != string::npos &&
			(pos = mInput.find_first_not_of(' ', pos)) != string::npos) {
			string params = mInput.substr(pos);
			MakeParams(params,ret.second);
		}
	}
	return ret;
}

void ErrorEvent() {
	cout << "wrong command" << endl << CommonHelp() << endl;
}
