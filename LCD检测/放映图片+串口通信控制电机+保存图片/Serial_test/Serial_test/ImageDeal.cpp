#include"ImageDeal.h"


void ImageShow(int num)
{
	char filename[100];
	char windowname[100];
	int i = num;
	sprintf(filename, "红绿蓝黑白\\%d.jpg", i);// 将图片以数字命名：例如1.jpg 2.jpg等，放入D:/test/文件夹下
	//printf("filename is %d\n", i);
	sprintf(windowname, "window%d.jpg", i);
	IplImage* src = cvLoadImage(filename, 1);//导入图片
	if (!src)
	{
		printf("err");
	}
	cvNamedWindow("src", CV_WND_PROP_FULLSCREEN);
	//cvResizeWindow("src", 2436, 1624);
	cvSetWindowProperty("src", CV_WND_PROP_FULLSCREEN, CV_WINDOW_FULLSCREEN);
	cvShowImage("src", src);

	ShowCursor(FALSE);//隐藏原来的光标
	//SetCursor(hcursor);//设置新的光标
	//ShowCursor(TRUE);//显示新的光标 

	//cvWaitKey(5000);
	//cvReleaseImage(&src);
	//cvDestroyWindow("src");

}