#pragma once

#include "opencv2/opencv.hpp"

using namespace std;

class CMat {
	cv::Mat cImg;
public:
	CMat(cv::Mat &mMat);
	cv::Mat& Img();
};