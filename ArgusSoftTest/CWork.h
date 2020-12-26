#pragma once

#include <string>
#include <vector>
#include <map>
#include "CMat.h"
#include "Help.h"

using namespace std;

class CWork {
	map<string, CMat*> cContainer;
	string cWorkName;
	string cPrefix = "[]>";
	CMat* cWork = nullptr;
public:
	~CWork();
	bool Load(vector<string>& mParams);
	bool Store(vector<string>& mParams);
	bool Switch(vector<string>& mParams);
	bool Free(vector<string>& mParams);
	bool Blur(vector<string>& mParams);
	bool Resize(vector<string>& mParams);
	string& Prefix();
private:
	void MakePrefix(string& mName);
	void FreePrefix();
	bool CheckBlurParams(vector<string>& mParams, cv::Size& mSize);
};
