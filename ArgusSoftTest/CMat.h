#pragma once

#include "opencv2/opencv.hpp"
#include <string>

using namespace std;

class CMat {
	cv::Mat cImg;
	string cFile;
public:
	CMat(cv::Mat &mMat);
	CMat(cv::Mat& mMat,string& mFile);
	cv::Mat& Img();
	string& File();
	void File(string& mFile);
};