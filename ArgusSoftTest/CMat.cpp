#include "CMat.h"

string LoadHelp();

CMat::CMat(cv::Mat& mMat) :
	cImg(mMat.clone()) {}

cv::Mat& CMat::Img() { return cImg; }
