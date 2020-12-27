#include "CWork.h"
#include <algorithm>

void MakeParams(string& mParams, vector<string>& mOut, const char mDel);

CWork::~CWork() {
	for_each(cContainer.begin(), cContainer.end(), [] (auto it){
		delete it.second;
		});
}

bool CWork::Load(vector<string>& mParams) {
	bool ret = false;
	switch (mParams.size()) {
	default:
		cout << "wrong params" << endl << LoadHelp() << endl;
		break;
	case 2: {
		cv::Mat mat = cv::imread(mParams[1]);
		if (mat.empty())
			cout << "load error" << endl;
		else {
			auto it = cContainer.insert({ mParams[0],nullptr });
			if (ret=it.second) {
				cWork = new CMat(mat,mParams[1]);
				it.first->second = cWork;
				MakePrefix(mParams[0]);
				cout << "load ok" << endl;
			}
			else
				cout << "name is busy" << endl;
		}
	}
		  break;
	}
	return ret;
}

bool CWork::Store(vector<string> &mParams) {
	bool ret = false;
	auto writer = [](string& name, string& file, CMat* mat) {
		bool ret = false;
		try {
			if (ret = cv::imwrite(file, mat->Img())) {
				cout << name << " save ok" << endl;
				mat->File(file);
			}
			else
				cout << name << " save error" << endl;
		}
		catch (...) {
			cout << name << " save raised an exception" << endl;
		}
		return ret;
	};
	switch (mParams.size()) {
	case 1:
		ret = writer(cWorkName, mParams[0], cWork);
		break;
	case 2: {
		auto find = cContainer.find(mParams[0]);
		if (find == cContainer.end())
			cout << "wrong name" << endl;
		else ret = writer(mParams[0], mParams[1], find->second);
	}
		  break;
	default:
		cout << "wrong params" << endl << StoreHelp() << endl;
		break;
	}
	return ret;
}

bool CWork::Switch(vector<string>& mParams) {
	bool ret = false;
	switch (mParams.size()) {
	default:
		cout << "wrong params" << endl << SwitchHelp() << endl;
		break;
	case 1: {
		auto find = cContainer.find(mParams[0]);
		if (ret = (find != cContainer.end())) {
			MakePrefix(mParams[0]);
			cWork = find->second;
		}
		else
			cout << "wrong name" << endl;
	}
		  break;
	}
	return ret;
}

bool CWork::Free(vector<string> &mParams){
	bool ret = false;
	switch (mParams.size()) {
	default:
		cout << "wrong params" << endl << FreeHelp() << endl;
		break;
	case 0:
		FreePrefix();
		cWork = nullptr;
		cout << "working object free" << endl;
		break;
	case 1: {
		auto find = cContainer.find(mParams[0]);
		if (ret=(find != cContainer.end())) {
			delete find->second;
			cContainer.erase(find);
			if (mParams[0] == cWorkName) {
				FreePrefix();
				cWork = nullptr;
			}
			cout << mParams[0] << " free" << endl;
		}
		else
			cout << "wrong name" << endl;
	}
	}
	return ret;
}

void CWork::List() {
	for (auto& it : cContainer)
		cout << it.first << "\t" << (it.second->File().empty() ? "no file" : it.second->File()) << endl;
}

bool CWork::Blur(vector<string>& mParams) {
	vector<string> params;
	cv::Size blurSize;
	if (mParams.size() > 0) MakeParams(mParams.back(), params, '*');
	if (!CheckBlurParams(params,blurSize)) return false;
	bool ret = false;
	switch (mParams.size()) {
	default:
		cout << "wrong params" << endl << BlurHelp() << endl;
		break;
	case 2:
		if (cWork == nullptr)
			cout << "working object is empty" << endl;
		else {
			auto it = cContainer.insert({ mParams[0],nullptr });
			if (it.second) {
				cv::Mat dst;
				cv::blur(cWork->Img(), dst, blurSize);
				ret = true;
				cWork = new CMat(dst);
				it.first->second = cWork;
				MakePrefix(mParams[0]);
				cout << "blur ok" << endl;
			}
			else
				cout << "name is busy" << endl;
		}
		break;
	case 3: {
		auto it = cContainer.find(mParams[0]);
		if (it == cContainer.end())
			cout << "wrong name" << endl;
		else {
			auto _it = cContainer.insert({ mParams[1],nullptr });
			if (_it.second) {
				cv::Mat dst;
				cv::blur(it->second->Img(), dst, blurSize);
				ret = true;
				cWork = new CMat(dst);
				_it.first->second = cWork;
				MakePrefix(mParams[1]);
				cout << "blur ok" << endl;
			}
			else
				cout << "name is busy" << endl;
		}
		break;
	}
	}
	return ret;
}

bool CWork::Resize(vector<string>& mParams) {
	bool ret = false;
	auto checker = [](cv::Size _size,string _first,string _second) {
		return to_string(_size.width) == _first && to_string(_size.height) == _second;
	};
	switch (mParams.size()) {
	default:
		cout << "wrong params" << endl << ResizeHelp() << endl;
		break;
	case 3: 
		if (cWork == nullptr)
			cout << "working object is empty" << endl;
		else {
			auto it = cContainer.insert({ mParams[0],nullptr });
			if (it.second) {
				cv::Size _size(stoi(mParams[1]), stoi(mParams[2]));
				if (!checker(_size, mParams[1], mParams[2])) {
					cout << "wrong params" << endl << ResizeHelp() << endl;
				}
				else {
					cv::Mat dst;
					cv::resize(cWork->Img(), dst, _size);
					ret = true;
					cWork = new CMat(dst);
					it.first->second = cWork;
					MakePrefix(mParams[0]);
					cout << "resize ok" << endl;
				}
			}
			else
				cout << "name is busy" << endl;
		}
		break;
	case 4: {
		auto it = cContainer.find(mParams[0]);
		if (it == cContainer.end())
			cout << "wrong name" << endl;
		else {
			auto _it = cContainer.insert({ mParams[1],nullptr });
			if (_it.second) {
				cv::Size _size(stoi(mParams[2]), stoi(mParams[3]));
				if (!checker(_size, mParams[2], mParams[3])) {
					cout << "wrong params" << endl << ResizeHelp() << endl;
				}
				else {
					cv::Mat dst;
					cv::resize(it->second->Img(), dst, _size);
					ret = true;
					cWork = new CMat(dst);
					_it.first->second = cWork;
					MakePrefix(mParams[1]);
					cout << "resize ok" << endl;
				}
			}
			else
				cout << "name is busy" << endl;
		}
	}
		  break;
	}
	return ret;
}

string& CWork::Prefix() { return cPrefix; }

void CWork::MakePrefix(string& mName) {
	cWorkName = mName;
	cPrefix = "[" + mName + "]>";
}

void CWork::FreePrefix() {
	cWorkName.clear();
	cPrefix = "[]>";
}

bool CWork::CheckBlurParams(vector<string>& mParams, cv::Size& mSize) {
	bool ret = true;
	if (ret = !mParams.empty() && mParams.size() < 3) {
		auto x = stoi(mParams[0]);
		if (ret = to_string(x) == mParams[0]) {
			auto y = x;
			if (mParams.size() == 2) {
				y = stoi(mParams[1]);
				ret = to_string(y) == mParams[1];
			}
			if (ret) mSize = { x,y };
		}
	}
	if (!ret)
		cout << "wrong params" << endl << BlurHelp() << endl;
	return ret;
}