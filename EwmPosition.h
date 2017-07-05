#include "highgui.h"
#include "cv.h"
#include <iostream>
#include<fstream>
#include <math.h>
#include<math.h> 
#include"opencv2/legacy/legacy.hpp"
#include"opencv2/nonfree/features2d.hpp"
#include<string.h>
using namespace cv;
using namespace std;
class TwoDimentionCode{
private:
	Mat srcImage;
	Mat afterResize;
	vector<KeyPoint> keypoints;
	//GoodFeaturesToTrackDetector detector;
	FastFeatureDetector detector;
public:
	TwoDimentionCode();
	void getImage(IplImage*);
	void getFeaturesPoint(Mat&);
	void drawFeaturesPoint(Mat&);
	void showImage(string,Mat);
	Mat getSrcImage();
	Mat getAfterResizeImage();
public:
	void imageProceed(Mat);
	void Resize();
	const char * recognize(IplImage*,int&);
};