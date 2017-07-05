// ewrPosition.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "highgui.h"
#include "cv.h"
#include <iostream>
#include<fstream>
#include <math.h>
#include<math.h> 
#include"opencv2/legacy/legacy.hpp"
#include"opencv2/nonfree/features2d.hpp"

using namespace cv;
using namespace std;
#include "EwmPosition.h"
int main(int argc, _TCHAR* argv[])
{
	TwoDimentionCode ewm;


	CvCapture*capture=cvCaptureFromFile("1.mp4");
	int frameNum=(int)cvGetCaptureProperty(capture,CV_CAP_PROP_FRAME_COUNT);
	cout<<"diyizhen:::"<<frameNum<<endl;
	int num=0;
	IplImage*frame=cvQueryFrame(capture);
	while(1){
	for(int i=0;i<3;i++){
	  frame=cvQueryFrame(capture);
	  if(frame==NULL)
		break;
	}
	if(frame==NULL)
		break;
	num++;
	cout<<"zhen:::"<<num<<endl;
	//IplImage*frame=cvLoadImage("e.jpg");
	//frame = cvLoadImage("e.jpg");
	ewm.getImage(frame);
	ewm.Resize();
	ewm.getFeaturesPoint(ewm.getAfterResizeImage());
	ewm.drawFeaturesPoint(ewm.getAfterResizeImage());
	//ewm.showImage("hello",);
    ewm.imageProceed(ewm.getAfterResizeImage());
//	ewm.showImage("hello",image);
	cvWaitKey(10);
	}
	//cvReleaseImage(&frame);
	system("pause");
	return 0;
}

