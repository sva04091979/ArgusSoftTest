#include "CMat.h"

string LoadHelp();

CMat::CMat(cv::Mat& mMat) :
	cImg(mMat.clone()) {}

CMat::CMat(cv::Mat& mMat,string& mFile):
	cImg(mMat.clone()),
	cFile(mFile){}

cv::Mat& CMat::Img() { return cImg; }

string& CMat::File() { return cFile; }

void CMat::File(string& mFile) {
	cFile = mFile;
}
