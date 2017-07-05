#include "stdafx.h"
#include "EwmPosition.h"
#include "highgui.h"
#include "cv.h"
#include <iostream>
#include<fstream>
#include <math.h>
#include<math.h> 
#include"opencv2/legacy/legacy.hpp"
#include"opencv2/nonfree/features2d.hpp"
#include<string.h>
#include "windows.h"
using namespace cv;
using namespace std;
#define SIZE1 6
int fg=0;
CvPoint item0,item1,item2,item3;
void TwoDimentionCode::getImage(IplImage*src){
	srcImage=Mat(src);
}
void TwoDimentionCode::getFeaturesPoint(Mat &s){
	detector.detect(s,keypoints);
}
void TwoDimentionCode::drawFeaturesPoint(Mat &srcImage){
//	cout<<srcImage.height<<endl;
	drawKeypoints(srcImage,        // 原始图像
				keypoints,                  // 关键点容器
				srcImage,                      // 结果图像
				Scalar(255, 0, 0),  // 关键点颜色
			2); // 绘制标志
	imwrite("m.png",srcImage);
	//imshow("???",srcImage);
	waitKey(1);
}
void on_mouse(int event,int x,int y,int flags,void *ustc)//event鼠标事件代号，x,y鼠标坐标，flags拖拽和键盘操作的代号  
{  
    static Point pre_pt = (-1,-1);//初始坐标  
    static Point cur_pt = (-1,-1);//实时坐标  
    char temp[16];  
    if (event == CV_EVENT_LBUTTONDOWN)//左键按下，读取初始坐标，并在图像上该点处划圆  
    {  
       // org.copyTo(img);//将原始图片复制到img中  
        sprintf(temp,"(%d,%d)",x,y);  
        pre_pt = Point(x,y);  
        //putText(img,temp,pre_pt,FONT_HERSHEY_SIMPLEX,0.5,Scalar(0,0,0,255),1,8);//在窗口上显示坐标  
		 //circle(img,pre_pt,2,Scalar(255,0,0,0),CV_FILLED,CV_AA,0);//划圆  
		//cout<<"起始坐标："<<x<<","<<y<<endl;
		if(x>item0.x&&x<item1.x&&y>item0.y&&y<item1.y)
		fg=1;
		if (x>item2.x&&x<item3.x&&y>item2.y&&y < item3.y)
			fg = 2;
		
        //imshow("img",img);  
		//cvWaitKey(0);
    }  
   
        
    
}
void TwoDimentionCode::showImage(string name,Mat image){
	imshow(name,image);
	waitKey();
}
TwoDimentionCode::TwoDimentionCode(){
      FastFeatureDetector::FastFeatureDetector(40,true);
}
void TwoDimentionCode::imageProceed(Mat srcImage){
	cout << "flag0" << endl;
	IplImage *temp;
	CvFont font;
	cvInitFont(&font, CV_FONT_HERSHEY_SIMPLEX, 0.4, 0.4, 1, 1, 8);
	IplImage*src=&IplImage(srcImage);
	unsigned char*pixel=NULL;
	unsigned char pixelr=0,pixelg=0,pixelb=0;
	IplImage *bwImage = cvCreateImage(cvGetSize(src), src->depth, 1);


    for(int i=0;i<src->height;i++)
		for(int j=0;j<src->width;j++){
			pixel=(unsigned char*)src->imageData+i*src->widthStep+j*3;
			pixelb=pixel[0];
			pixelg=pixel[1];
			pixelr=pixel[2];

			if (pixelb>238&&pixelg<15&&pixelr<15){
					*((unsigned char*)bwImage->imageData + i*bwImage->widthStep + j) = 255;
				}
				else {
					*((unsigned char*)bwImage->imageData + i*bwImage->widthStep + j) = 0;
				}
		}
		
		Mat m(bwImage);
		Mat element = getStructuringElement(MORPH_RECT, Size(3, 3));
		//erode(m,m,element);
		//element = getStructuringElement(MORPH_RECT, Size(5, 5));
		dilate(m, m, element);
		dilate(m, m, element);
		erode(m,m,element); 
		//erode(m,m,element); 
		cvSmooth(bwImage,bwImage,CV_MEDIAN);
		imshow("therhold",m);
		IplImage *show = cvCreateImage(cvGetSize(src), src->depth, 3);
		const char * data = NULL;
		const char * blackboard = NULL;
		const char * door = NULL;
		CvMemStorage *storage1 = cvCreateMemStorage(0);
		CvSeq * seq1 = cvCreateSeq(CV_SEQ_ELTYPE_POINT, sizeof(CvSeq), sizeof(CvPoint), storage1);
		CvSeq * tempSeq1 = cvCreateSeq(CV_SEQ_ELTYPE_POINT, sizeof(CvSeq), sizeof(CvPoint), storage1);
		temp = &IplImage(this->srcImage);
		cvResize(temp, show);
		int cnt=0;
		int count = cvFindContours(bwImage, storage1, &seq1);//返回轮廓的数目 

		for (tempSeq1 = seq1; tempSeq1 != NULL; tempSeq1 = tempSeq1->h_next)
		{
			double Area = cvContourArea(tempSeq1);
			CvRect Rect = cvBoundingRect(tempSeq1, 1);
			CvPoint2D32f point[4];
			CvBox2D box1 = cvMinAreaRect2(tempSeq1, 0);
			cvBoxPoints(box1, point);
			double area = Rect.width*Rect.height;
			double radio_a = Area/area;
			double radio = (double)Rect.width / Rect.height;
			
			//cout<<"AREA"<<Area/A<<endl;
			CvPoint rect_fast_x,rect_fast_y;
			rect_fast_x.x = Rect.x - Rect.width / 2;
			rect_fast_x.y = Rect.y - Rect.height / 2;
			rect_fast_y.x = Rect.x + Rect.width * 3 / 2;
			rect_fast_y.y = Rect.y + Rect.height * 3 / 2;
			CvPoint x,y;
			x.x = SIZE1*Rect.x - SIZE1*Rect.width / 2;
			x.y = SIZE1*Rect.y - SIZE1*Rect.height / 2;
			y.x = SIZE1*Rect.x + SIZE1*Rect.width * 3 / 2;
			y.y = SIZE1*Rect.y + SIZE1*Rect.height * 3 / 2;
			
			CvRect rect_ecode;
			rect_ecode.x = x.x;
			rect_ecode.y = x.y;
			rect_ecode.width = y.x - x.x;
			rect_ecode.height = y.y - x.y;
			
			if (radio>0.7&&radio<1.2&&radio_a>0.5&&area>100&&area<8000)
			{
				
				
				
	            
				cvRectangle(src,rect_fast_x,rect_fast_y, CV_RGB(255, 0, 0), 1, 8, 0);
				cvShowImage("fast",src);
				cvSetImageROI(temp, rect_ecode);
				int flag = 0;
				
				data = recognize(temp,flag);
				

				cvResetImageROI(temp);
				
				if (flag == 1){
						cnt++;
						
					if(data[0] == 'b'){
					
						item0.x=Rect.x-15*Rect.width;
						if(item0.x<0)item0.x=0;
						item0.y=Rect.y-2*Rect.height;
						if(item0.y<0)item0.y=0;
						item1.x=Rect.x+2*Rect.width;
						if(item1.x>show->width)item1.x=show->width;
						item1.y=Rect.y+8*Rect.height;
						if(item1.y>show->height)item1.y=show->height;
					   cvRectangle(show,item0,item1, CV_RGB(0, 255, 0), 2, 8, 0);
					   cvPutText(show, data, cvPoint(Rect.x-3*Rect.width, Rect.y-Rect.height/6), &font, CV_RGB(255, 0, 0));
					   blackboard = data;
					  if(cnt>1)break;
					}
					if(data[0] == 'd'){
					
						item2.x=Rect.x-6*Rect.width;
						if(item2.x<0)item2.x=0;
						item2.y=Rect.y-4*Rect.height;
						if(item2.y<0)item2.y=0;
						item3.x=Rect.x+1*Rect.width;
						if(item3.x>show->width)item3.x=show->width;
						item3.y=Rect.y+12*Rect.height;
						if(item3.y>show->height)item3.y=show->height;
					   cvRectangle(show,item2,item3, CV_RGB(0, 255, 0), 2, 8, 0);
					   cvPutText(show, data, cvPoint(Rect.x-3*Rect.width, Rect.y-Rect.height/6), &font, CV_RGB(255, 0, 0));
					   door = data;
					  if(cnt>1)break;
					}
					//break;
				}
				//cout<<"find"<<endl;
				
			}
		}
		
		cvNamedWindow("find",1);
		setMouseCallback("find",on_mouse,0);
		cvShowImage("find", show);
		cvWaitKey(1);
		
		if(fg == 1){
		
		//MessageBoxA(NULL,blackboard,blackboard,MB_OK);
		ShellExecuteA(NULL,NULL,blackboard,NULL,NULL,SW_SHOWNA);
		}
		if (fg == 2){
		//MessageBoxA(NULL, door, door, MB_OK);
		ShellExecuteA(NULL, NULL, "door.html", NULL, NULL, SW_SHOWNA);
		}
		cout << "flag1" << endl;
		fg = 0;
	
		
	

}
void TwoDimentionCode::Resize(){
	Size size(srcImage.cols/SIZE1,srcImage.rows/SIZE1);
	resize(srcImage,afterResize,size,(0,0),(0,0),1);
}
Mat TwoDimentionCode::getSrcImage(){
	return this->srcImage;
}
Mat TwoDimentionCode::getAfterResizeImage(){
	return this->afterResize;
}
