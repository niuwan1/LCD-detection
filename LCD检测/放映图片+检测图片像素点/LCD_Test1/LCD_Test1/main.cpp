      #include <iostream>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cv.h>

#include<windows.h>

using namespace std;
using namespace cv;

//int main()
//{
//
//	/*Mat src = imread("4.jpg",1);
//	if (!src.data)	
//	{
//		printf("err");
//	}
//
//	Mat imgROI;
//
//	src(Rect(20, 20, 480, 480)).copyTo(imgROI);
//	imwrite("roi.jpg", imgROI);
//	cv::namedWindow("ROI");
//	cv::imshow("ROI", imgROI);*/
//
//	//Mat img2(src.rows, src.cols, CV_8UC3);
//
//	////设置感兴趣区域,拷贝
//	//src(Rect(10, 15, 150, 250)).copyTo(img2);
//
//	////显示
//	//imshow("img1", src);
//	//imshow("img2", img2);
//	//waitKey(0);
//
//
//	//CvCapture *capture;
//	//capture = cvCreateCameraCapture(0);   //0为外部摄像头的ID，1为笔记本内置摄像头的ID
//
//	//assert(capture != NULL);
//
//	//IplImage *frame;
//	//cvNamedWindow("camera", 1);
//
//	//int n = 1, m = 5;
//	//char *cstr = new char[30];
//	////char cstr[20];
//
//	//while (m--)
//	//{
//	//	frame = cvQueryFrame(capture);
//	//	if (!frame)
//	//	{
//	//		printf("err\n");
//	//	}
//	//	//break;
//
//	//	sprintf(cstr, "%d%s", n++, ".jpg");
//
//	//	cvShowImage("camera", frame);
//
//	//	cvSaveImage(cstr, frame);
//
//	//	/*if (cvWaitKey(33) >= 0)
//	//	break;*/
//	//	cvWaitKey(0);
//	//}
//	//cvReleaseCapture(&capture);
//	////cvReleaseImage(&frame);
//	//cvDestroyWindow("camera");
//
//
//	IplImage *src = cvLoadImage("77.bmp", 1);
//	if (!src)
//	{
//		printf("err");
//	}
//
//	//cvSetImageROI(src, cvRect(300, 400, 3000, 1500));
//	cvSetImageROI(src, cvRect(1400, 1000, 300, 300));
//
//	//感兴趣区域大小一样
//	IplImage *imgROI = cvCreateImage(cvGetSize(src), src->depth, src->nChannels);
//	//拷贝
//	cvCopy(src, imgROI, NULL);
//
//	//重置
//	cvResetImageROI(imgROI);
//	cvSaveImage("5_ROI.jpg", imgROI);
//
//	cvNamedWindow("src");
//	cvNamedWindow("imgROI");
//	cvShowImage("src", src);
//	cvShowImage("imgROI", imgROI);
//	
//
//	IplImage* rImg = cvCreateImage(cvGetSize(imgROI), IPL_DEPTH_8U, 1);
//
//	IplImage* gImg = cvCreateImage(cvGetSize(imgROI), IPL_DEPTH_8U, 1);
//
//	IplImage* bImg = cvCreateImage(cvGetSize(imgROI), IPL_DEPTH_8U, 1);
//
//	cvSplit(src, bImg, gImg, rImg,0);
//
//	cvNamedWindow("rImg");
//	cvShowImage("rImg", rImg);
//	cvNamedWindow("gImg");
//	cvShowImage("gImg", gImg);
//	cvNamedWindow("bImg");
//	cvShowImage("bImg", bImg);
//
//	
//	CvScalar rgb=cvGet2D(imgROI, 10, 10);    //坐标（10，10）处的像素值
//	cout << "r:" << rgb.val[2] << endl;
//	cout << "g:" << rgb.val[1] << endl;
//	cout << "b:" << rgb.val[0] << endl;
//
//
//	//CvScalar cvAvg(const CvArr* arr, const CvArr* mask = NULL);
//	CvScalar avgChannels = cvAvg(imgROI);   //先求出该图像的平均像素值，再分离到红绿蓝三通道
//
//	double avgB = avgChannels.val[0];
//
//	double avgG = avgChannels.val[1];
//
//	double avgR = avgChannels.val[2];
//
//	cout << "r:" << avgR << endl;
//	cout << "g:" << avgG << endl;
//	cout << "b:" << avgB << endl;
//
//	int num_Red = 0;        //红色图片噪点个数
//	int num_Green = 0;	    //绿色图片噪点个数
//	int num_Blue = 0;		//蓝色图片噪点个数
//	int num_White = 0;		//白色图片噪点个数
//	int num_Black = 0;		//黑色图片噪点个数
//
//
//	if (avgR > 240 && avgG < 60 && avgB < 60)		//检测红色图片噪点个数
//	{
//		cout << "此图片为红色" << endl;
//		cv::Mat img = cv::Mat(imgROI);
//		for (int i = 0; i<img.rows; i++)			//检测每个像素
//		{
//			for (int j = 0; j<img.cols; j++)
//			{
//				
//				if (img.at<Vec3b>(i, j)[2] < 240)
//				{
//					num_Red++;
//					circle(img, cv::Point(i,j), 1, cv::Scalar(0, 0, 0), 1);
//				}
//			}
//		}
//		cvNamedWindow("draw_r");
//		imshow("draw_r", img);
//		cout << "红色图片噪点个数：" << num_Red << endl;
//		if (num_Red>200)
//		{
//			cout << "该图片不合格！！！" << endl;
//		}
//		cout << "width:" << img.rows << endl; 
//		cout << "height:"<< img.cols << endl;
//	}
//
//
//	if (avgR < 20 && avgG > 240 && avgB < 20)		//检测绿色图片噪点个数
//	{
//		cout << "此图片为绿色" << endl;
//		cv::Mat img = cv::Mat(imgROI);
//		for (int i = 0; i<img.rows; i++)
//		{
//			for (int j = 0; j<img.cols; j++)
//			{
//
//				if (img.at<Vec3b>(i, j)[1] < 253)
//				{
//					num_Green++;
//					circle(img, cv::Point(i, j), 3, cv::Scalar(0, 0, 0), 1);
//				}
//			}
//		}
//		cvNamedWindow("draw_g");
//		imshow("draw_g", img);
//		cout << "绿色图片噪点个数：" << num_Green << endl;
//		if (num_Green > 200)
//		{
//			cout << "该图片不合格！！！" << endl;
//		}
//		cout << "width:" << img.rows << endl;
//		cout << "height:" << img.cols << endl;
//	}
//
//
//	if (avgR < 20 && avgG < 20 && avgB > 240)		//检测蓝色图片噪点个数
//	{
//		cout << "此图片为蓝色" << endl;
//		cv::Mat img = cv::Mat(imgROI);
//		for (int i = 0; i<img.rows; i++)
//		{
//			for (int j = 0; j<img.cols; j++)
//			{
//
//				if (img.at<Vec3b>(i, j)[0] < 252)
//				{
//					num_Blue++;
//					circle(img, cv::Point(i, j), 3, cv::Scalar(0, 0, 0), 1);
//				}
//			}
//		}
//		cvNamedWindow("draw_b");
//		imshow("draw_b", img);
//		cout << "蓝色图片噪点个数：" << num_Blue << endl;
//		if (num_Blue > 200)
//		{
//			cout << "该图片不合格！！！" << endl;
//		}
//		cout << "width:" << img.rows << endl;
//		cout << "height:" << img.cols << endl;
//	}
//
//
//	if (avgR > 100 && avgG > 100 && avgB > 100)		//检测白色图片噪点个数
//	{
//		cout << "此图片为白色" << endl;
//		cv::Mat img = cv::Mat(imgROI);
//		for (int i = 0; i<img.rows; i++)
//		{
//			for (int j = 0; j<img.cols; j++)
//			{
//
//				if (img.at<Vec3b>(i, j)[0] < 100 || img.at<Vec3b>(i, j)[1] < 100 || img.at<Vec3b>(i, j)[2] < 100)
//				{
//					num_White++;
//					circle(img, cv::Point(i, j), 3, cv::Scalar(0, 0, 0), 1);
//				}
//			}
//		}
//		cvNamedWindow("draw_w",0);
//		cvResizeWindow("draw_w", 300, 300);
//		imshow("draw_w", img);
//		cout << "白色图片噪点个数：" << num_White << endl;
//		if (num_White > 200)
//		{
//			cout << "该图片不合格！！！" << endl;
//		}
//		cout << "width:" << img.rows << endl;
//		cout << "height:" << img.cols << endl;
//	}
//
//
//	if (avgR < 20 && avgB < 20 && avgG < 20)		//检测黑色图片噪点个数
//	{
//		cout << "此图片为黑色" << endl;
//		cv::Mat img = cv::Mat(imgROI);
//		for (int i = 0; i<img.rows; i++)
//		{
//			for (int j = 0; j<img.cols; j++)
//			{
//
//				if (img.at<Vec3b>(i, j)[0] > 1 || img.at<Vec3b>(i, j)[1] > 1 || img.at<Vec3b>(i, j)[2] > 1)
//				{
//					num_Black++;
//					circle(img, cv::Point(i, j), 3, cv::Scalar(255, 255, 255), 1);
//				}
//			}
//		}
//		cvNamedWindow("draw_black");
//		imshow("draw_black", img);
//		cout << "黑色图片噪点个数：" << num_Black << endl;
//		if (num_Black > 200)
//		{
//			cout << "该图片不合格！！！" << endl;
//		}
//		cout << "width:" << img.rows << endl;
//		cout << "height:" << img.cols << endl;
//	}
//
//
//
//	
//
//
//
//
//
//
//
//
//	//if (avgR > 240 && avgB < 20 && avgG < 20)		//检测红色图片噪点个数
//	//{
//	//	cout << "此图片为红色" << endl;
//	//	cv::Mat img = cv::Mat(imgROI);
//	//	cv::MatIterator_<cv::Vec3b> it = img.begin<cv::Vec3b>();
//	//	cv::MatIterator_<cv::Vec3b> itend = img.end<cv::Vec3b>();
//	//	for (; it!=itend; it++)
//	//	{
//	//		if ((*it)[2]<255)
//	//		{
//	//			num_Red++;
//	//			circle(img, cv::Point(), 2, cv::Scalar(0, 0, 0),2);
//	//		}			
//	//	}
//	//	cvNamedWindow("draw_r");
//	//	imshow("draw_r", img);
//	//	cout << "红色图片噪点个数：" << num_Red << endl;
//	//}
//	//
//
//	//if (avgR < 20 && avgB < 20 && avgG > 240)		//检测绿色图片噪点个数
//	//{
//	//	cout << "此图片为绿色" << endl;
//	//	cv::Mat img = cv::Mat(imgROI);
//	//	cv::MatIterator_<cv::Vec3b> it = img.begin<cv::Vec3b>();
//	//	cv::MatIterator_<cv::Vec3b> itend = img.end<cv::Vec3b>();
//	//	for (; it != itend; it++)
//	//	{
//	//		if ((*it)[1]<253)
//	//		{
//	//			num_Green++;
//	//		}
//	//	}
//	//	cout << "绿色图片噪点个数：" << num_Green << endl;
//	//}
//	//
//
//	//if (avgR < 20 && avgB > 240 && avgG < 20)		//检测蓝色图片噪点个数
//	//{
//	//	cout << "此图片为蓝色" << endl;
//	//	cv::Mat img = cv::Mat(imgROI);
//	//	cv::MatIterator_<cv::Vec3b> it = img.begin<cv::Vec3b>();
//	//	cv::MatIterator_<cv::Vec3b> itend = img.end<cv::Vec3b>();
//	//	for (; it != itend; it++)
//	//	{
//	//		if ((*it)[0]<252)
//	//		{
//	//			num_Blue++;
//	//		}
//	//	}
//	//	cout << "蓝色图片噪点个数：" << num_Blue << endl;
//	//}
//	//
//
//	//if (avgR > 240 && avgB > 240 && avgG > 240)		//检测白色图片噪点个数
//	//{
//	//	cout << "此图片为白色" << endl;
//	//	cv::Mat img = cv::Mat(imgROI);
//	//	cv::MatIterator_<cv::Vec3b> it = img.begin<cv::Vec3b>();
//	//	cv::MatIterator_<cv::Vec3b> itend = img.end<cv::Vec3b>();
//	//	for (; it != itend; it++)
//	//	{
//	//		if ((*it)[0]<255 || (*it)[1]<255 || (*it)[2]<255)
//	//		{
//	//			num_White++;
//	//		}
//	//	}
//	//	cout << "白色图片噪点个数：" << num_White << endl;
//	//}
//	//
//
//	//if (avgR < 20 && avgB < 20 && avgG < 20)		//检测黑色图片噪点个数
//	//{
//	//	cout << "此图片为黑色" << endl;
//	//	cv::Mat img = cv::Mat(imgROI);
//	//	cv::MatIterator_<cv::Vec3b> it = img.begin<cv::Vec3b>();
//	//	cv::MatIterator_<cv::Vec3b> itend = img.end<cv::Vec3b>();
//	//	for (; it != itend; it++)
//	//	{
//	//		if ((*it)[0]>3 || (*it)[1]>3 || (*it)[0]>3)
//	//		{
//	//			num_Black++;
//	//		}
//	//	}
//	//	cout << "黑色图片噪点个数：" << num_Black << endl;
//	//}
//	
//	cvReleaseImage(&src);
//	cvReleaseImage(&imgROI);
//	cvReleaseImage(&rImg);
//	cvReleaseImage(&gImg);
//	cvReleaseImage(&bImg);
//	//cvReleaseImage(&src);
//	cv::waitKey(0);
//
//
//
//
//}




//void main()
//{
//
//	IplImage *src = cvLoadImage("77.bmp", 0);
//	if (!src)
//	{
//		printf("err");
//	}
//	cvNamedWindow("src");
//	cvShowImage("src", src);
//
//	double fScale = 0.5;      //缩放倍数  
//	CvSize Size;              //目标图像尺寸  
//
//	//计算目标图像大小  
//	Size.width = src->width * fScale;
//	Size.height = src->height * fScale;
//
//	//创建图像并缩放  
//	IplImage* dst = cvCreateImage(Size, src->depth, src->nChannels);
//	cvResize(src, dst, CV_INTER_AREA);
//	cvNamedWindow("dst");
//	cvShowImage("dst", dst);
//	cvSaveImage("dst.jpg", dst);
//
//	//CvScalar avgChannels = cvAvg(src);   //先求出该图像的平均像素值，再分离到红绿蓝三通道
//
//	//double avgB = avgChannels.val[0];
//
//	//double avgG = avgChannels.val[1];
//
//	//double avgR = avgChannels.val[2];
//
//	//cout << "r:" << avgR << endl;
//	//cout << "g:" << avgG << endl;
//	//cout << "b:" << avgB << endl;
//
//	int numBad = 0;
//
//	cv::Mat img = cv::Mat(dst);
//
//	cout <<(int) img.at<Vec3b>(10, 10)[0] << endl;
//	cout << (int)img.at<Vec3b>(10, 10)[1] << endl;
//	cout << (int)img.at<Vec3b>(10, 10)[2] << endl;
//
//
//	for (int i = 1; i<img.rows-1; i++)			//检测每个像素
//	{
//		for (int j = 1; j<img.cols-1; j++)
//		{
//			/*cout << (int)img.at<Vec3b>(i, j)[0] << endl;
//			cout << (int)img.at<Vec3b>(i, j)[1] << endl;
//			cout << (int)img.at<Vec3b>(i, j)[2] << endl;*/
//			if (img.at<uchar>(i, j) < 40/* && img.at<uchar>(i, j+1) < 40 && img.at<uchar>(i-1, j) < 40 && img.at<uchar>(i+1, j+1) < 40 */ )
//			{
//				numBad++;
//				//circle(img, cv::Point(j,i), 1, cv::Scalar(255, 0, 0), 1);
//
//				img.at<uchar>(i, j) = 255;
//			}
//		}
//	}
//
//	//for (int i = 1; i<(dst->width)-1; i=i+3)			//检测每个像素
//	//{
//	//	for (int j = 1; j<(dst->height)-1; j=j+3)
//	//	{
//	//		/*cout << cvGet2D(src, i, j).val[0] << endl;
//	//		cout << cvGet2D(src, i, j).val[1] << endl;
//	//		cout << cvGet2D(src, i, j).val[2] << endl;*/
//	//		/*if (cvGet2D(src, i, j).val[0] < 90 && cvGet2D(src, i-1, j-1).val[0] < 90 && cvGet2D(src,i-1,j).val[0] < 90&&
//	//			cvGet2D(src, i-1, j+1).val[0] < 90 && cvGet2D(src, i, j-1).val[0] < 90 && cvGet2D(src, i, j+1).val[0] < 90 &&
//	//			cvGet2D(src, i+1, j-1).val[0] < 90 && cvGet2D(src, i+1, j).val[0] < 90 && cvGet2D(src, i+1, j+1).val[0] < 90)*/
//	//		if (cvGet2D(dst, i, j).val[0] < 45 /*&& cvGet2D(dst, i, j + 1).val[0] < 30 && cvGet2D(dst, i + 1, j).val[0] < 30 &&
//	//			cvGet2D(dst, i + 1, j + 1).val[0] < 30*/ )
//	//		{
//	//			numBad++;
//	//			//cvCircle(src, cv::Point(i, j), 1, cv::Scalar(255, 255, 255), 1);
//	//			cvSet2D(dst, i, j,cvScalar(255,0,0));
//
//	//		}
//
//	//	}
//
//	//}
//
//	//cv::Mat img = cv::Mat(dst);
//	//for (int i = 1; i<img.rows-1; i++)
// //   {
// //         //每一行图像的指针
// //        const uchar* inData = img.ptr<uchar>(i);
// //        //uchar* outData = outImage.ptr<uchar>(i);
// //        for (int j = 1; j<img.cols-1; j++)
// //        {
//	//		 if (img.ptr<uchar>(i)[j] < 40 /*&& img.ptr<uchar>(i)[j+1] < 30 && img.ptr<uchar>(i+1)[j] < 30 && img.ptr<uchar>(i+1)[j+1] < 30*/ )
//	//		 {
//
//	//			 numBad++;
//	//			 /*cout << "i:" << i << "," << "j:" << j << endl;
//	//			 CvPoint p = cvPoint(i, j);
//	//			 cout << "p:" << p.x <<" "<< p.y << endl;
//	//			 circle(img, cvPoint(j,i), 1, cv::Scalar(255, 255, 255), 1);*/
//	//			 img.ptr<uchar>(i)[j] = 255;
//	//		 }
// //        }
// //    }
//
//
//
//
//
//	cout << "numBad:" << numBad << endl;
//
//	
//
//	//cvNamedWindow("src1");
//	//cvShowImage("src1", dst);
//	//cvSaveImage("result.jpg", dst);
//	cvNamedWindow("img");
//	setWindowProperty("img", CV_WND_PROP_FULLSCREEN, CV_WINDOW_FULLSCREEN);
//	imshow("img", img);
//	imwrite("img.jpg",img);
//
//
//	cvWaitKey(0);
//}


void main()
{
	//CvSize Size=cvSize(1600, 900);
	//IplImage* img = cvCreateImage(Size, 8, 3);
	//for (int i =0 ; i<img->width; i++)			//检测每个像素
	//{
	//	for (int j = 0; j<img->height; j++)
	//	{		
	//			cvSet2D(img, j,  i,cvScalar(128,128,128));
	//	}	
	//}

	//cvNamedWindow("img", CV_WND_PROP_FULLSCREEN);
	////cvResizeWindow("src", 2436, 1624);
	//cvSetWindowProperty("img", CV_WND_PROP_FULLSCREEN, CV_WINDOW_FULLSCREEN);
	//cvShowImage("img", img);
	//cvSaveImage("gray.jpg", img);

	char filename[100];

	char windowname[100];
	

	int num = 6;// 读入num个图片

	for (int i = 1; i <= num; i++)
	{
		//sprintf(filename, "D:\\红绿蓝黑 白\\%d.jpg", i);// 将图片以数字命名：例如1.jpg 2.jpg等，放入D:/test/文件夹下
		sprintf(filename, "D:\\红绿蓝黑白169\\%d.jpg", i);// 将图片以数字命名：例如1.jpg 2.jpg等，放入D:/test/文件夹下
		//printf("filename is %d\n", i);
		sprintf(windowname, "window%d.jpg", i);
		IplImage* src = cvLoadImage(filename, 1);//导入图片 
		if (!src)
		{
			printf("err");
		}

		cvNamedWindow("src", CV_WND_PROP_FULLSCREEN);
		//cvResizeWindow("src", 1024, 768);
		cvSetWindowProperty("src", CV_WND_PROP_FULLSCREEN, CV_WINDOW_FULLSCREEN);
		cvShowImage("src", src);
		//ShowCursor（0）;
		ShowCursor(FALSE);//隐藏原来的光标
		////SetCursor(hcursor);//设置新的光标
		//ShowCursor(TRUE);//显示新的光标 

		cvWaitKey(0);
		//ShowCursor(TRUE);//显示新的光标 

	}



	//IplImage *src = cvLoadImage("red.jpg", 0);
	//if (!src)
	//{
	//printf("err");
	//}

	//cvNamedWindow("src", CV_WND_PROP_FULLSCREEN);
	////cvResizeWindow("src", 2436, 1624);
	//cvSetWindowProperty("src", CV_WND_PROP_FULLSCREEN, CV_WINDOW_FULLSCREEN);
	//cvShowImage("src", src);
	//cvWaitKey(0);
}


